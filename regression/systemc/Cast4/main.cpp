#include <cassert>

class mysuperclass
{
  int x;
public:
  mysuperclass(int _x) : x(_x) {}
  operator int () { return x+1; }  
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
  int z = a; //(int)(mysuperclass)
  
  assert(y+1 == z);

  return 0;
}

