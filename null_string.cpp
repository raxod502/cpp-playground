#include <iostream>
#include <string>

using namespace std::string_literals;

int main()
{
  std::string naive_initialization{"null\0byte"};
  std::string parameterized_initialization{"null\0byte", 9};
  std::string literal_initialization = "null\0byte"s;

  std::cout << "With naive initialization, we have " <<
    naive_initialization.length() << " characters." << std::endl;
  std::cout << "With parameterized initialization, we have " <<
    parameterized_initialization.length() << " characters." << std::endl;
  std::cout << "With literal initialization, we also have " <<
    literal_initialization.length() << " characters." << std::endl;
  std::cout << "Watch out!" << std::endl;
}
