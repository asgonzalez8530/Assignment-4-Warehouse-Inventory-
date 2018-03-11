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
    if (date != NULL)
    {
      delete date;
      date == NULL;
    }
    
    int month = std::atoi(start_date.substr(0, 2).c_str());
    int day = std::atoi(start_date.substr(3, 2).c_str());
    int year = std::atoi(start_date.substr(6,4).c_str());
    date = new boost_date(year,month,day);
  }
  
  /**
   * Adds a warehouse to this report
   */ 
  void report::add_warehouse(const std::string & name)
  {
    warehouse house = warehouse(name);

    // map the name to the ware house object in warehouses
    warehouses->insert(std::pair<std::string, warehouse> (name, house));   

  }
  
  /**
   * Adds a food item to this report
   */ 
  void report::add_food_item(const std::string & name, const std::string & upc, 
    int shelf_life)
  {
    
    std::pair<std::string, food_item> upc_item_pair(upc, food_item(name, upc, shelf_life));
    
    
    food_items->insert(std::pair<std::string, food_item>(upc_item_pair));
      
    
    // all products will appear in popular_products even if they haven't been
    // requested before
    popular_products->insert(std::pair<std::string, long long>(upc, 0));
  }
  
  /**
   * If the date has already been set, adds the quantity of upc to the 
   * inventory of warehouse_name else does nothing 
   */
  void report::receive_at_warehouse(const std::string & warehouse_name,
    const std::string & upc, int quantity)
  {
    if (date == NULL)
    {
      return;
    }


    
    warehouse * house;
    
    // get reference to the warehouse safely
    if (warehouses->count(warehouse_name))
    {

      house = &(warehouses->at(warehouse_name));
    }

   
    // lookup the shelflife for this food item
    int shelf_life = 0;
    
    // get reference to food_item safely
    if (food_items->count(upc))
    {
      food_item item = food_items->at(upc);
      shelf_life = item.get_shelf_life();
    }

    
    // add inventory to the warehouse
    house->add_inventory(upc, quantity, shelf_life);

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
    if (date == NULL)
    {
      return;
    }    
    
    // update popular_products
    if (popular_products->count(upc))
    {
      // get an iterator which points to the product 
      upc_number_map::iterator it= popular_products->find(upc);
      // follow the iterator to the second element of the pair and add quantity
      // to it.
      it->second += quantity;
    }
    
    // add the request to the pending requests
    shipment_request request = {warehouse_name, upc, quantity};
    requests->push_back(request);
    
  }
  
  /**
   * If the date has not been set does nothing. Else, processes all pending
   * requests tracking any underfilled items. 
   */
  void report::end_day()
  {
    if (date == NULL)
    {
      return;
    } 
    
    while (!requests->empty())
    {
      // get a pointer to the first item of the list
      request_list::iterator request = requests->begin();
      
      // process the request
      // get the warehouse for this request
      warehouse * house;
    
      // get reference to the warehouse safely
      if (warehouses->count(request->name))
      {
        house = &(warehouses->at(request->name));
      }
      
      // follow the pointer to the warehouse and remove the inventory. Story the
      // amount removed to check for an underfilled order
      int amount_removed = house->remove_inventory(request->upc,
        request->quantity);
      
      // make sure full request was fulfilled
      if (amount_removed != request->quantity)
      {
        // wasn't completely fulfilled, need to track it as an underfilled item  
        if (underfilled_orders->count(*date))
        {
          // date is already in underfilled_orders
          // get the set
          std::set<std::string> * orders = &(underfilled_orders->at(*date));
          
          // add the upc to the set of underfilled orders on this date
          orders->insert(request->upc);
        }
        else
        {
          // date is not already in underfilled_orders create entry          
          
          std::set<std::string> orders = std::set<std::string>();
          orders.insert(request->upc);
          
          // date is not already in underfilled_orders create entry
          underfilled_orders->insert(
            std::pair<boost_date, std::set<std::string> > (*date, orders)); 
          
        }
      }
      // pop the front of the list and return to top to process next request
      requests->pop_front();
    }
    
    
  }
  
  /**
   * If the date has not been set does nothing. Else, Advances the date by 
   * one day and processes expiration dates. Items expire on the start of 
   * the day that they expire.
   */
  void report::start_day()
  {
    if (date == NULL)
    {
      return;
    } 
    
    //advance date by one day
    boost_date_duration one_day(1);
    boost_date new_date = *date + one_day;
    
    // delete the date that is on the heap (avoid memory leak)
    delete date;
    date = NULL;
    
    // now that date is cleaned, lets create a date on the heap using new_date
    date = new boost_date(new_date);
    
    // for each warehouse
    
    // get an iterator for the warehouses map that points to the beginning
    name_warehouse_map::iterator it = warehouses->begin();
    // and another for the end
    name_warehouse_map::iterator end = warehouses->end();
    
    for (it; it != end; it++)
    {
      // get a pointer to the actual warehouse
      warehouse * house = &(it->second);
      
      // update its day
      house->update_day();
      
      // take care of its expire inventory
      house->remove_expired_inventory();   
    }
    
  }
  
  /**
   * Adds underfilled orders into a vector as a string and returns the 
   * resulting vector 
   * Strings in vector will be in the format DATE UPC ITEM_NAME this will be
   * ordered first by DATE then by UPC 
   * 
   * If an underfilled order was made on July 20, 1969 with upc 0123456789
   * and that upc corresponded to a food item named Tang, it would appear
   * as the following: 
   *
   * "07/20/1969 0123456789 Tang"
   */
  std::vector<std::string> report::request_underfilled_orders()
  {
    // vector that we will build up and return at the end
    std::vector<std::string> result;

    // make an iterator to loop through underfilled_orders
    date_items_map::iterator it = underfilled_orders->begin();
    date_items_map::iterator end = underfilled_orders->end();

    for(it; it != end; it++)
    {
      // pull out the date and convert to a string
      boost_date d = it->first;
      std::string entry = "";
      entry.push_back(d.month());
      entry.push_back('/');
      entry.push_back(d.day());
      entry.push_back('/');
      entry.push_back(d.year());

      // pull out the set of orders that correspond to that date
      std::set<std::string> * orders = &(it->second);
      std::string order_results = "";
      
      // make an iterator to loop through the orders
      std::set<std::string>::iterator it2 = orders->begin();
      std::set<std::string>::iterator end2 = orders->end();    

      for (it2; it2 != end2; it2++)
      {
        // get the upc
        std::string upc = *it2;

        // map the upc to the item name
        std::string name = food_items->at(upc).get_name();

        // insert the upc and item name into the order_result string
        order_results += upc + name;
      }

      // add the order information to the date entry 
      entry += order_results;

      // add the order entry to the end of the vector
      result.push_back(entry);
    }

    return result;
  }
   
  /**
   * Returns a vector containing [0, 3] items which are the three most 
   * requested items in the inventory.
   * String in vector will be in the format NUMBER_OF_REQUESTS UPC ITEM_NAME
   * and will be ordered by NUMBER_OF_REQUESTS then by UPC
   *
   * If popular order was requested 500 times with upc 0123456789
   * and that upc corresponded to a food item named "Hot Wings", it would 
   * appear as the following: 
   *
   * "500 0123456789 Hot Wings"
   */
  std::vector<std::string> report::request_popular_items()
  {
    std::set<popular_product, popularity_comp> popularity_set = 
      std::set<popular_product, popularity_comp> ();
    
    // create a scope for these iterators
    {
      // add all items to a set
      upc_number_map::iterator item = popular_products->begin();
      upc_number_map::iterator end = popular_products->end();
    
      for (item; item != end; item++)
      {
        // get the upc
        std::string upc = item->first;
        // get the number of requests
        long long requests = item->second;
      
        // add it to products
        popular_product product = { upc, requests };
      
        popularity_set.insert(product);
      }
    }
    
    // this set now contains all items and is sorted in decending order
    
    std::vector<std::string> return_vector;
    
    // get the first three items
    // add all items to a set
    std::set<popular_product, popularity_comp>::iterator item = 
      popularity_set.begin();
      
    std::set<popular_product, popularity_comp>::iterator end = 
      popularity_set.end();
    
    std::set<popular_product, popularity_comp>::iterator third_item = item;
    third_item ++;
    third_item ++;
    third_item ++;
    
    for (item; item != end && item != third_item; item++)
    {
      // get the item
      std::string upc = item->upc;
      long long req = item->requests;
      
      // get the name of this item
      std::string name = food_items->at(upc).get_name();
      
      // put the string together
      std::stringstream ss;
      ss << req << " " << upc << name; 
      
      // add it to the vector
      return_vector.push_back(ss.str());
    }
    
    return return_vector;
  }
  
  /**
   * Returns a vector containing all items which are currently stocked in at
   * least two warehouses. Strings will be in the format UPC ITEM_NAME
   *
   * If a product with upc 0123456789 named "Hello Kitty Erasers" was
   * was stocked in the inventory of two warehouses, it would appear as the
   * following:
   * 
   * "0123456789 Hello Kitty Erasers"
   */
   std::vector<std::string> report::request_well_stocked_items()
   {
     // vector that we will build up and return at the end
      std::vector<std::string> result;

      // set that will hold the most popular items
      std::set<std::string> well_stocked;

      // set that will hold all items
      std::set<std::string> all_items;

      // make an iterator to loop through underfilled_orders
      name_warehouse_map::iterator it = warehouses->begin();
      name_warehouse_map::iterator end = warehouses->end();

      bool not_first = false;
      for(it; it != end; it++)
      { 
        // pull out the date and convert to a string
        warehouse w = it->second;
        
        // pull out the inventory from the warehouse
        std::map< std::string, std::list<item_status> > inventory = w.get_inventory();
        
        // make an iterator to loop through the orders
        std::map< std::string, std::list<item_status> >::iterator it2 = inventory.begin();
        std::map< std::string, std::list<item_status> >::iterator end2 = inventory.end();    

        for (it2; it2 != end2; it2++)
        {
          // get the item
          std::string upc = it2->first;

          // add the food item to all items
          std::pair<std::set<std::string>::iterator, bool> insertion = all_items.insert(upc);

          if (not_first)
          {
            if (!(insertion.second))
            {
              well_stocked.insert(upc);
            }
          }
        }

        not_first = true;
      }

      // make an iterator to loop through the orders
      std::set<std::string>::iterator it2 = well_stocked.begin();
      std::set<std::string>::iterator end2 = well_stocked.end();    

      for (it2; it2 != end2; it2++)
      {
        // get the item
        std::string upc = *it2;

        // entry that will go into vector
        std::string entry = upc + food_items->at(upc).get_name();
        result.push_back(entry);
      }

      return result;
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
