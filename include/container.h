#include <memory>
#include <ostream>

template<class T>
struct Node {
  T value;
  Node<T>* next;

  Node(const T& v, Node<T>* n) : value(v), next(n) {};
};

template<class T, class Allocator = std::allocator<T> >
class Container {
public:

  Container() : head(nullptr) {}
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

  void pushBack(const T& other) {
    Node<T>* newHead = alloc.allocate(1);
    std::allocator_traits <decltype(alloc)>::construct(alloc, newHead, other, head);
    head = newHead;
  }

  struct Iterator {

    Iterator(Node<T>* p) : ptr(p) {};
    
    bool operator!=(const Iterator& other) const{
      return !(*this == other);
    }
    
    bool operator==(const Iterator& other) const{
      return ptr == other.ptr;
    }
    
    Iterator& operator++(){
      ptr = ptr->next;
    }
    
    //refferenc or value???
    decltype(auto) operator*() const{
      return (ptr->value);
    }

  private:
    Node<T>* ptr;
  };
  
  Iterator begin() const{
    return Iterator(head);
  }
  
  Iterator end() const{
    return nullptr;
  }

private:
  typename Allocator::template rebind< Node<T> >::other alloc;
  Node<T>* head;
};

template<class... Args>
std::ostream& operator<<(std::ostream& os, const Container<Args...>& cont){
  for(const auto& elem: cont)
    os<<elem<<'\n';
  return os;
}