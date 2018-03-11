/**
* Author: Aaron Bellis and  Anastasia Gonzalez
* UID: u0981638 and u0985898
* Date: 3/8/18
* Class: CS 3505
* Purpose: Header file for food_item class CS3505 C++ Assignment 4
*   Contains the food_item class declaration.
* How to run: must be used in conjunction with food_item.cpp
*/

#ifndef FOOD_ITEM_H
#define FOOD_ITEM_H

#include <string>


namespace inventory_report
{
  
  /**
  * food_item class represents food items contained in a warehouses inventory
  * and provides information about its name, upc code and shelf life (in days)
  */
  class food_item
  {
    // the name of this item
    std::string item_name;
    // a string of number characters of positive length.
    // upc_code uniquely identifies each food item.
    std::string item_upc_code; 
    // a number < 0 which represents this items shelf life in days
    int item_shelf_life;
    
    public:
      
      /**
      * food_item constructor which takes a name as string of words, a upc_code
      * as a string of number characters of positive length and a shelf_life as
      * an int which is greater than zero. 
      * 
      * The upc_code provided uniquely identifies this food item.
      */
      food_item(const std::string & name, const std::string & upc_code, 
        int shelf_life); 
      
      /**
      * Copy constructor for the food_item class. Takes a food_item other, and
      * constructs a new food_item object using its contents.
      */
      food_item(const food_item & other);
      
      /**
      * Returns a reference to this food_item's name.
      */
      const std::string & get_name() const;
      
      /**
      * Returns a reference to this food_item's upc code which uniquely 
      * identifies this food_item .
      */
      const std::string & get_upc_code() const;
      
      /**
      * Returns the shelf life of this object.
      */
      int get_shelf_life() const;
      
      /**
      * Overloaded assignment operator. Assigns the contents of the food_item 
      * object rhs into the object to the left of the operator.
      */
      food_item & operator= (const food_item & rhs);
      
      /**
       * overloaded operators. All operators compare objects upcs
       */
       
      bool operator> (const food_item & rhs) const;
      bool operator>= (const food_item & rhs) const;
      bool operator<= (const food_item & rhs) const;
      bool operator< (const food_item & rhs) const;
      bool operator== (const food_item & rhs) const;
      bool operator!= (const food_item & rhs) const;
  };
}

#endif
