#include <iostream>
#include <vector>

int main()
{
  std::vector<int> v{1, 2, 3};

  *v.begin() = 4;

  auto it = v.begin();
  if (it != v.end())
  {
    std::cout << *it;
    ++it;
  }

  for (; it != v.end(); ++it)
  {
    std::cout << ", " << *it;
  }
}
