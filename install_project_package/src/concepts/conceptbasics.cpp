
#include "conceptbasics.hpp"

static_assert(not are_same<decltype(1), decltype(2.4)>);

int Test::get_value() const { return value; }

int getnumber() { return 5; }
