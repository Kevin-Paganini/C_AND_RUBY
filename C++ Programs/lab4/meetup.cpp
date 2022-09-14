// meetup.cpp: finds perfect matches in two pools of people
// Robert W. Hasker, 2021

#include "pool.h"
#include "pool.cpp"
#include <iostream>
#include <string>

using namespace std;

void smoke_test();

int main() {
  smoke_test();

  Pool *pool1 = new Pool;
  cout << "Enter the first names of the people in the first pool:" << endl;
  pool1->readNames();
  cout << "Enter the first names of the people in the second pool:" << endl;
  Pool *pool2 = new Pool;
  pool2->readNames();
  cout << endl;

  if ( pool1->empty() && pool2->empty() )
    cout << "Both pools are empty." << endl;
  else if ( pool1->empty() )
    cout << "First pool is empty." << endl;
  else if ( pool2->empty() )
    cout << "Second pool is empty." << endl;

  pool1->printMatches(pool2);
  return 0;
}

// a very simple test that ensures we can create a pool, add a name,
//   and that nothing is printed when we find matches to that name
void smoke_test() {
  Pool *test = new Pool;
  test->add("sue");
  // all of the following should print nothing
  test->printMatches("tom");
  test->printMatches("sue");
  test->printMatches(test);
}

