#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testExtra();
    testAll();
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}