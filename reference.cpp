#include <iostream>

int main()
{
  int x = 5;
  int *y = &x;
  int &z = *y;
  int w = 6;
  *y = w;
  std::cout << z << std::endl;
}
