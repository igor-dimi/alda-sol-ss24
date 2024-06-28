#include "list.hpp"
#include "testing.hpp"
#include <sstream>

bool test_push_front() {
  List lst;

  fail_unless(lst.empty());

  for (int i = 0; i < 10; ++i) {
    fail_unless_eq(lst.size(), static_cast<size_t>(i));
    lst.push_front(i);
  }

  fail_if(lst.empty());

  for (int i = 10; i; --i) {
    fail_unless_eq(lst.size(), static_cast<size_t>(i));
    auto popped = lst.pop_front();
    fail_unless_eq(popped->get_value(), i - 1);
  }

  fail_unless(lst.empty());

  return true;
}

// Aufgabe 2: tests for push_back
// general push_back functionality:
bool test_push_back() {
  List l;
  fail_unless(l.empty());

  for (int i = 0; i < 10; ++i) {
    fail_unless_eq(l.size(), static_cast<size_t>(i));
    l.push_back(i);
  }
  // here l == [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  fail_if(l.empty());

  for (int i = 0; i < 10; i++) {
    fail_unless_eq(l.size(), static_cast<size_t>(10 - i));
    auto popped = l.pop_front();
    fail_unless_eq(popped->get_value(), i);
  }

  return true;
}

// testing correctness of push_back() with regards to last element
bool test_push_back_last_1()
{
  List l;
  fail_unless(l.empty());

  l.push_front(1);
  l.push_back(2);

  auto popped = l.pop_front();
  fail_unless_eq(popped->get_value(), 1);
  popped = l.pop_front();
  fail_unless_eq(popped->get_value(), 2);

  return true;

}

bool test_push_back_last_2()
{
  List l;
  fail_unless(l.empty());

  l.push_front(1);
  l.pop_front();
  l.push_back(3);

  auto popped = l.pop_front();
  fail_unless_eq(popped->get_value(), 3);

  return true;

}

// aufgabe 3
// nothing goes wrong (in both versions) if two lits are concatenated only once
bool test_concat_once()
{
  List l1, l2;
  l1.push_back(1);
  l2.push_back(2);
  l1.concat(l2);

  fail_unless(l2.empty());

  std::stringstream ss;
  ss << l1;

  fail_unless_eq(ss.str(), "[1, 2]");
  return true;
}

// concatenating more than once leads to a bug in the original version
// comment out our correction in order for this test to fail:
bool test_concat_twice()
{
  List l1, l2, l3;
  l1.push_back(1);
  l2.push_back(2);
  l3.push_back(3);

  l1.concat(l2);
  l1.concat(l3);

  fail_unless(l2.empty());
  fail_unless(l3.empty());


  std::stringstream ss;
  ss << l1;

  // our correction removes the bug:
  // in the original wrong version the last pointer of the list
  // wasn't updated to the last pointer of the other (concatenated) list
  // this causes repeated concatenations to be applied (wrongly) after original last item
  // thus loosing in-between concatenations
  fail_unless_eq(ss.str(), "[1, 2, 3]");

  return true;
}

// This test detects the bug in the original version
// but will fail in our corrected version.
// comment out our correction and comment in this test
// in case you would like to see the bug
// bool test_concat_twice_bug()
// {
//   List l1, l2, l3;
//   l1.push_back(1);
//   l2.push_back(2);
//   l3.push_back(3);

//   l1.concat(l2);
//   l1.concat(l3);

//   fail_unless(l2.empty());
//   fail_unless(l3.empty());


//   std::stringstream ss;
//   ss << l1;

//   // in the original wrong version the last pointer the list
//   // wasn't updated to point to the last pointer to the other (concatenated) list
//   // this leads repeated concatenations being applied (wrongly) after original last item
//   // thus loosing in between concatenations
//   fail_unless_eq(ss.str(), "[1, 3]"); // 2 is lost

//   return true;
// }


// Aufgabe 4
// testing move_into_if

