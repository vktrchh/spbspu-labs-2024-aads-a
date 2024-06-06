#ifndef SORTINGS_HPP
#define SORTINGS_HPP

#include <algorithm>
#include <iterator>

namespace novokhatskiy
{
  template < class Iter, class P >
  void doShakerSort(Iter begin, Iter end, P cmp)
  {
    auto last = std::prev(end);
    bool swapped = true;
    while (swapped)
    {
      swapped = false;
      for (auto i = begin; i != last; i++)
      {
        auto next = std::next(i);
        if (!cmp(*i, *next))
        {
          std::swap(*i, *next);
          swapped = true;
        }
      }
      last = std::prev(last);
      if (!swapped)
      {
        break;
      }
      swapped = false;
      for (auto i = last; i != begin; --i)
      {
        auto prev = std::prev(i);
        if (cmp(*i, *prev))
        {
          std::swap(*i, *prev);
          swapped = true;
        }
      }
      begin = std::next(begin);
    }
  }

  template < class It, class P >
  void doInsertionSort(It begin, It end, P cmp)
  {
    for (auto i = begin; i != end; i++)
    {
      auto tmp = std::upper_bound(begin, i, *i, cmp);
      std::rotate(tmp, i, std::next(i));
    }
  }
}

#endif
