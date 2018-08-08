#include <iostream>
#include <map>
#include <cmath>
#include "allocator.h"
#include "container.h"

template <class Cont, class Lambda>
void fillContainer(Cont& c, Lambda lamb){
  for(int i=0; i< 10; ++i)
    lamb(c, i);
}

template<typename... Args>
std::ostream& operator<<(std::ostream& os, const std::map<Args...> &m){
	for(const auto& p: m)
			os << p.first << ' ' << p.second << '\n';
	return os;
}

int main(int argc, char** argv)
{
  auto setMap = [](auto& cont, const auto& i) {cont[i] = std::tgamma(i+1);};
    
//Default Allocator
  std::map<int, int> md;
  fillContainer(md, setMap);		

  std::cout<<"\nStandart Container: Reserve Allocator\n";
  std::map<int, int, std::less<int>, reserveAllocator<int,10> > mr;
  fillContainer(mr, setMap);
  std::cout << mr;
		
  
  auto setCont = [](auto& container, const auto& i) {container.pushFront(i);};
              
//Cuastom container: default allocator\n";
  Container<int> con1;       
  fillContainer(con1, setCont);    

  std::cout << "\nCuastom container: Reserve Allocator\n";
  Container<int, reserveAllocator<int,10> > con2;
  fillContainer(con2, setCont);    
  std::cout << con2;
	
	return 0;
}
