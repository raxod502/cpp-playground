#include <iostream>

int main()
{
  int **arrayOfPointer = new int *[3];
  for (unsigned int i=0; i<3; ++i)
  {
    arrayOfPointer[i] = new int;
    *(arrayOfPointer[i]) = i;
    std::cout << *(arrayOfPointer[i]) << std::endl;
  }

  int **pointerToArray = new int *;
  *pointerToArray = new int[3];
  for (unsigned int i=0; i<3; ++i)
  {
    (*pointerToArray)[i] = i;
    std::cout << (*pointerToArray)[i] << std::endl;
  }

  delete[] *pointerToArray;
  delete pointerToArray;

  for (unsigned int i=0; i<3; ++i)
  {
    delete arrayOfPointer[i];
  }
  delete[] arrayOfPointer;
}
