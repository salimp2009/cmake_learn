namespace sp {
template <bool nexcept, bool operatorPlus, bool validReturnType> struct Stub {
  Stub operator+(const Stub &rhs) const noexcept(nexcept)
    requires(operatorPlus && validReturnType)
  {
    return Stub{};
  }

  // invalid return type
  int operator+(const Stub &rhs) noexcept(nexcept)
    requires(operatorPlus && not validReturnType)
  {
    return {};
  }
};

using NoAdd = Stub<true, false, true>;
using ValidClass = Stub<true, true, true>;
using NotExcept = Stub<false, true, true>;
using DifferentReturnType = Stub<true, true, false>;
using NoAddNotExceptDiffRtnrType = Stub<false, false, false>;
} // namespace sp
