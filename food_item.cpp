/**
* Author: Aaron Bellis and  Anastasia Gonzalez
* UID: u0981638 and u0985898
* Date: 3/8/18
* Class: CS 3505
* Purpose: CPP file for food_item class CS3505 C++ Assignment 4
*   Contains the food_item class member definitions.
* How to run: must be used in conjunction with food_item.h
*/

#include "food_item.h" // food_item class declaration

namespace inventory_report
{
  
  /**
  * food_item constructor which takes a name as string of words, a upc_code
  * as a string of number characters of positive length and a shelf_life as
  * an int which is greater than zero. 
  * 
  * The upc_code provided uniquely identifies this food item.
  */
  food_item::food_item(const std::string & name, const std::string & upc_code, 
    int shelf_life)
  {
    item_name = name;
    item_upc_code = upc_code;
    item_shelf_life = shelf_life;
  }
      
  /**
  * Copy constructor for the food_item class. Takes a food_item other, and
  * constructs a new food_item object using its contents.
  */
  food_item::food_item(const food_item & other)
  {
    // I don't know if we will need this but it is super easy so
    // I defined it. Okay to delete if we don't need it.
    this->item_name = other.item_name;
    this->item_upc_code = other.item_upc_code;
    this->item_shelf_life = other.item_shelf_life;
    
  }
      
  /**
  * Returns a reference to this food_item's name.
  */
  const std::string & food_item::get_name() const
  {
    return item_name;
  }
    
  /**
  * Returns a reference to this food_item's upc code which uniquely 
  * identifies this food_item .
  */
  const std::string & food_item::get_upc_code() const
  {
    return item_upc_code;
  }
      
  /**
  * Returns the shelf life of this object.
  */
  int food_item::get_shelf_life() const
  {
    return item_shelf_life;
  }
  
  /**
  * Overloaded assignment operator. Assigns the contents of the food_item 
  * object rhs into the object to the left of the operator.
  */
  food_item & food_item::operator= (const food_item & rhs)
  {
    // do not assign this object to itself
    if (this == &rhs)
    {
      return *this;
    }
    
    // copy contents of rhs into this
    this->item_name = rhs.item_name;
    this->item_upc_code = rhs.item_upc_code;
    this->item_shelf_life = rhs.item_shelf_life;
    
    // return this, always the final step of an overloaded operator=
    return *this;
  }
  
  /**
   * returns true if upc of lhs is greater than that of rhs
   */
  bool food_item::operator> (const food_item & rhs) const
  {
    return this->item_upc_code > rhs.item_upc_code;
  }
  
  /**
   * returns true if upc of lhs is greater or equal to that of rhs
   */
  bool food_item::operator>= (const food_item & rhs) const
  {
    return !(*this < rhs);
  }
  
  /**
   * returns true if upc of lhs is less than or equal to that of rhs
   */
  bool food_item::operator<= (const food_item & rhs) const
  {
    return !(*this > rhs);
  }
  
  /**
   * returns true if upc of lhs is less than that of rhs
   */
  bool food_item::operator< (const food_item & rhs) const
  {
    return this->item_upc_code < rhs.item_upc_code;
  }
  
  /**
   * returns true if upc of lhs is equal to that of rhs
   */
  bool food_item::operator== (const food_item & rhs) const
  {
    return this->item_upc_code == rhs.item_upc_code;
  }
  
  /**
   * returns true if upc of lhs is not equal to that of rhs
   */
  bool food_item::operator!= (const food_item & rhs) const
  {
    return !(*this == rhs);
  }
  
}
