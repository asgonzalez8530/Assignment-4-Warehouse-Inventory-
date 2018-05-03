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
#include <map>
#include <list>
#include <set>


namespace inventory_report
{
  
  /**
   * represents the status of an item in a warehouse inventory 
   */
  struct item_status 
  {
    long long quantity;
    int shelf_life;
    int death_day;
  };
  
  /**
   * maps a upc to a doubly linked list of items which expire on the same day
   */
  typedef std::map< std::string, std::list<item_status> > inventory;
  
  /**
   * warehouse class represents individual food warehouses and provides
   * information about its name and inventory
   */
  class warehouse
  {
    // a string of words that is the city where the warehouse is located
    std::string warehouse_name;
    
    // keeps track of number of days since report began
    int day;
    
    // contains this warehouse's inventory 
    inventory * my_inventory;
    

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
       * warehouse class default destructor
       *
       * Guarantees that the resources used by this warehouse object will be
       * freed.
       */
      ~warehouse();

      /**
       * Returns a reference to the name of this warehouse.
       */
      const std::string & get_name() const;

      /**
       * Takes a string of number characters of positive length as upc which 
       * represents the type of item to be added to this warehouses inventory, 
       * the quantity of items to be added to the inventory, and that item's 
       * shelf life and adds those items to this warehouses inventory.
       */
      void add_inventory(const std::string & upc, int quantity, int shelf_life);
      
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
      int remove_inventory(const std::string & upc, int quantity);

      /**
       * Increments the day counter of the warehouse
       */
      void update_day();

      /**
       * Removes all items in inventory with which expire this day. 
       */
      void remove_expired_inventory();

      /**
       * Returns a reference to the inventory contained by this warehouse
       */
      std::set<std::string> get_inventory() const;

      /**
       * Overloaded assignment operator. Assigns the contents of the warehouse
       * object rhs into the object to the left of the operator.
       */
      warehouse & operator= (const warehouse & rhs);
      
    private:
      
      /**
       * Releases any memory that was allocated by this object
       */
      void clean();
      
      /**
       * Takes a list of items and the quantity to be removed. If the first item in
       * the list has a quantity greater than or equal to the quantity to be 
       * removed from warehouse inventory, removing the items with the lowest 
       * shelf_life first. If the first item in the list is less than or equal to 
       * the quantity, then the first item is removed and this method is 
       * recursively on the amount of orders left to fill and the list of items left. 
       * 
       * Returns the number of items removed from inventory.
       */
      int remove_inventory(std::list<item_status> & items, int quantity);
  };
}

#endif
