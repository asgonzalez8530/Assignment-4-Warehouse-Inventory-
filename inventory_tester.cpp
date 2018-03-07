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
#include "warehouse.h"

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

// warehouse class tests
bool test_warehouse_constructor();
bool test_warehouse_copy_constructor();
bool test_warehouse_assignment_operator();
bool test_warehouse_get_name();
bool test_warehouse_add_inventory();
bool test_warehouse_remove_inventory();
bool test_warehouse_update_day();
bool test_warehouse_remove_expired_inventory();

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
  
  /*
  // test warehouse class
  std::cout << "Test warehouse class" << std::endl << std::endl;
  
  print_test_result("test warehouse constructor", 
    test_warehouse_constructor());
  print_test_result("test warehouse copy constructor",
    bool test_warehouse_copy_constructor());
  print_test_result("test warehouse assignment operator",
    test_warehouse_assignment_operator());
  print_test_result("test warehouse get_name",
    test_warehouse_get_name());
  print_test_result("test warehouse add_inventory",
    test_warehouse_add_inventory());
  print_test_result("test warehouse remove_inventory",
    test_warehouse_remove_inventory());
  print_test_result("test warehouse update_day",
    test_warehouse_update_day());
  print_test_result("test warehouse remove_expired_inventory",    
    test_warehouse_remove_expired_inventory());
  */
  
  std::cout << std::endl;
    
  
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
  // this will turn the text green
  std::string green = "\033[1;32m";
  // this will turn the text red
  std::string red = "\033[1;31m";
  // this will reset the text to default
  std::string regular = "\033[0m";
  
  std::string pass = "passed";
  std::string fail = "failed";
  
  std::cout << test_name << " : ";
  if (result)
  {
    std::cout <<  green; // change green
    std::cout << pass;
  }
  else
  {
    std::cout <<  red; // change red
    std::cout << fail;
  }
  
  std::cout << regular << std::endl; // reset color and end line

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

/**
 * tests the warehouse class constructor
 */
bool test_warehouse_constructor()
{
  std::string name = "Albuquerque";
  
  // call default constructor
  warehouse costco(name);
  
  // check state of warehouse after construction
  std::string ware_name = costco.get_name();
  inventory ware_inventory = costco.get_inventory();
  int inventory_size = ware_inventory.size();
  
  // check that the getters returned expected values
  bool test_result = true;
  test_result = test_result && name == ware_name;
  test_result = test_result && inventory_size == 0;
  
  return test_result;
}

/**
 * tests the warehouse class copy constructor
 */
bool test_warehouse_copy_constructor()
{
  std::string name = "Albuquerque";
  
  // call default constructor
  warehouse costco(name);
  // call copy constructor
  warehouse samsclub(costco);
  
  // check state of warehouse after construction
  std::string ware_name = samsclub.get_name();
  inventory ware_inventory = samsclub.get_inventory();
  int inventory_size = ware_inventory.size();
  
  // check that the getters returned expected values
  bool test_result = true;
  test_result = test_result && name == ware_name;
  test_result = test_result && inventory_size == 0;
  
  return test_result;
}

/**
 * tests the warehouse class assignment operator
 */
bool test_warehouse_assignment_operator()
{
  std::string name = "Albuquerque";
  
  // call default constructor
  warehouse costco(name);
  // assign into costco into new warehouse
  warehouse samsclub = costco;
  
  // check state of warehouse after construction
  std::string ware_name = samsclub.get_name();
  inventory ware_inventory = samsclub.get_inventory();
  int inventory_size = ware_inventory.size();
  
  // check that the getters returned expected values
  bool test_result = true;
  test_result = test_result && name == ware_name;
  test_result = test_result && inventory_size == 0;
  
  return test_result;
}

/**
 * tests the get_name function of the warehouse class
 */
bool test_warehouse_get_name()
{
  std::string name1 = "Albuquerque";
  std::string name2 = "Magic Kingdom";
  
  // call default constructor
  warehouse costco(name1);
  warehouse samsclub(name2);
  
  // call the function on both objects
  std::string ware_name1 = costco.get_name();
  std::string ware_name2 = samsclub.get_name();
  
  // check that the getters returned expected values
  bool test_result = true;
  test_result = test_result && name1 == ware_name1;
  test_result = test_result && name2 == ware_name2;
  
  return test_result;
}

