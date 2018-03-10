/**
 * Author: Aaron Bellis and  Anastasia Gonzalez
 * UID: u0981638 and u0985898
 * Date: 3/8/18
 * Class: CS 3505
 * Purpose: Defines a main function for the inventory_report program
 *   as specified in cs3505 assignment4 
 * How to run: Can be compiled with the default make rule and ran as a standalone
 *   executalbe. 
 */

// #include "warehouse.h"
// #include "food_item.h"
// #include <boost/date_time/gregorian/gregorian.hpp>

#include "report.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

// using namespace inventory_report;

food_item parse_food_item (const std::string & line);
const std::string & parse_warehouse (const std::string & line);
void parse_receive (const std::string & line);
void parse_request (const std::string & line);
std::string get_next_token(const std::string & line, 
  const std::string & search_string);
std::string get_till_end_of_line(const std::string & line, 
  const std::string & search_string);
boost::gregorian::date parse_start_date (const std::string & line);

//******** global variables ********//
const std::string report_by = "Report by Aaron and Anastasia\n";
const std::string underfilled_orders = "Underfilled orders:\n";
const std::string well_stocked_products = "Well-Stocked Products:\n";
const std::string most_popular_products = "Most Popular Products:\n";


/**
 * Main function for the inventory report program. Takes one command line
 * argument which is the name of a text file to be processed and outputs to
 * standard output the results of that processing. This program assumes that
 * the input file will be propperly formatted. Additional command line arguments
 * beyond the expected will be ignored. If no command line arguments are passed
 * to program, will return instantly.
 */
int main(int argc, char** argv)
{
  // check that at least one command line argument was given to program
  if (argc < 2)
  {
    return 0;
  }

  // the report object that will handle the processing of the file
  inventory_report::report * my_report = new report();
  
  // get first command line argument, which should be the file to be processed
  char* file = argv[1];
  
  // create an in file stream using the file
  std::ifstream in_file;
  
  in_file.open(file);
  
  int line_size = 1000;
  char line[line_size];
  std::string word_delimiter = " ";
  // getline reads up to line_size or until '/n' char and places into line 
  while (in_file.getline(line,line_size))
  {
    std::string line_string(line);
    std::string token = line_string.substr(0, line_string.find(word_delimiter));
    
    if (token == "FoodItem")
    {
      food_item item = parse_food_item(line_string); 
      // do something with the food item
      // ...
    }
    else if (token == "Warehouse")
    {
      // parse the warehouse name ad add it to the report
      std::string warehouse_name = parse_warehouse(my_report, line_string);
      my_report->add_warehouse(warehouse_name);
    }
    else if (token == "Start")
    {
      // parse the date and add set it as the date of the report
      string date = parse_start_date(line);
      my_report->set_date(date);
    }
    else if (token == "Receive:")
    {
      // we will probably want to do all the work inside the method
      // or we can return a vector or array with the info
      parse_receive (line_string);
    }
    else if (token == "Request:")
    {
      // we will probably want to do all the work inside the method
      // or we can return a vector or array with the info
      parse_request (line_string);
    }
    else if (token == "Next")
    {
      my_report->end_day();
      my_report->start_day();
    }
    else if (token == "End")
    {
      // do end of day then break
      
      break;
    }
    
  }
  
  // file must be closed when done
  in_file.close();

  // clean up our report object
  delete my_report;
  my_report = NULL;
}

/**
 * Takes in a line from transaction report and parses it into a food_item object 
 */
food_item parse_food_item (const std::string & line)
{ 
  std::string upc = get_next_token(line, "UPC Code: ");
  std::string shelf_life = get_next_token(line, "Shelf life: ");
  std::string name = get_till_end_of_line(line, "Name: ");
  int life = std::atoi(shelf_life.c_str());
  
  return food_item(name, upc, life);
}

/**
 * Parses a line which includes the start date and returns the date as a string
 */ 
std::string & parse_start_date (const std::string & line)
{
  std::string date_string = get_next_token(line, "Start Date: ");
  
  return date_string;
}

/**
 * Takes in a line from transaction report and parses it into a warehouse object 
 */
const std::string & parse_warehouse (const std::string & line)
{ 
  // parse the line for the warehouse name
  std::string name = get_till_end_of_line(line, "Warehouse - ");

  return name;
}

/**
 * Takes in a line from transaction report and parses the shipment 
 */
void parse_receive (const std::string & line)
{ 
  // parse the line for the upc number
  std::string upc = get_next_token(line, "Receive: ");
  // parse the line for the shipment quantity
  std::string shipment_size = get_next_token(line, " ");
  int quantity = std::atoi(shipment_size.c_str());
  // parse the line for the warehouse name 
  std::string warehouse_name = get_next_token(line, " ");
}

/**
 * Takes in a line from transaction report and parses the request
 */
void parse_request (const std::string & line)
{ 
  // parse the line for the upc number
  std::string upc = get_next_token(line, "Request: ");
  // parse the line for the request quantity
  std::string request_size = get_next_token(line, " ");
  int quantity = std::atoi(request_size.c_str());
  // parse the line for the warehouse name 
  std::string warehouse_name = get_next_token(line, " ");
}

/**
 * Searches line for search_string and returns the next token (delimited by ' ')
 * contianed in line
 */
std::string get_next_token(const std::string & line, 
  const std::string & search_string)
{
  
  // this will return the position of search_string[0] in the above string
  int position = line.find_first_of(search_string);
  
  // we want the upc, which should start in the character after the search 
  // string
  std::string token = "";
  int i = position + search_string.length() + 1;
  // go untill we find a space
  while (line[i] != ' ' && line[i] != '\n' && i != line.length())
  {
    token += line[i];
    i++;
  }
  
  return token;
}

/**
 * Searches line for search_string and returns a string which contains all 
 * characters after search_string until the end of the line
 */
std::string get_till_end_of_line(const std::string & line, 
  const std::string & search_string)
{
  
  // this will return the position of search_string[0] in the above string
  int position = line.find_first_of(search_string);
  
  // we want the upc, which should start in the character after the search 
  // string
  std::string token = "";
  int i = position + search_string.length() + 1;
  // go untill we find a space
  while (line[i] != '\n' && i == line.length())
  {
    token += line[i];
    i++;
  }
  
  return token;
}
