#include <vector>

int main()
{
  std::vector<int> v{1, 2, 3};

  v->*foo;
}
