#include "stockindex.hpp"

namespace sp {
message_EXPORT std::vector<StockIndex> getindices() {

  StockIndex dax{"DAX"};
  dax.set_points(13'052.95);
  dax.set_points(13'108.50);

  StockIndex dow{"Dow"};
  dow.set_points(29'080.07);
  dow.set_points(29'290.00);

  return {dax, dow};
}

} // namespace sp
