#include <iostream>
#include <iterator>
#include <vector>

class Bowl
{
public:
  unsigned int apples;
  unsigned int oranges;
  unsigned int bananas;

  Bowl(unsigned int apples, unsigned int oranges, unsigned int bananas)
    : apples(apples), oranges(oranges), bananas(bananas)
  {
    // nothing to do here
  }
};

template <typename TClass, typename TIterator, typename TResult>
TResult sum_attribute(TIterator begin, TIterator end, TResult TClass::*attribute)
{
  TResult sum = 0;
  for (TIterator it = begin; it != end; ++it)
  {
    sum += (*it).*attribute;
  }
  return sum;
}

int main()
{
  std::vector<Bowl> bowls =
    {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
    };

  int num_apples = sum_attribute(std::begin(bowls), std::end(bowls), &Bowl::apples);
  int num_oranges = sum_attribute(std::begin(bowls), std::end(bowls), &Bowl::oranges);
  int num_bananas = sum_attribute(std::begin(bowls), std::end(bowls), &Bowl::bananas);

  std::cout << "We have " << num_apples << " apples, " << num_oranges << " oranges, and " <<
    num_bananas << " bananas. Now wasn't that fun?" << std::endl;
}
