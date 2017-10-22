#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

template <class T>
class Vector
{
public:
  class iterator
  {
  private:
    // The containing Vector.
    Vector<T> *m_vector;

    // The current index of the iterator.
    size_t m_idx;

    // In order to represent an iterator which has been decremented
    // past the beginning, we need more than a size_t can accomodate.
    // If this boolean is true, then idx is "-1".
    bool m_beforeBegin;

    // Is this a reverse iterator, or not?
    bool m_isReverse;

  public:
    iterator() = delete;

    iterator(
      Vector<T> *vector, size_t idx, bool beforeBegin, bool isReverse)
      : m_vector(vector), m_idx(idx), m_beforeBegin(beforeBegin),
        m_isReverse(isReverse)
    {
      // nothing to do here
    }

    iterator(const iterator &other) = default;

    iterator &operator=(const iterator &other) = default;

  private:
    int compare(const iterator &other) const
    {
      int result;
      if (m_beforeBegin)
      {
        if (other.m_beforeBegin)
        {
          result = 0;
        }
        else
        {
          result = -1;
        }
      }
      else
      {
        if (other.m_beforeBegin)
        {
          result = 1;
        }
        else if (m_idx < other.m_idx)
        {
          result = -1;
        }
        else if (m_idx == other.m_idx)
        {
          result = 0;
        }
        else
        {
          result = 1;
        }
      }

      if (m_isReverse)
      {
        return -result;
      }
      else
      {
        return result;
      }
    }

  public:
    bool &operator==(const iterator &other) const
    {
      return compare(other) == 0;
    }

    bool operator!=(const iterator &other) const
    {
      return compare(other) != 0;
    }

    bool operator<(const iterator &other) const
    {
      return compare(other) < 0;
    }

    bool operator<=(const iterator &other) const
    {
      return compare(other) <= 0;
    }

    bool operator>(const iterator &other) const
    {
      return compare(other) > 0;
    }

    bool operator>=(const iterator &other) const
    {
      return compare(other) >= 0;
    }

    T &operator*() const
    {
      if (m_beforeBegin)
      {
        throw std::out_of_range(
          "attempt to dereference iterator before beginning of vector");
      }
      else if (m_idx >= m_vector->m_size)
      {
        throw std::out_of_range(
          "attempt to dereference iterator after end of vector");
      }
      else
      {
        return m_vector->m_arr[m_idx];
      }
    }

  private:
    iterator &increment()
    {
      if (m_beforeBegin)
      {
        m_beforeBegin = false;
        m_idx = 0;
      }
      else if (m_idx >= m_vector->m_size)
      {
        throw std::out_of_range(
          "attempt to increment iterator after end of vector");
      }
      else
      {
        ++m_idx;
      }
      return *this;
    }

    iterator &decrement()
    {
      if (m_beforeBegin)
      {
        throw std::out_of_range(
          "attempt to decrement iterator before beginning of vector");
      }
      else if (m_idx == 0)
      {
        m_beforeBegin = true;
      }
      else
      {
        --m_idx;
      }
      return *this;
    }

  public:
    iterator &operator++()
    {
      if (m_isReverse)
        return decrement();
      else
        return increment();
    }

    iterator &operator--()
    {
      if (m_isReverse)
        return increment();
      else
        return decrement();
    }
  };

private:
  // The initial capacity of the data array when an empty Vector is
  // created.
  static const size_t INITIAL_CAPACITY = 10;

  // The factor by which the data array capacity is increased when the
  // Vector needs to accomodate more elements.
  static const unsigned int RESIZE_FACTOR = 2;

  // The maximum possible capacity.
  static const size_t MAX_SIZE = std::numeric_limits<size_t>::max();

  // The current capacity of the data array.
  size_t m_capacity;

  // The number of valid elements in the data array. This is the
  // user-facing size of the Vector.
  size_t m_size;

  // The data array, which holds the actual elements. (This means the
  // elements must have default constructors; use pointers to avoid
  // this.)
  T *m_arr;

public:
  Vector()
    : m_capacity(INITIAL_CAPACITY), m_size(0), m_arr(new T[INITIAL_CAPACITY])
  {
    // nothing to do here
  }

