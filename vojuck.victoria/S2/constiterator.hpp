#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include <cassert>
#include <iterator>
#include <forward_list>
#include "node.hpp"
#include "list.hpp"

namespace vojuck
{
  template < typename T >
  class List;
  template < typename T >
  struct ConstIteratorList
  {
    friend class List< T >;
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    ConstIteratorList():
      node_(nullptr)
    {}
    ConstIteratorList(details::Node< T > * node):
      node_(node)
    {}
    ~ConstIteratorList() = default;

    ConstIteratorList(const ConstIteratorList &) = default;
    ConstIteratorList(const IteratorList< T > & other):
      node_(other.node_)
    {}
    ConstIteratorList & operator=(const ConstIteratorList &) = default;
    ConstIteratorList & operator++()
    {
      assert(node_ != nullptr);
      node_ = node_->next_;
      return *this;
    }
    ConstIteratorList operator++(int)
    {
      assert(node_ != nullptr);
      ConstIteratorList result(*this);
      ++(*this);
      return result;
    }
    const T & operator*() const
    {
      assert(node_ != nullptr);
      return node_->data_;
    }
    const T * operator->() const
    {
      assert(node_ != nullptr);
      return std::addressof(node_->data_);
    }

    bool operator==(const ConstIteratorList & rhs) const
    {
      return node_ == rhs.node_;
    }
    bool operator!=(const ConstIteratorList & rhs) const
    {
      return !(rhs == *this);
    }
  private:
    details::Node< T > * node_;
  };
}

#endif