/**
* Author: Aaron Bellis and  Anastasia Gonzalez
* UID: u0981638 and u0985898
* Date: 3/8/18
* Class: CS 3505
* Purpose: CPP file for warehouse class CS3505 C++ Assignment 4
*   Contains the warehouse class member definitions.
* How to run: must be used in conjunction with warehouse.h
*/

#include "warehouse.h"

namespace inventory_report
{

  /**
   * Warehouse constructor takes a name as string of words, which is the city
   * in which this warehouse is located. 
   * 
   * The warehouse name provided uniquely identifies this warehouse.
   */
  warehouse::warehouse(const std::string & name)
  {
  
  }
      
  /**
   * Copy constructor for the warehouse class. Takes a warehouse other, and
   * constructs a new warehouse object using its contents.
   */
  warehouse::warehouse(const warehouse & other)
  {
  
  }
    
  /**
   * warehouse class default destructor
   *
   * Guarantees that the resources used by this warehouse object will be
   * freed.
   */
  // don't know if we need to define our own destructor for this class
  // warehouse::~warehouse()
  // {
  
  // }

  /**
   * Returns a reference to the name of this warehouse.
   */
  const std::string & warehouse::get_name() const
  {
  
  }

  /**
   * Takes a string of number characters of positive length as upc which 
   * represents the type of item to be added to this warehouses inventory, 
   * the quantity of items to be added to the inventory, and that item's 
   * shelf life and adds those items to this warehouses inventory.
   */
  void warehouse::add_inventory(const std::string & upc, int quantity, int shelf_life)
  {
  
  }
      
  /**
   * Takes a string of number characters of positive length as upc which
   * represents the type of item to be removed, along with the quantity to 
   * be removed. If the number of items with upc is greater than  quantity 
   * removes quantity items with upc from warehouse inventory, removing the
   * items with the lowest shelf_life first. If the number of items with upc
   * is less than or equal to quantity, then all items with upc are removed
   * from inventory. 
   * 
   * Returns the number of items removed from inventory.
   */
  int warehouse::remove_inventory(const std::string & upc, int quantity)
  {
  
  }

  /**
   * Reduces the shelf_life of all items in inventory by 1
   */
  void warehouse::update_shelf_life()
  {
  
  }

  /**
   * Removes all items in inventory with a shelf_life of 0. 
   */
  void warehouse::remove_expired_inventory()
  {
  
  }

  /**
   * Returns a reference to the inventory contained by this warehouse
   */
  const inventory & warehouse::get_inventory() const
  {
  
  }

  /**
   * Overloaded assignment operator. Assigns the contents of the warehouse
   * object rhs into the object to the left of the operator.
   */
  warehouse & warehouse::operator= (const warehouse & rhs)
  {
  
  }
      
  /**
   * Releases any memory that was allocated by this object
   */
  void warehouse::clean()
  {
  
  }
}
