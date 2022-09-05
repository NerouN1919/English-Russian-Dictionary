#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <iostream>
#include "Node.h"
namespace sviridenko
{
  template < typename T >
  class ForwardList
  {
  public:
    ForwardList();
    ForwardList(const ForwardList& List);
    ~ForwardList();
    ForwardList<T>& operator=(const ForwardList& list);
    void pushFront(const T&);
    void pushBack(const T&);
    void dropFront();
    T peekFront() const;
    bool isEmpty() const noexcept;
    void swap(ForwardList&) noexcept;
    void print() const;
    bool remove(const T& item);
    int size();
    struct Iterator
    {
      Iterator();
      Iterator(const Iterator& other);
      ~Iterator() = default;
      T& operator*();
      Iterator& operator=(const Iterator& other);
      bool operator!=(const Iterator& lhs) const;
      bool operator==(const Iterator& lhs) const;
      Iterator& operator++();
      Iterator operator++(int);
      T* operator->();
    private:
      Node< T >* current_;
      Node< T >* next_;
      Iterator(Node< T >* node);
      friend ForwardList;
    };
    struct ConstIterator
    {
      ConstIterator();
      ConstIterator(const ConstIterator& other);
      ~ConstIterator() = default;
      const T& operator*() const;
      ConstIterator& operator=(const ConstIterator& other);
      bool operator!=(const ConstIterator& lhs) const;
      bool operator==(const ConstIterator& lhs) const;
      ConstIterator& operator++();
      ConstIterator operator++(int);
      const T* operator->() const;
    private:
      Node< T >* current_;
      Node< T >* next_;
      ConstIterator(Node< T >* node);
      friend ForwardList;
    };
    const ConstIterator cbeforeBegin() const;
    const ConstIterator cbegin() const;
    const ConstIterator cend() const;
    Iterator beforeBegin();
    Iterator begin();
    Iterator end();
    Iterator insertAfter(Iterator pos, const T& item);
  private:
    Node< T >* head_;
    Node< T >* tail_;
  };

  template< typename T >
  const typename ForwardList< T >::ConstIterator ForwardList< T >::cbeforeBegin() const
  {
    ConstIterator it;
    it.current_ = nullptr;
    it.next_ = head_;
    return it;
  }
  template< typename T >
  const typename ForwardList< T >::ConstIterator ForwardList< T >::cbegin() const
  {
    return ConstIterator(head_);
  }
  template< typename T >
  const typename ForwardList< T >::ConstIterator ForwardList< T >::cend() const
  {
    return ConstIterator(nullptr);
  }
  template< typename T >
  typename ForwardList< T >::Iterator ForwardList< T >::beforeBegin()
  {
    Iterator it;
    it.current_ = nullptr;
    it.next_ = head_;
    return it;
  }
  template< typename T >
  typename ForwardList< T >::Iterator ForwardList< T >::begin()
  {
    return Iterator(head_);
  }
  template< typename T >
  typename ForwardList< T >::Iterator ForwardList< T >::end()
  {
    return Iterator(nullptr);
  }

  template< typename T >
  ForwardList< T >::Iterator::Iterator() :
    current_(nullptr),
    next_(nullptr)
  {}

  template< typename T >
  ForwardList< T >::Iterator::Iterator(const Iterator& other) :
    current_(other.current_),
    next_(other.next_)
  {}

  template< typename T >
  ForwardList< T >::ConstIterator::ConstIterator() :
    current_(nullptr),
    next_(nullptr)
  {}

  template< typename T >
  ForwardList< T >::ConstIterator::ConstIterator(const ConstIterator& other) :
    current_(other.current_),
    next_(other.next_)
  {}

  template< typename T >
  ForwardList< T >::ConstIterator::ConstIterator(Node< T >* node)
  {
    if (node == nullptr)
    {
      current_ = nullptr;
      next_ = nullptr;
    }
    else
    {
      current_ = node;
      next_ = node->next_;
    }
  }

  template< typename T >
  ForwardList< T >::Iterator::Iterator(Node< T >* node)
  {
    if (node == nullptr)
    {
      current_ = nullptr;
      next_ = nullptr;
    }
    else
    {
      current_ = node;
      next_ = node->next_;
    }
  }
  template< typename T >
  T& ForwardList< T >::Iterator::operator*()
  {
    return current_->data;
  }
  template< typename T >
  const T& ForwardList< T >::ConstIterator::operator*() const
  {
    return current_->data;
  }
  template< typename T >
  typename ForwardList< T >::Iterator& ForwardList< T >::Iterator::operator=(const Iterator& other)
  {
    Iterator newIt(other);
    std::swap(current_, newIt.current_);
    std::swap(next_, newIt.next_);
    return *this;
  }
  template< typename T >
  bool ForwardList< T >::Iterator::operator!=(const Iterator& lhs) const
  {
    return !(*this == lhs);
  }
  template< typename T >
  bool ForwardList< T >::Iterator::operator==(const Iterator& lhs) const
  {
    return current_ == lhs.current_;
  }
  template< typename T >
  typename ForwardList< T >::Iterator& ForwardList< T >::Iterator::operator++()
  {
    current_ = next_;
    if (next_ != nullptr)
    {
      next_ = next_->next_;
    }
    return *this;
  }
  template< typename T >
  typename ForwardList< T >::Iterator ForwardList< T >::Iterator::operator++(int)
  {
    Iterator result(*this);
    ++(*this);
    return result;
  }
  template< typename T >
  typename ForwardList< T >::ConstIterator& ForwardList< T >::ConstIterator::operator=(const ConstIterator& other)
  {
    ConstIterator newIt(other);
    std::swap(current_, newIt.current_);
    std::swap(next_, newIt.next_);
    return *this;
  }
  template< typename T >
  bool ForwardList< T >::ConstIterator::operator!=(const ConstIterator& lhs) const
  {
    return !(*this == lhs);
  }
  template< typename T >
  bool ForwardList< T >::ConstIterator::operator==(const ConstIterator& lhs) const
  {
    return current_ == lhs.current_;
  }
  template< typename T >
  typename ForwardList< T >::ConstIterator& ForwardList< T >::ConstIterator::operator++()
  {
    current_ = next_;
    if (next_ != nullptr)
    {
      next_ = next_->next_;
    }
    return *this;
  }
  template< typename T >
  typename ForwardList< T >::ConstIterator ForwardList< T >::ConstIterator::operator++(int)
  {
    ConstIterator result(*this);
    ++(*this);
    return result;
  }
  template< typename T >
  T* ForwardList< T >::Iterator::operator->()
  {
    return std::addressof(current_->data);
  }
  template< typename T >
  const T* ForwardList< T >::ConstIterator::operator->() const
  {
    return std::addressof(current_->data);
  }

