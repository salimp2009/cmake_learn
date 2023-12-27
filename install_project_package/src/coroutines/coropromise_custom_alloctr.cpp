#include "coropromise_custom_alloctr.hpp"

namespace sp {

void *arena::allocate(std::size_t size) noexcept {

  auto objectsize = size;
  size += sizeof(arena *);

  char *ptr = new char[size];
  [[maybe_unused]] arena *aa = reinterpret_cast<arena *>(ptr + objectsize);
  aa = this;

  arena *b = reinterpret_cast<arena *>(ptr + objectsize);

#ifdef DEBUG
  printf("custom alloc %zu  %s  %p  %p\n", objectsize, ptr, this, b);
#endif

  return ptr;
}

void arena::deallocate(void *ptr, std::size_t size) noexcept {

#ifdef DEBUG
  printf("custom dealloc %zu  %p  %p\n", size, ptr, this);
#endif

  delete[] static_cast<char *>(ptr);
}

arena *arena::getfrom_ptr(void *ptr, std::size_t size) {
  return reinterpret_cast<arena *>(static_cast<char *>(ptr) + size);
}

} // namespace sp
