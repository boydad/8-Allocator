#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include "version.h"
#include "allocator.h"
#include "container.h"

template <class T>
void fillMap(T& m){
	for(int i=0; i< 10; ++i)
			m[i] = std::tgamma(i+1);
}

template <class Cont, class Lambda>
void fillContainer(Cont& c, Lambda lamb){
  for(int i=0; i< 10; ++i)
    lamb(c, i);
}

template<typename... Args>
std::ostream& operator<<(std::ostream& os, const std::map<Args...> &m){
	for(const auto& p: m)
			os<<p.first<<' '<<p.second<<'\n';
	return os;
}

int main(int argc, char** argv)
{
  auto setMap = [](auto& cont, const auto& i) {cont[i] = std::tgamma(i+1);};
    
//  std::cout<<"\nDefault Allocator\n";
  std::map<int, int> md;
  fillContainer(md, setMap);
//  std::cout<<md;		

  std::cout<<"\nReserve Allocator\n";
  std::map<int, int, std::less<int>, reserveAllocator<int,10> > mr;
  fillContainer(mr, setMap);
  std::cout<<mr;
		
  
  auto setCont = [](auto& container, const auto& i) {container.pushBack(i);};
              
//  std::cout<<"\nContainer: default allocator\n";
  Container<int> con1;            
  fillContainer(con1, setCont);    
//  std::cout<<con1;

  std::cout<<"\nContainer: custom allocator\n";
  Container<int, reserveAllocator<int,10> > con2;
  fillContainer(con2, setCont);    
  std::cout<<con2;
//  
	return 0;
}
