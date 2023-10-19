#include <array>
#include <experimental/executor>
#include <iostream>
#include <list>
#include <scoped_allocator>
#include <string>

struct StackBuffer {
  alignas(alignof(std::max_align_t)) std::array<std::byte, 512 * 1024> buffer;
  size_t used = 0;

  template <typename T> size_t get_offset() const {
    if (used % alignof(T) == 0)
      return 0;
    return alignof(T) - (used % alignof(T));
  }
  template <typename T> T *allocate(std::size_t cnt) {
    size_t off = get_offset<T>();
    if (used + off + cnt * sizeof(T) >= buffer.size())
      throw std::bad_alloc();
    T *result = reinterpret_cast<T *>(buffer.data() + used + off);
    used += off + cnt * sizeof(T);
    return result;
  }
  void deallocate(void *, std::size_t) {}
};

template <typename T> struct StackAllocator {
  using value_type = T;
  using outer_allocator_type = StackAllocator;
  using inner_allocator_type = StackAllocator;

  explicit StackAllocator(StackBuffer *storage) : storage_(storage) {}
  template <typename U>
  explicit StackAllocator(const StackAllocator<U> &other)
      : storage_(other.storage_) {}

  T *allocate(std::size_t n) {
    std::cerr << "Allocating " << n << " elements of " << sizeof(T)
              << " bytes.\n";
    return storage_->allocate<T>(n);
  }
  void deallocate(T *p, std::size_t n) {
    std::cerr << "Deallocating " << n << " elements of " << sizeof(T)
              << " bytes.\n";
    storage_->deallocate(p, n);
  }

 private:
  template <typename U> friend struct StackAllocator;
  StackBuffer *storage_;
};

int main() {
  StackBuffer buffer;
  using CharAllocator = StackAllocator<char>;
  using String = std::basic_string<char, std::char_traits<char>, CharAllocator>;
  using OuterAllocator = std::scoped_allocator_adaptor<StackAllocator<String>>;

  std::list<String, OuterAllocator> list{OuterAllocator(&buffer)};
  for (int i = 0; i < 10; ++i) {
    list.emplace_back("Hello World, it is a good day today.");
  }
  std::cout << list.front() << "\n";
}
