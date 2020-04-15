#include "signal.h"
#include <iostream>
#include <string>

namespace T1
{
  void InitVariations()
  {
    S::Signal<void()> s;
  }
}

namespace T2
{
  void Foo(int a, std::string b)
  {
    std::cout << "In Foo: a=" << a << ", b=" << b << std::endl;
  }

  void Coo(int a, std::string b)
  {
    std::cout << "In Coo: a=" << a << ", b=" << b << std::endl;
  }

  struct Goo
  {
    void Exec(int a, std::string b)
    {
      std::cout << "In Goo::Exec(): a=" << a << ", b=" << b << std::endl;
    }
  };

  void ConnectionTests()
  {
    S::Signal<void(int,std::string)> s;
    auto fooConn = s.Connect(Foo);
    auto cooConn = s.Connect(Coo);

    Goo g;
    s.Connect([&](int a, std::string b) -> void { g.Exec(a, b); });

    s.Connect(std::bind(&Goo::Exec, g, std::placeholders::_1, std::placeholders::_2));

    s(1, std::string("Number 1"));
  }
}

int main()
{
  T1::InitVariations();
  T2::ConnectionTests();
}

