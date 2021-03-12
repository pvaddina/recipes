#include <iostream>
#include "bt.h"

void Test4() { std::cout << "Print backtrace" << std::endl; print_stacktrace(); }
void Test3() { Test4(); }
void Test2() { Test3(); }
void Test1() { Test2(); }


int main()
{
  Test1();
  return 0;
}
