#pragma once

#include <stdexcept>


template <typename T, const std::size_t totalSize=1>
class reserveAllocator{
public:
    
  using value_type = T;
  
  reserveAllocator(): offset(0){
    if(totalSize <= 0)
      throw std::logic_error("ReserveAllocator: totalSize must be more 0"); 
    
    memPtr = reinterpret_cast<T*> (::operator new (totalSize * sizeof(T)));      
  };
  
  ~reserveAllocator(){
    ::operator delete(memPtr);
  };
  
  T *allocate(std::size_t n) {
    T* ptr = nullptr;      
    const std::size_t newOffset = offset + n;
    if(newOffset <= totalSize){
      ptr = memPtr + offset;
      offset = newOffset;        
    } else
      throw std::bad_alloc();    
    
    return ptr; 
  }
  
  void deallocate(T *p, std::size_t n) {    
    if(memPtr+offset == p+n)
      offset -= n;
  }
  
  template<typename U, typename ...Args>
  void construct(U *p, Args &&...args) {    
    new(p) U(std::forward<Args>(args)...);
  }  
  
  void destroy(T *p) {
    p->~T();
  }    
  
  template<typename U>
  struct rebind {
      using other = reserveAllocator<U, totalSize>;
  };
  
private:
  std::size_t offset;
  T* memPtr;  
};