#pragma once
#include "apoccommon.h"

namespace Apoc
{
  //! A doubly-linked list
  template <typename T>
  class LinkedList
  {
    struct Node;

  public:
    class Iterator
    {
      friend class LinkedList;

      Node* node;

    public:
      inline Iterator(Node* node = 0) : node(node) {}

      Iterator& operator = (const Iterator& iterator)
      {
        node = iterator.node;
	return *this;
      }

      Iterator& operator ++ ()
      {
        if (node->next)
          node = node->next;

        return *this;
      }

      Iterator operator ++ (int)
      {
        Node* oldNode = node;

        if (node->next)
          node = node->next;

        return Iterator(oldNode);
      }

      T& operator * ()
      { return node->value; }

      const T& operator * () const
      { return node->value; }

      bool operator != (const Iterator& iterator)
      { return this->node != iterator.node; }
 
      bool operator == (const Iterator& iterator)
      { return this->node == iterator.node; }
    };

  private:
    struct Node
    {

      T value;
      Node* previous;
      Node* next;

      inline Node(const T& value, Node* previous = 0, Node* next = 0) :
        value(value), previous(previous), next(next) {}
    };


    Node* start;
    Node* end;
  public:
    inline LinkedList() : start(0), end(0) {}

    inline void Append(const T& value)
    {
      if (!start)
        start = end = new Node(value, 0, 0);
      else
        end = end->next = new Node(value, end, 0);
    }

    inline Iterator Begin()
    { return Iterator(start); }

    inline Iterator End()
    { return Iterator(end); }

    inline const Iterator Begin() const
    { return Iterator(start); }

    inline const Iterator End() const
    { return Iterator(end); }

    inline void Remove(Iterator element)
    {
      Node* const previous = element.node->previous;
      Node* const next = element.node->next;

      if (previous)
        previous->next = next;
      if (next)
        next->previous = previous;

      if (element.node == start)
        start = 0;
      else if (element.node == end)
        end = previous;
    }
  };
}
