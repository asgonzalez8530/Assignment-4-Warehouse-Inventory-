/**
* Author: Aaron Bellis and  Anastasia Gonzalez
* UID: u0981638 and u0985898
* Date: 3/8/18
* Class: CS 3505
* Purpose: Header file for report class CS3505 C++ Assignment 4
*   Contains the report class declaration.
* How to run: must be used in conjunction with report.cpp
*/

#ifndef REPORT_H
#define REPORT_H

#include "warehouse.h"
#include "food_item.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <map>
#include <list>
#include <set>

namespace inventory_report
{
  
  struct shipment_request
  {
    std::string name;
    std::string upc;
    int quantity;
  };
  
  // typedefs to make our life easier
  
  // a shorter name for a boost date
  typedef boost::gregorian::date boost_date; 
  typedef boost::gregorian::date_duration boost_date_duration;
  
  // warehouse_map maps a warehouses names to warehouse objects
  typedef std::map<std::string, warehouse> name_warehouse_map;
  
  // food_item_map maps upcs to food_item objects
  typedef std::map<std::string, food_item> upc_food_item_map;
  
  // request_list is a list of shipment_request structs
  typedef std::list<shipment_request> request_list;
  
  // underfilled_map maps a date to a set of item upc's which were underfilled
  // that day
  typedef std::map<boost_date, std::set<std::string> > date_items_map;
  
  // maps an item to the number of times it was requested
  typedef std::map<std::string, long long> upc_number_map;
  
  
  /**
   *  Report class represents state of all warehouses, possible items and 
   * pending requests for the inventory report program.
   */ 
  class report
  {
        
    // warehouses maps warehouse names to a warehouse object with the same name
    name_warehouse_map * warehouses;
    
    // food_items maps upc's to indivdual food items allowing for easy look up
    // of information about food items
    upc_food_item_map * food_items;
    
    // contians a list of pending requests. This list is emptied by end_day()
    request_list * requests;
    
    // maps a date to a list of upc's which are underfilled orders from that day
    date_items_map * underfilled_orders;
    
    // maps upcs to the number of times they have been requested, all products 
    // appear in this map
    upc_number_map * popular_products;
    
    // the current date. NULL if not yet specified
    boost_date * date;
    
    public: 
      
      /**
       * Default constructor. Creates a report object which contains no 
       * warehouses, no food items, no requested items and no underfilled
       * orders. Sets date to NULL
       * 
       * If a receive, request, end_day or start_day method is called before the
       * date has been set, then they will be ignored. 
       */
      report();
      
      /**
       * Default destructor, ensures all resources used by this object are freed
       */
      ~report();
      
      /**
       * Sets the date of this warehouse to start_date
       */
      void set_date(const std::string & start_date);
      
      /**
       * Adds a warehouse to this report
       */ 
      void add_warehouse(const std::string & name);
      
      /**
       * Adds a food item to this report
       */ 
      void add_food_item(const std::string & name, const std::string & upc, 
        int shelf_life);
      
      /**
       * If the date has already been set, adds the quantity of upc to the 
       * inventory of warehouse_name else does nothing 
       */
      void receive_at_warehouse(const std::string & warehouse_name,
        const std::string & upc, int quantity);
      
      /** 
       * If the date has already been set, adds a request to the queue else does
       * nothing.
       * 
       * If the request cannot be processed before start of next day, tracks it
       * as an underfilled order 
       */   
      void request_from_warehouse(const std::string & warehouse_name,
        const std::string & upc, int quantity);
      
      /**
       * If the date has not been set does nothing. Else, processes all pending
       * requests tracking any underfilled items. 
       */
      void end_day();
      
      /**
       * If the date has not been set does nothing. Else, Advances the date by 
       * one day and processes expiration dates. Items expire on the start of 
       * the day that they expire.
       */
      void start_day();
      
    private:
      
      /**
       * Frees all resources used by this object and sets any references to 
       * objects to null;
       */ 
      void clean();
      
  };
}

#endif
