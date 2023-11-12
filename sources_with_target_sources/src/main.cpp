#include "conversion.hpp"
#include "evolution.hpp"
#include "initial.hpp"
#include "io.hpp"
#include "parser.hpp"

#include <iostream>

int main(int argc, char *argv[]) {

  // parse arguments
  // int length, num_steps, rule_decimal;
  auto parsed_arguments = parse_arguments(argc, argv);
  auto [length, num_steps, rule_decimal] = parsed_arguments;
  // print information about parameters
  std::cout << "length: " << length << '\n';
  std::cout << "number of steps: " << num_steps << '\n';
  std::cout << "rule: " << rule_decimal << '\n';

  // obtain binary representation for the rule
  std::string rule_binary = binary_representation(rule_decimal);

  // create initial distribution
  std::vector<int> row = initial_distribution(length);

  // print initial configuration
  print_row(row);

  // the system evolves, print each step
  for (int step = 0; step < num_steps; step++) {
    row = evolve(row, rule_binary);
    print_row(row);
  }
}
