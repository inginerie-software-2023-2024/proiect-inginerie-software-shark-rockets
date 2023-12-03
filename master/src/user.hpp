#pragma once
#include <string>

// dummy user implementation
class User {
 private:
  const std::string name;

 public:
  User(std::string name = "guest");
  std::string get_name() const;
};