bool test_move_into_if_even() 
{
  List l1, l2;
  for (int i = 0; i < 10; i++) {
    l1.push_back(i);
  }

  auto is_even = [] (const List::Value& val) {return (val % 2 == 0);};

  l1.move_into_if(l2, is_even);

  std::cout << "l1 has odd elements: " << l1 << std::endl;
  std::cout << "l2 has even elements: " << l2 << std::endl;

  // testing if all elements in l1 are odd
  while (!l1.empty()) {
    auto popped = l1.pop_front();
    fail_if(popped->get_value() % 2 == 0);
  }

  // testing wether all elements in l2 are even
  while (!l2.empty()) {
    auto popped = l2.pop_front();
    fail_unless(popped->get_value() % 2 == 0);
  }


  return true;
}

// testing for predicate "greater than 5"
bool test_move_into_if_greater_5()
{
  List l1, l2;
  for (int i = 0; i < 10; i++) {
    l1.push_back(i);
  }

  auto is_greater_5 = [] (const List::Value& val) {return (val > 5);};

  l1.move_into_if(l2, is_greater_5);

  std::cout << "elements of l1 are not greater than 5: " << l1 << std::endl;
  std::cout << "elements of l2 are greater than 5: " << l2 << std::endl;

  // testing if all elements in l1 not greater than 5
  while (!l1.empty()) {
    auto popped = l1.pop_front();
    fail_if(popped->get_value() > 5);
  }

  // testing wether all elements in l2 are greater than 5
  while (!l2.empty()) {
    auto popped = l2.pop_front();
    fail_unless(popped->get_value() > 5);
  }
  return true;
}

// testing for correct appending
bool test_move_into_append()
{
  List l1;
  List l2;

  l1.push_back(2);
  l1.push_back(3); // l1 == [2, 3]
  l2.push_back(1); // l2 == [1]

  auto is_2_or_3 = [] (const List::Value& val) {return (val == 2 || val == 3);};

  l1.move_into_if(l2, is_2_or_3);
  std::cout << "l1: " << l1 << std::endl;
  std::cout << "l2: " << l2 << std::endl;
  // now l1 == [] && l2 == [1, 2, 3] must hold, we test:



  std::stringstream ss1, ss2;

  ss1 << l1;
  ss2 << l2;

  fail_unless_eq(ss1.str(), "[]");
  fail_unless_eq(ss2.str(), "[1, 2, 3]");

  return true;


}

bool test_foreach() {
  List lst;

  fail_unless(lst.empty());

  int ref_sum = 0;

  for (int i = 0; i < 10; ++i) {
    fail_unless_eq(lst.size(), static_cast<size_t>(i));
    lst.push_front(i);
    ref_sum += i * i;
  }

  int foreach_sum = 0;
  lst.foreach ([&foreach_sum](int i) { foreach_sum += i * i; });

  fail_unless_eq(foreach_sum, ref_sum);

  return true;
}

bool test_ostream() {
  List lst;
  lst.push_front(1);
  lst.push_front(2);

  std::stringstream ss;
  ss << lst;

  fail_unless_eq(ss.str(), "[2, 1]");
  return true;
}

bool test_destruct() {
  List lst;

  for (int i = 0; i < 1000; ++i) {
    lst.push_front(i);
  }

  return true;
}





int main() {
  run_test(test_push_front);
  run_test(test_foreach);
  run_test(test_ostream);
  run_test(test_destruct);

  //Aufgabe 2
  run_test(test_push_back);
  run_test(test_push_back_last_1);
  run_test(test_push_back_last_2);

  // Aufgabe 3
  run_test(test_concat_once);
  run_test(test_concat_twice); // passes in our corrected version, fails in original buggy version.

  // if you comment out our correction in concat() (reverting to original version)
  // and comment in this test, this test will pass:
  // run_test(test_concat_twice_bug);

  // Aufgabe 4
  run_test(test_move_into_if_even);
  run_test(test_move_into_if_greater_5);
  run_test(test_move_into_append);




  return 0;
}