  template < typename T >
  ForwardList< T >::ForwardList() :
    head_(nullptr),
    tail_(nullptr)
  {}

  template < typename T >
  ForwardList< T >::ForwardList(const ForwardList& list) :
    head_(nullptr),
    tail_(nullptr)
  {
    ForwardList temp;
    Node< T >* src = list.head_;
    while (src)
    {
      temp.pushBack(src->data);
      src = src->next_;
    }
    swap(temp);
  }

  template < typename T >
  ForwardList< T >& ForwardList<T>::operator=(const ForwardList& list)
  {
    if (this == &list)
    {
      return *this;
    }

    ForwardList< T > tempList(list);
    swap(tempList);

    return *this;
  }

  template < typename T >
  void ForwardList< T >::swap(ForwardList& list) noexcept
  {
    std::swap(head_, list.head_);
    std::swap(tail_, list.tail_);
  }

  template < typename T >
  bool ForwardList< T >::remove(const T& item)
  {
    if (head_ != nullptr)
    {
      Node< T >* currentNode = head_;
      if (head_->data == item)
      {
        head_ = head_->next_;
        currentNode->next_ = nullptr;
        delete currentNode;
        return true;
      }
      while (currentNode->next_ != nullptr)
      {
        if (currentNode->next_->data == item)
        {
          Node< T >* uslNode = currentNode->next_;
          if (uslNode->next_ != nullptr)
          {
            currentNode->next_ = uslNode->next_;
            uslNode->next_ = nullptr;
          }
          else
          {
            currentNode->next_ = nullptr;
          }
          delete uslNode;
          return false;
        }
        currentNode = currentNode->next_;
      }
    }
    return false;
  }

  template < typename T >
  ForwardList< T >::~ForwardList()
  {
    while (head_)
    {
      Node< T >* temp = head_;
      head_ = head_->next_;
      delete temp;
    }
  }

  template < typename T >
  void ForwardList< T >::pushBack(const T& d)
  {
    if (!head_)
    {
      head_ = tail_ = new Node< T >;
    }
    else
    {
      tail_->next_ = new Node< T >;
      tail_ = tail_->next_;
    }
    tail_->data = d;
    tail_->next_ = nullptr;
  }

  template < typename T >
  void ForwardList< T >::pushFront(const T& d)
  {
    Node< T >* newNode = new Node< T >;
    newNode->data = d;
    newNode->next_ = head_;
    head_ = newNode;
  }

  template< typename T >
  typename ForwardList< T >::Iterator ForwardList< T >::insertAfter(typename ForwardList< T >::Iterator pos, const T& item)
  {
    if (pos == beforeBegin())
    {
      if (head_ != nullptr)
      {
        Node< T >* exHead = head_;
        head_ = new Node< T >;
        head_->data = item;
        head_->next_ = exHead;
        return begin();
      }
      else
      {
        head_ = new Node< T >;
        head_->data = item;
        return begin();
      }
    }
    else
    {
      Node< T >* temp = pos.next_;
      pos.next_ = new Node< T >;
      pos.next_->data = item;
      pos.current_->next_ = pos.next_;
      ++pos;
      if (temp != nullptr)
      {
        pos.next_ = temp;
        pos.current_->next_ = pos.next_;
      }
      return pos;
    }
  }

  template < typename T >
  T ForwardList< T >::peekFront() const
  {
    Node< T >* temp = head_;
    return temp->data;
  }

  template < typename T >
  void ForwardList< T >::dropFront()
  {
    if (!head_)
    {
      throw std::logic_error("Standque is empty");
    }
    Node< T >* temp = head_;
    if (head_ == tail_)
    {
      head_ = tail_ = nullptr;
    }
    else
    {
      head_ = head_->next_;
    }
    delete temp;
  }

  template < typename T >
  bool ForwardList< T >::isEmpty() const noexcept
  {
    if (!head_)
    {
      return true;
    }
    return false;
  }

  template < typename T >
  void ForwardList< T >::print() const
  {
    Node< T >* temp = head_;
    while (temp)
    {
      if (temp->next_ == nullptr)
      {
        std::cout << temp->data;
      }
      else
      {
        std::cout << temp->data << " ";
      }
      temp = temp->next_;
    }
  }

  template < typename T >
  int ForwardList< T >::size()
  {
    int counter = 0;
    for (Iterator it = begin(); it != end(); it++)
    {
      counter++;
    }
    return counter;
  }
}
#endif
