class IntBox
{
public:
  int &x;

  IntBox(int &x)
    : x(x)
  {
    // nothing to do here
  }
};

int main()
{
  {
    int x = 5;
    IntBox box{x};
  }
}
