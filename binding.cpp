#include <iostream>

int main()
{
  int x = 1;
  int &y = x, &z = x;
  z = 2;
  std::cout << x << std::endl;
}
