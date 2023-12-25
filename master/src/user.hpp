#pragma once
#include <string>

// dummy user implementation
class User {
 private:
  const std::string email;

 public:
  User(std::string email = "guest");
  std::string get_email() const;
};
