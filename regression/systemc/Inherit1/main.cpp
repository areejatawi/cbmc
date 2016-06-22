#include <cassert>

class mysuperclass
{
  int x;
public:
  mysuperclass(int _x) : x(_x) {}
  int get() { return x; }  
};

class myclass : public mysuperclass
{
public:
  myclass(int _x) : mysuperclass(_x) {}
};


int main(int argc, char *argv[]) 
{
  int y;
  myclass a(y);
  int z = a.get();
  
  assert(y == z);

  return 0;
}

