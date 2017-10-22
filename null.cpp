#include <iostream>
#include <string>

int main()
{
  std::cout << "C-style string" << std::endl;
  for (char c : "hello")
    std::cout << "Got character: " << c << std::endl;

  std::cout << "STL string" << std::endl;
  for (char c: static_cast<std::string>("hello"))
    std::cout << "Got character: " << c << std::endl;
}
