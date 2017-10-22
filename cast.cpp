class A {};
class B {};

class Class
{
  Class &operator=(A &other);
  Class &operator=(B &other);
};
