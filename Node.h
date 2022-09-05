#ifndef NODE_H
#define NODE_H
namespace sviridenko
{
  template < typename T >
  struct Node
  {
  public:
    T data;
    Node* next_ = nullptr;
  };
}
#endif
