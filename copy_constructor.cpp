#include <iostream>

class Example
{
public:
  Example()
  {
    std::cout << "Default constructor invoked for object at " << this << "." << std::endl;
  }

  Example(const Example &src)
  {
    std::cout << "Copy constructor invoked for object at " << this << " copying object at " << &src << "." << std::endl;
  }

  ~Example()
  {
    std::cout << "Destructor invoked for object at " << this << "." << std::endl;
  }
};

Example process(Example src)
{
  std::cout << "Processing function invoked on object at " << &src << "." << std::endl;
  return src;
}

int main()
{
  std::cout << "Main function started." << std::endl;
  Example foo;
  std::cout << "Example object initialized." << std::endl;
  Example bar = process(foo);
  std::cout << "Main function finished." << std::endl;
}
