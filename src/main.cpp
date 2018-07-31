#include <iostream>
#include "version.h"

int main(int argc, char** argv)
{
  std::cout<<"Hello, World!\n";
  std::cout<<"\t"<<gGIT_VERSION<<"\n";
  std::cout<<std::endl;
	return 0;
}
