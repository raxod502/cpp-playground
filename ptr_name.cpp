#include <iostream>

int main()
{
  int *ptr;
  std::cout << "How to spell a pointer: " << typeid(ptr).name() << std::endl;
}
