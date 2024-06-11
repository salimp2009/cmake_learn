#pragma once

class Account {
public:
  Account();
  ~Account();

  void deposit(const double amount);
  void withdraw(const double amount);
  double get_balance() const;

private:
  double balance{0.0};
  bool is_initialized{false};
};
