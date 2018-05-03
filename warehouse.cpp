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
    // check if this upc exists in inventory
    if(my_inventory->count(upc)) 
    {
      // it exists so lets look at the end and see if we can just add it to that group
      std::list<item_status> * status_list = &(my_inventory->at(upc));
      item_status & last_status = status_list->back();
      
      // if these items will expire on the same day
      if (last_status.death_day == shelf_life + day)
      {
	      // ... add the quantity to this status
	      last_status.quantity += static_cast<long long> (quantity);
      }
      else
      {
	      // add a new item_status to the back of the list
	      item_status status = { static_cast<long long>(quantity), shelf_life, shelf_life + day};
	      status_list -> push_back(status);
      }
    }
    else
    {
      // upc is not in inventory, need to add it
      // create new list
      std::list<item_status> status_list = std::list<item_status>();
      
      // create status with given info
      item_status status = {static_cast<long long>(quantity), shelf_life, shelf_life +day};
      
      // place it in the list
      status_list.push_back(status);
      // place list in inventory with desegnated upc
      my_inventory->insert(std::pair< std::string, std::list<item_status> > (upc, status_list));
    }

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
    std::list <item_status> * items = NULL;
    
    // safely used map::at(key)
    if (my_inventory->count(upc))
    {
      items = &my_inventory->at(upc);
    }
    // if the list stored in the inventory map is empty then state that we were
    // unable to remove any items by returning 0
    if (items == NULL || items->empty())
    {
      return 0;
    }
    // we pull out the first item
    else
    {
      int amount_removed = remove_inventory(*items, quantity);
      // clean up inventory 
      if (items->empty())
      {
        my_inventory->erase(upc);
      }
      
      return amount_removed;
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
   * Removes all items in inventory which expire this day. 
   */
  void warehouse::remove_expired_inventory()
  {
    // get a pointer that points to the beginning and end
    inventory::iterator inv = my_inventory->begin();
    inventory::iterator end = my_inventory->end();

    // this is a list of upc's for empty lists, need to be cleaned from inventory
    std::list<std::string> cleanup;

    for (inv; inv != end; inv++)
    {
      // the list is actually the second item of a pair type
      // get the address of the list so we don't have to copy the whole list
      std::list<item_status> * status_list = &(inv->second);
      // look to the first item of each list
      std::list<item_status>::iterator status = status_list->begin();
      // remove it if its expired
      if (status->death_day == day)
      {
	      status_list->pop_front();
      }

      if (status_list->empty())
      {
        cleanup.push_back(inv->first);
      }
    }

    // clean up the inventory
    std::list<std::string>::iterator clean_it = cleanup.begin();
    std::list<std::string>::iterator clean_end = cleanup.end();

    for (clean_it; clean_it != clean_end; clean_it++)
    {
      my_inventory->erase(*clean_it);
    }


  }

  /**
   * Returns a set containing the UPC's of all items stocked by this warehouse.
   */
  std::set<std::string> warehouse::get_inventory() const
  {
    std::set<std::string> inv; // a set to put item upc's

    inventory::const_iterator it = my_inventory->begin();
    inventory::const_iterator end = my_inventory->end();

    // add each upc to the set
    for (it; it != end; it++)
    {
      inv.insert(it->first);
    }

    // return the set
    return inv;
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
