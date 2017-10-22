template <typename T>
class FakePointer
{
private:
  T m_data;

public:
  FakePointer(T data)
    : m_data(data)
  {
    // nothing to do here
  }

  T &operator*()
  {
    return m_data;
  }

  FakePointer *operator->()
  {
    return this;
  }
};
