#pragma once

#include <memory>
#include <ostream>

template<class T, class Allocator = std::allocator<T> >
class Container {
public:

  Container(): head(nullptr) {}
  
  Container(const Container<T, Allocator>& c) = delete;
  ~Container() {
    while (head) {
      auto newHead = head->next;
      std::allocator_traits < decltype(alloc)>::destroy(alloc, head);
      alloc.deallocate(head, 1);
      head = newHead;
    }

  }
  
  Container<T, Allocator>& operator=(const Container<T, Allocator>& c) = delete;

  template <class... Args>
  decltype(auto) emplaceFront(Args&&... args){
    Node* newHead = alloc.allocate(1);
    std::allocator_traits <decltype(alloc)>::construct(alloc, newHead, head, 
                                                   std::forward<Args>(args)...);
    head = newHead;
    return (*head);
  }
    
  void pushFront(const T& other) {
    this->emplaceFront(other);
  }
  
  void pushFront(T&& other){
    this->emplaceFront(std::move(other));
  }
  
  struct Node {
    Node* next;
    T value;    
    
    template <class... Args>
    Node(Node* n, Args&&... args): next(n), value(std::forward<Args>(args)...) {}
  };
  
  
  struct Iterator {

    Iterator(Node* p) : ptr(p) {};
    
    bool operator!=(const Iterator& other) const{
      return !(*this == other);
    }
    
    bool operator==(const Iterator& other) const{
      return ptr == other.ptr;
    }
    
    Iterator& operator++(){
      ptr = ptr->next;
    }
    
    decltype(auto) operator*() const{
      return (ptr->value);
    }

  private:
    Node* ptr;
  };
  
  
  Iterator begin() const{
    return Iterator(head);
  }
  
  Iterator end() const{
    return nullptr;
  }

private:
  typename Allocator::template rebind< Node >::other alloc;
  Node* head;
};

template<class... Args>
std::ostream& operator<<(std::ostream& os, const Container<Args...>& cont){
  for(const auto& elem: cont)
    os << elem << '\n';
  return os;
}