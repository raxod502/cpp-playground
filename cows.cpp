#include <iostream>

class Cow
{
private:
  unsigned int numSpots;

public:
  Cow()
    : numSpots(0)
  {
    std::cout << "Cow: Default constructor: " << this << std::endl;
  }

  explicit Cow(const unsigned int numSpots)
    : numSpots(numSpots)
  {
    std::cout << "Cow: Parameterized constructor: " << this << " <- " <<
      numSpots << std::endl;
  }

  Cow(const Cow &other)
    : numSpots(other.numSpots)
  {
    std::cout << "Cow: Copy constructor: " << this << " <- " << &other <<
      std::endl;
  }

  Cow &operator=(const Cow &other)
  {
    std::cout << "Cow: Assignment operator: " << this << " <- " << &other <<
      std::endl;

    if (this != &other)
    {
      numSpots = other.numSpots;
    }
    return *this;
  }

  ~Cow()
  {
    std::cout << "Cow: Destructor: " << this << std::endl;
  }
};

void testCow()
{
  std::cout << "--> Create Cow on stack" << std::endl;
  const Cow stackCow;

  std::cout << "--> Create Cow on heap" << std::endl;
  const Cow *const heapCow = new Cow;

  std::cout << "--> Create array of Cows on stack" << std::endl;
  const Cow stackCows[3];

  std::cout << "--> Create array of Cows on heap" << std::endl;
  const Cow *const heapCows = new Cow[3];

  std::cout << "--> Create array of Cow pointers on stack" << std::endl;
  const Cow *stackCowPointers[3];
  for (unsigned int i=0; i<3; ++i)
  {
    stackCowPointers[i] = new Cow;
  }

  std::cout << "--> Create array of Cow pointers on heap" << std::endl;
  const Cow **const heapCowPointers = new const Cow *[3];
  for (unsigned int i=0; i<3; ++i)
  {
    heapCowPointers[i] = new Cow;
  }

  std::cout << "--> Destroy array of Cow pointers on heap" << std::endl;
  for (unsigned int i=0; i<3; ++i)
  {
    delete heapCowPointers[i];
  }
  delete[] heapCowPointers;

  std::cout << "--> Destroy array of Cow pointers on stack" << std::endl;
  for (unsigned int i=0; i<3; ++i)
  {
    delete stackCowPointers[i];
  }

  std::cout << "--> Destroy array of Cows on heap" << std::endl;
  delete[] heapCows;

  std::cout << "--> Destroy Cow on heap" << std::endl;
  delete heapCow;

  std::cout << "--> Finalize" << std::endl;
}

class Barn {
private:
  unsigned int numStalls;
  Cow **stalls;

public:
  Barn(const int numStalls, Cow **const stalls)
    : numStalls(numStalls), stalls(stalls)
  {
    std::cout << "Barn: Parameterized constructor: " << this << std::endl;
  }

  Barn(const Barn &other)
    : numStalls(other.numStalls), stalls(new Cow *[other.numStalls])
  {
    std::cout << "Barn: Copy constructor: " << this << " <- " << &other <<
      std::endl;
    for (unsigned int i = 0; i < numStalls; ++i)
    {
      stalls[i] = new Cow(*other.stalls[i]);
    }
  }

  Barn &operator=(const Barn &other)
  {
    std::cout << "Barn: Assignment operator: " << this << " <- " << &other <<
      std::endl;
    if (this != &other)
    {
      for (unsigned int i = 0; i < numStalls; ++i)
      {
        delete stalls[i];
      }
      delete[] stalls;

      numStalls = other.numStalls;
      stalls = new Cow *[other.numStalls];
      for (unsigned int i = 0; i < other.numStalls; ++i)
      {
        stalls[i] = new Cow(*other.stalls[i]);
      }
    }
    return *this;
  }

  ~Barn()
  {
    std::cout << "Barn: Destructor: " << this << std::endl;
    for (unsigned int i = 0; i < numStalls; ++i)
    {
      delete stalls[i];
    }
    delete[] stalls;
  }
};

void testBarn()
{
  std::cout << "--> Create array of Cow pointers on heap" << std::endl;
  const int numStalls = 3;
  Cow **const stalls = new Cow *[numStalls];
  for (unsigned int i = 0; i < numStalls; ++i)
  {
    stalls[i] = new Cow(i);
  }

  std::cout << "--> Create barn" << std::endl;
  Barn barn1(numStalls, stalls);

  std::cout << "--> Copy barn" << std::endl;
  Barn barn2 = barn1;

  std::cout << "--> Assign barn" << std::endl;
  barn1 = barn2;

  std::cout << "--> Finalize" << std::endl;
}

int main()
{
  testCow();
  testBarn();
}