/**
 * tests the add_inventory method of the warehouse class
 */
bool test_warehouse_add_inventory()
{
  warehouse costco("Albuquerque");
  
  std::string upc1 = "0123456789";
  std::string upc2 = "9876543210";
  
  int quantity = 10;
  int shelf_life = 2;
  
  // add items to warehouse
  costco.add_inventory(upc1, quantity, shelf_life);
  costco.add_inventory(upc1, quantity, shelf_life + 1);
  costco.add_inventory(upc2, quantity, shelf_life);
  costco.add_inventory(upc2, quantity + 1, shelf_life);
  
  
  inventory inv = costco.get_inventory();
  int size = inv.size();
  std::list<item_status> status1 = inv.at(upc1);
  std::list<item_status> status2 = inv.at(upc2);
  
  int status_size1 = status1.size();
  int status_size2 = status2.size();
  
  // check that the inventory is as expected
  bool test_result = true;
  test_result = test_result && size == 2;
  test_result = test_result && inv.count(upc1);
  test_result = test_result && inv.count(upc2);
  test_result = test_result && status_size1 == 2;
  test_result = test_result && status_size2 == 1;
  
  return test_result;
  
}

/**
 * tests the remove_inventory method of the warehouse class
 */
bool test_warehouse_remove_inventory()
{
  warehouse costco("Albuquerque");
  
  std::string upc1 = "0123456789";
  std::string upc2 = "9876543210";
  
  int quantity = 10;
  int shelf_life = 2;
  
  // add items to warehouse
  costco.add_inventory(upc1, quantity, shelf_life);
  costco.add_inventory(upc1, quantity, shelf_life + 1);
  costco.add_inventory(upc2, quantity, shelf_life);
  costco.add_inventory(upc2, quantity + 1, shelf_life);
  
  // there should now be 20 of upc1 with two different shelf lifes
  // there should now be 21 of upc2 with one shelf life
  
  // should be able to remove all 15 items, there will be nothing with a 
  // shelf_life of 2.
  int removed_from_upc1 = costco.remove_inventory(upc1, 15);
  
  // shouldn't be able to remove 25 items from upc2, function will report 
  // that 21 items were removed.
  int removed_from_upc2 = costco.remove_inventory(upc2, 25);
  
  // inventory now only has one item type in it
  inventory inv = costco.get_inventory();
  int size = inv.size(); // should be size 1
  std::list<item_status> status1 = inv.at(upc1);
  
  int status_size1 = status1.size(); // should be size 1 group of items
  
  // check that the inventory is as expected
  bool test_result = true;
  test_result = test_result && size == 1;
  test_result = test_result && inv.count(upc1); // should return 1
  test_result = test_result && !inv.count(upc2); // should return 0
  test_result = test_result && status_size1 == 1; // one list of upc1
  test_result = test_result && removed_from_upc1 == 15;
  test_result = test_result && removed_from_upc2 == 21;
  
  return test_result;
  
}

/**
 * tests the update_daymethod of the warehouse class
 */
bool test_warehouse_update_day()
{
  // this method updates the day then removes expired inventory and checks the
  // state afterwards. So it tests this method well. 
  return test_warehouse_remove_expired_inventory();
  
}

/**
 * tests the remove_expired_inventory method of the warehouse class
 */
bool test_warehouse_remove_expired_inventory()
{
  warehouse costco("Albuquerque");
  
  std::string upc1 = "0123456789";
  std::string upc2 = "9876543210";
  
  int quantity = 10;
  // add items to warehouse
  costco.add_inventory(upc1, quantity, 1);
  costco.add_inventory(upc1, quantity, 2);
  costco.add_inventory(upc2, quantity, 3);
  
  costco.update_day();
  costco.remove_expired_inventory();
  
  // there should now be 10 of upc1 with one shelf life
  // there should now be 10 of upc2 with one shelf life
  
  // should return 10
  int removed_from_upc1 = costco.remove_inventory(upc1, 15);
  // should return 10
  int removed_from_upc2 = costco.remove_inventory(upc2, 25);
  
  bool test_result = true;
  test_result = test_result && removed_from_upc1 == 10;
  test_result = test_result && removed_from_upc2 == 10;
  
  return test_result;
  
}
