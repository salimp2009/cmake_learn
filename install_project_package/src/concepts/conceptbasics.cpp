
#include "conceptbasics.hpp"

static_assert(not sp::are_same_v<decltype(1), decltype(2.4)>);

int sp::Test::get_value() const { return value; }

int sp::getnumber() { return 5; }
