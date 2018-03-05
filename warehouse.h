/**
* Author: Aaron Bellis and  Anastasia Gonzalez
* UID: u0981638 and u0985898
* Date: 3/8/18
* Class: CS 3505
* Purpose: Header file for warehouse class CS3505 C++ Assignment 4
*   Contains the warehouse class declaration.
* How to run: must be used in conjunction with warehouse.cpp
*/

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>

namespace inventory_report
{
  
  /**
  * warehouse class represents individual food warehouses and provides
  * information about its name and inventory
  */
  class warehouse
  {
    // a string of words that is the city where the warehouse is located
    std::string warehouse_name;
    
    // contains this warehouse's inventory 
    public:
    
      /**
      * Warehouse constructor takes a name as string of words, which is the city
      * in which this warehouse is located. 
      * 
      * The warehouse name provided uniquely identifies this warehouse.
      */
      warehouse(const std::string & name);
      
      /**
      * Copy constructor for the warehouse class. Takes a warehouse other, and
      * constructs a new warehouse object using its contents.
      */
      warehouse(const warehouse & other);
      
      /**
      * Takes a string of number characters of positive length as upc which 
      * represents the type of item to be added to this warehouses inventory, 
      * the quantity of items to be added to the inventory, and that item's 
      * shelf life and adds those items to this warehouses inventory.
      */
      void add_inventory(const std::string & upc, int quantity, int shelf_life);
      
      
  };
}

#endif
