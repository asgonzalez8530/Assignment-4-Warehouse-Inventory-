/**
* Author: Aaron Bellis and  Anastasia Gonzalez
* UID: u0981638 and u0985898
* Date: 3/8/18
* Class: CS 3505
* Purpose: Defines testing functions for the inventory_report program
*   as specified in cs3505 assignment4 
* How to run: Can be built by using the tester rule in the provided Makefile
*   and running the tester executable. 
*/

#include "food_item.h"
#include <iostream>

using namespace inventory_report;

/************* declarations for methods defined below main method *************/

// a method for printing test results
// test methods must return a bool in order to use print_test_result function
void print_test_result(const std::string & test_name, bool result);

// food_item class tests
bool test_food_item_class();
bool test_food_item_class_copy_constructor();
bool test_food_item_assignment_operator();

/**
* Main class for inventory_report program testing
*/
int main(int argc, char** argv)
{
  // test food_item class
  std::cout << "Test food_item class" << std::endl << std::endl;
  
  print_test_result("test food_item class", test_food_item_class());
  print_test_result("test food_item copy constructor", 
    test_food_item_class_copy_constructor());
  print_test_result("test food_item operator=", 
    test_food_item_assignment_operator());
  
  std::cout << std::endl;
    
  // test warehouse class
  //std::cout << "Test warehouse class" << std::endl << std::endl;
}

/**
* Takes a string test_name and a bool result and prints the value of test_name 
* followed by " : " then "passed" if result is true, or "false" if result is
* false on its own line.
* 
* For example, if the test name is "example test" and result was true, the 
* following string would be printed to the console
* 
*               "example test : passed"
*/
void print_test_result(const std::string & test_name, bool result)
{
  std::string result_string = result ? "passed" : "failed";
  std::cout << test_name << " : ";
  std::cout << result_string << std::endl;
}

/**
* Tests the food item class using the default constructor
*/
bool test_food_item_class()
{
  std::string name = "froot loops";
  std::string upc_code = "0123456789";
  int shelf_life = 730;
  
  // call constructor
  food_item item(name, upc_code, shelf_life);
  
  // check state of item after construction
  std::string item_name = item.get_name();
  std::string item_upc = item.get_upc_code();
  int item_shelf_life = item.get_shelf_life();
  
  // check that that getters returned expected values
  bool test_result = true;
  test_result = test_result && name == item_name;
  test_result = test_result && upc_code == item_upc;
  test_result = test_result && shelf_life == item_shelf_life;
  
  return test_result;
}

/**
* Tests the food item class' copy constructor
*/
bool test_food_item_class_copy_constructor()
{
  std::string name = "froot loops";
  std::string upc_code = "0123456789";
  int shelf_life = 730;
  
  // call constructor
  food_item item(name, upc_code, shelf_life);
  food_item copy_item(item);
  
  // check state of item after construction
  std::string item_name = copy_item.get_name();
  std::string item_upc = copy_item.get_upc_code();
  int item_shelf_life = copy_item.get_shelf_life();
  
  // check that that getters returned expected values
  bool test_result = true;
  test_result = test_result && name == item_name;
  test_result = test_result && upc_code == item_upc;
  test_result = test_result && shelf_life == item_shelf_life;
  
  return test_result;
}

/**
* Tests the food item class assignment operator
*/
bool test_food_item_assignment_operator()
{
  std::string name = "froot loops";
  std::string upc_code = "0123456789";
  int shelf_life = 730;
  
  // call constructor
  food_item item(name, upc_code, shelf_life);
  food_item copy_item = item;
  
  // check state of item after construction
  std::string item_name = copy_item.get_name();
  std::string item_upc = copy_item.get_upc_code();
  int item_shelf_life = copy_item.get_shelf_life();
  
  // check that that getters returned expected values
  bool test_result = true;
  test_result = test_result && name == item_name;
  test_result = test_result && upc_code == item_upc;
  test_result = test_result && shelf_life == item_shelf_life;
  
  return test_result;
}
