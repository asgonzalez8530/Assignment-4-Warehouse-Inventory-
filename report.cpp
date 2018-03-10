/**
* Author: Aaron Bellis and  Anastasia Gonzalez
* UID: u0981638 and u0985898
* Date: 3/8/18
* Class: CS 3505
* Purpose: cpp file for report class CS3505 C++ Assignment 4
*   Contains the report class definition.
* How to run: must be used in conjunction with inventory.h
*/

#include "report.h"

namespace inventory_report
{

   /**
   * Default constructor. Creates a report object which contains no 
   * warehouses, no food items, no requested items and no underfilled
   * orders. Sets date to NULL
   * 
   * If a receive, request, end_day or start_day method is called before the
   * date has been set, then they will be ignored. 
   */
  report::report()
  {
    warehouses = new name_warehouse_map();
    food_items = new upc_food_item_map();
    requests = new request_list();
    underfilled_orders = new date_items_map();
    popular_products = new upc_number_map();
    date = NULL;
  }
  
  /**
   * Default destructor, ensures all resources used by this object are freed
   */
  report::~report()
  {
    clean();
  }
  
  /**
   * Takes a string which contains a delimited date in the US format and sets 
   * the date of this warehouse to start_date
   */
  void report::set_date(const std::string & start_date)
  {
    date = new boost_date(boost::gregorian::from_us_string(start_date));
  }
  
  /**
   * Adds a warehouse to this report
   */ 
  void report::add_warehouse(const std::string & name)
  {
  
  }
  
  /**
   * Adds a food item to this report
   */ 
  void report::add_food_item(const std::string & name, const std::string & upc, 
    int shelf_life)
  {
  
  }
  
  /**
   * If the date has already been set, adds the quantity of upc to the 
   * inventory of warehouse_name else does nothing 
   */
  void report::receive_at_warehouse(const std::string & warehouse_name,
    const std::string & upc, int quantity)
  {
  
  }
  
  /** 
   * If the date has already been set, adds a request to the queue else does
   * nothing.
   * 
   * If the request cannot be processed before start of next day, tracks it
   * as an underfilled order 
   */   
  void report::request_from_warehouse(const std::string & warehouse_name,
    const std::string & upc, int quantity)
  {
  
  }
  
  /**
   * If the date has not been set does nothing. Else, processes all pending
   * requests tracking any underfilled items. 
   */
  void report::end_day()
  {
  
  }
  
  /**
   * If the date has not been set does nothing. Else, Advances the date by 
   * one day and processes expiration dates. Items expire on the start of 
   * the day that they expire.
   */
  void report::start_day()
  {
  
  }
  
  /**
   * Frees all resources used by this object and sets any references to 
   * objects to null;
   */ 
  void report::clean()
  {
    delete warehouses;
    warehouses = NULL;
    
    delete food_items;
    food_items = NULL;
    
    delete requests;
    requests = NULL;
    
    delete underfilled_orders;
    underfilled_orders = NULL;
    
    delete popular_products;
    popular_products = NULL;
    
    if (date != NULL)
    {
      delete date;
      date = NULL;
    }
  }
  
}
