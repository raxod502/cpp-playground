class Outer
{
  class Inner
  {
  private:
    int x;
  };

  int get(Inner inner)
  {
    return inner.x;
  }
};
