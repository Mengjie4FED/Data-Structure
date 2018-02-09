#include "list.h"
#include <iostream>

int main() {
  List<int> list1;
  for (unsigned i = 0; i < 10; i+=1) { list1.insertBack(i); }
  /*
  list1.insertBack(6);
  list1.insertBack(1);
  list1.insertBack(5);
  list1.insertBack(3);
  list1.insertBack(8);
  list1.insertBack(4);
  list1.insertBack(7);
  list1.insertBack(2);
  list1.insertBack(9);
  list1.print(std::cout);

  list1.sort();
  list1.print(std::cout);
  */
  List<int> list2;
  //for (unsigned i = 1; i < 10; i+=2) { list2.insertBack(i); }
  list2 = list1.split(5);
  list2.print(std::cout);

  list1.mergeWith(list2);

  list1.print(std::cout);
  list2.print(std::cout);
  cout << endl;

  return 0;
}
