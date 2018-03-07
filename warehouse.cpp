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
    warehouse_name = name;
    day = 0;
    my_inventory = new inventory();
  }
      
  /**
   * Copy constructor for the warehouse class. Takes a warehouse other, and
   * constructs a new warehouse object using its contents.
   */
  warehouse::warehouse(const warehouse & other)
  {
    warehouse_name = "";
    day = 0;
    my_inventory = NULL;
    
    *this = other;

  }
    
  /**
   * warehouse class default destructor
   *
   * Guarantees that the resources used by this warehouse object will be
   * freed.
   */
  warehouse::~warehouse()
  {
    clean();
  }

  /**
   * Returns a reference to the name of this warehouse.
   */
  const std::string & warehouse::get_name() const
  {
    return warehouse_name;
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
    // get the items that correlate to the inputted upc
    std::list <item_status> items = my_inventory->at(upc);
    // if the list stored in the inventory map is empty then state that we were
    // unable to remove any items by returning 0
    if (items.empty())
    {
      return 0;
    }
    // we pull out the first item
    else
    {
      remove_inventory(items, quantity);
    }
  }
  
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
  int warehouse::remove_inventory(std::list<item_status>  & items, int quantity)
  {
      // base cases:
      // 1) quantity is zero
      if (quantity == 0)
      {
        return 0;
      }
      // 2) reached the end of the list
      if (items.empty())
      {
        // the order can not be fulfilled
        return 0;
      }
      
      // look at the first item in the list (oldest item in inventory)
      item_status oldest_item = *items.begin();
      // if the quantity of the first item is greater than the quantity...
      if (oldest_item.quantity > quantity)
      {
        // ...then we decrement the items quantity appropriate
        oldest_item.quantity -= quantity;
        // whole order was fulfilled so we return quantity
        return quantity;
      }
      // else if the quantity of the first item is equal to the quantity...
      else if (oldest_item.quantity == quantity)
      {
        // ...then we remove the item from the inventory 
        items.pop_front();
        // whole order was fulfilled so we return the quantity
        return quantity;
      }
      // else the quantity of the first item is less than the quantity...
      else
      {
        // ...we determine how many orders we are able to fill
        int orders_filled = oldest_item.quantity;
        // remove the oldest item from the inventory because the quantity is now zero
        items.pop_front();
        // and ask for the amount of orders left to fill on the updated list
        return orders_filled + remove_inventory(items, quantity - orders_filled);
      }
  }

  /**
   * Increments the day counter of the warehouse
   */
  void warehouse::update_day()
  {
    day++;
  }

  /**
   * Removes all items in inventory with which expire this day. 
   */
  void warehouse::remove_expired_inventory()
  {
  
  }

  /**
   * Returns a reference to the inventory contained by this warehouse
   */
  const inventory & warehouse::get_inventory() const
  {
    return *my_inventory;
  }

  /**
   * Overloaded assignment operator. Assigns the contents of the warehouse
   * object rhs into the object to the left of the operator.
   */
  warehouse & warehouse::operator= (const warehouse & rhs)
  {
    if (this == &rhs)
    {
      return *this;
    }
    
    clean ();
    
    // copy rhs contents
    this->warehouse_name = rhs.warehouse_name;
    this->day = rhs.day;
    this->my_inventory = new inventory(*rhs.my_inventory);
    
    return *this;
    
  }
      
  /**
   * Releases any memory that was allocated by this object
   */
  void warehouse::clean()
  {
    
    // free my_inventory
    if (my_inventory != NULL)
    {
      delete my_inventory;
    }
    // make sure we aren't holding onto a reference to deleted inventory
    my_inventory = NULL;
    warehouse_name = "";
    day = 0;
    
  }
}