  Vector(const Vector<T> &other)
    : m_capacity(other.m_capacity), m_size(other.m_size),
      m_arr(new T[other.m_capacity])
  {
    for (size_t i = 0; i < other.m_size; ++i)
    {
      m_arr[i] = other.m_arr[i];
    }
  }

  ~Vector()
  {
    delete[] m_arr;
  }

  Vector &operator=(const Vector &other)
  {
    if (this != &other)
    {
      delete[] m_arr;

      m_capacity = other.m_capacity;
      m_size = other.m_size;
      m_arr = new T[other.m_capacity];

      for (size_t i = 0; i < other.m_size; ++i)
      {
        m_arr[i] = other.m_arr[i];
      }
    }
  }

  T &operator[](size_t idx) const
  {
    if (idx >= m_size)
    {
      throw std::out_of_range(
        "index out of bounds: " + std::to_string(idx) + " > " +
        std::to_string(m_size));
    }

    return m_arr[idx];
  }

  T &front() const
  {
    if (m_size == 0)
    {
      throw std::runtime_error(
        "attempt to retrieve element from front of empty vector");
    }

    return m_arr[0];
  }

  T &back() const
  {
    if (m_size == 0)
    {
      throw std::runtime_error(
        "attempt to retrieve element from back of empty vector");
    }

    return m_arr[m_size - 1];
  }

  iterator begin()
  {
    return iterator(this, 0, false, false);
  }

  iterator end()
  {
    return iterator(this, m_size, false, false);
  }

  iterator rbegin() const
  {
    if (m_size == 0)
    {
      return iterator(this, 0, true, true);
    }
    else
    {
      return iterator(this, m_size - 1, false, true);
    }
  }

  iterator rend() const
  {
    return iterator(this, 0, true, true);
  }

  bool empty() const
  {
    return m_size == 0;
  }

  size_t size() const
  {
    return m_size;
  }

  void clear()
  {
    m_size = 0;
  }

private:
  void ensure_capacity()
  {
    if (m_size == m_capacity)
    {
      if (m_capacity == MAX_SIZE)
      {
        throw std::length_error(
          "vector size too large: " + std::to_string(m_capacity) + " + 1");
      }
      else
      {
        size_t newCapacity;
        if (m_capacity > MAX_SIZE / RESIZE_FACTOR)
        {
          newCapacity = MAX_SIZE;
        }
        else
        {
          newCapacity = m_capacity * RESIZE_FACTOR;
        }

        T *newArr = new T[newCapacity];

        for (size_t i = 0; i < m_size; ++i)
        {
          newArr[i] = m_arr[i];
        }
        delete[] m_arr;

        m_capacity = newCapacity;
        m_arr = newArr;
      }
    }
  }

public:
  void push_back(const T &value)
  {
    ensure_capacity();
    m_arr[m_size] = value;
    ++m_size;
  }

  void pop_back()
  {
    --m_size;
  }

private:
  int compare(const Vector<T> &other) const
  {
    const size_t size = std::min(m_size, other.m_size);
    for (size_t i = 0; i < size; ++i)
    {
      if (m_arr[i] < other.m_arr[i])
        return -1;
      if (m_arr[i] > other.m_arr[i])
        return 1;
    }

    if (m_size < other.m_size)
      return -1;
    if (m_size > other.m_size)
      return 1;

    return 0;
  }

public:
  bool operator==(const Vector<T> &other) const
  {
    return compare(other) == 0;
  }

  bool operator!=(const Vector<T> &other) const
  {
    return compare(other) != 0;
  }

  bool operator<(const Vector<T> &other) const
  {
    return compare(other) < 0;
  }

  bool operator<=(const Vector<T> &other) const
  {
    return compare(other) <= 0;
  }

  bool operator>(const Vector<T> &other) const
  {
    return compare(other) > 0;
  }

  bool operator>=(const Vector<T> &other) const
  {
    return compare(other) >= 0;
  }
};

#endif
