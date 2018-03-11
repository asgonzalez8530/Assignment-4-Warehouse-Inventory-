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

#include "report.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

// pre defined methods
void parse_food_item (inventory_report::report * r, const std::string & line);
std::string parse_warehouse (const std::string & line);
std::string parse_start_date (const std::string & line);
void parse_receive (inventory_report::report * r, const std::string & line);
void parse_request (inventory_report::report * r, const std::string & line);
std::string print_report(inventory_report::report * r);
std::string request_underfilled_items(inventory_report::report * r);
std::string request_well_stocked_items(inventory_report::report * r);
std::string request_most_popular_products(inventory_report::report * r);
inventory_report::shipment_request get_upc_quantity_warehouse(const std::string & line, 
  const std::string & search_string);

// helper methods
std::string get_next_token(const std::string & line, 
  const std::string & search_string);
std::string get_till_end_of_line(const std::string & line, 
  const std::string & search_string);


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
  
  // get first command line argument, which should be the file to be processed
  char* file = argv[1];
  
  // create an in file stream using the file
  std::ifstream in_file;
  
  in_file.open(file);
  
  int line_size = 1000;
  char line[line_size];
  std::string word_delimiter = " ";
  // getline reads up to line_size or until '/n' char and places into line 

  // make a new report object on the heap 
  inventory_report::report * my_report = new inventory_report::report();

  while (in_file.getline(line,line_size))
  {
    std::string line_string(line);
    std::string token = line_string.substr(0, line_string.find(word_delimiter));
    
    if (token == "FoodItem")
    {
      // parse the footitem and add it to the report
      parse_food_item(my_report, line_string);
    }
    else if (token == "Warehouse")
    {
      std::string warehouse_name = parse_warehouse (line_string);

      // add a new warehouse to the report
      my_report->add_warehouse(warehouse_name);
    }
    else if (token == "Start")
    {
      std::string date = parse_start_date(line);

      // set the date to the start date of the report
      my_report->set_date(date);
    }
    else if (token == "Receive:")
    {
      // parse receive and adds the shipment to the warehouse in the report
      parse_receive (my_report, line_string);
    }
    else if (token == "Request:")
    {
      // parse request and remove items from the warehouse in the report
      parse_request (my_report, line_string);
     
    }
    else if (token == "Next")
    {
      // do the end of the day actions 
      my_report->end_day();

      // do the start of the day actions
      my_report->start_day();
    }
    else if (token == "End")
    {
      // do end of day actions
      my_report->end_day();

      break;
    }
    
  }
  // file must be closed when done
  in_file.close();
  
  std::cout << print_report(my_report) << std::endl;

  // clean up report 
  delete my_report;
  my_report = NULL;
  
}

/**
 * Takes in a line from transaction report and parses it into a food_item object 
 */
void parse_food_item (inventory_report::report * r, const std::string & line)
{ 
  std::string upc = get_next_token(line, "UPC Code: ");
  std::string shelf_life = get_next_token(line, "Shelf life: ");
  std::string name = get_till_end_of_line(line, "Name: ");

  int life = std::atoi(shelf_life.c_str());

  // add food item to the report
  r->add_food_item(name, upc, life);
}

/**
 * Takes in a line from transaction report and parses out the warehouse name
 */
std::string parse_warehouse (const std::string & line)
{ 

  // parse the line for the warehouse name
  std::string name = get_till_end_of_line(line, "Warehouse - ");

  // return the warehouse name
  return name;
}

/**
 * Parses a line which includes the start date and returns a string of the start date
 */ 
std::string parse_start_date (const std::string & line)
{
  // parse the line for the start date
  std::string date = get_next_token(line, "Start date: ");
  
  // return the start date 
  return date;
}

/**
 * Takes in a line from transaction report. Parses the shipment and adds
 * it to the indicated warehouse in the report.
 */
void parse_receive (inventory_report::report * r, const std::string & line)
{ 
  
  // parse line for upc, quantity, and warehouse name
  inventory_report::shipment_request request = 
    get_upc_quantity_warehouse(line, "Receive: ");

  // add shipment to the warehouse in the report
  r->receive_at_warehouse(request.name, request.upc, request.quantity);

}

/**
 * Takes in a line from transaction report and parses the request
 */
void parse_request (inventory_report::report * r, const std::string & line)
{ 
   // parse line for upc, quantity, and warehouse name
  inventory_report::shipment_request request = 
    get_upc_quantity_warehouse(line, "Request: ");
    

  // add shipment to the warehouse in the report
  r->receive_at_warehouse(request.name, request.upc, request.quantity);
  
}

/**
 * Returns a string to print to the console of the report required for this assignment. 
 * Finds the underfilled products, wellstocked products, and the most popular products.
 */
std::string print_report(inventory_report::report * r)
{
  // report header
  std::string result = report_by;

  // underfilled items
  result += underfilled_orders;
  result += request_underfilled_items(r);
  result += "\n";

  // well stocked items
  result += well_stocked_products;
  result += request_well_stocked_items(r);
  result += "\n";

  // most popular products
  result += most_popular_products;
  result += request_most_popular_products(r);

  return result;
}

/**
 * Helper method to print report. Returns a string of the underfilled items. 
 * Underfilled orders are a list of the orders (in sorted order by date first, 
 * UPC second, no duplicates) that could not be partially or fully satisfied.
 */
std::string request_underfilled_items(inventory_report::report * r)
{
  // build up the report that we will return at the end
  std::string report = "";
  // get the vector report
  std::vector<std::string> underfilled_order_report = r->request_underfilled_orders();

  // make an iterator to loop through the entries
  std::vector<std::string>::iterator it = underfilled_order_report.begin();
  std::vector<std::string>::iterator end = underfilled_order_report.end();

  for(it; it != end; it++)
  {
    // dereference the iterator to get the string stored at that location
    report += *it;
    // insert a new line after the report entry
    report += "\n";
  }

  return report;
}

/**
 * Helper method to print report. Returns a string of the well stocked items. 
 * Well stocked items are a a list of the products (in sorted order by UPC) that 
 * have positive quantities in at least two warehouses (at the end of the simulation).
 */
std::string request_well_stocked_items(inventory_report::report * r)
{
  // build up the report that we will return at the end
  std::string report = "";
  // get the vector report
  std::vector<std::string> underfilled_order_report = r->request_well_stocked_items();

  // make an iterator to loop through the entries
  std::vector<std::string>::iterator it = underfilled_order_report.begin();
  std::vector<std::string>::iterator end = underfilled_order_report.end();

  for(it; it != end; it++)
  {
    // dereference the iterator to get the string stored at that location
    report += *it;
    // insert a new line after the report entry
    report += "\n";
  }

  return report;
}

/**
 * Helper method to print report. Returns a string of the most popular items. 
 * The most popular products are the top three most requested products; the most popular products 
 * have the highest total quantity in the data file requests.  If items have identical 
 * request quantities, break ties using UPCs (lower UPC comes first).  If you receive a 
 * data file with less than three products, report them in popularity order.  For each 
 * food item, print out its total requested quantity, UPC, and name.
 */
std::string request_most_popular_products(inventory_report::report * r)
{
  // build up the report that we will return at the end
  std::string report = "";
  // get the vector report
  std::vector<std::string> underfilled_order_report = r->request_popular_items();

  // make an iterator to loop through the entries
  std::vector<std::string>::iterator it = underfilled_order_report.begin();
  std::vector<std::string>::iterator end = underfilled_order_report.end();

  for(it; it != end; it++)
  {
    // dereference the iterator to get the string stored at that location
    report += *it;
    // insert a new line after the report entry
    report += "\n";
  }

  return report;
}

/**
 * Searches line for search_string and returns the token (delimited by ' ')
 * immediately following search_string contianed in line
 */
std::string get_next_token(const std::string & line, 
  const std::string & search_string)
{
    
  // get the first char position of the search_string
  int first_char_position = line.find(search_string);
  int i = first_char_position;
  int j = 0;
  
  // addvance i untill we get past search_string
  while (j < search_string.length() && line[i] == search_string[j])
  {
    i++;
    j++;
  }
  
  //create a stringstream to add chars
  std::stringstream ss;
  //as long as we aren't at the end of the line
  while (i < line.length())
  {
    
    // if we find a space, \r or \n character stop adding to ss
    if (line[i] == ' ' || line[i] == '\r' || line[i] == '\n')
    {
      break;
    }
    
    // add the char to ss then increment i
    ss << line[i];
    i++;  
  }
  
  // return a string representation of ss
  return ss.str();
 
}

/**
 * Searches line for search_string and returns a string which contains all 
 * characters after search_string until the end of the line
 */
std::string get_till_end_of_line(const std::string & line, 
  const std::string & search_string)
{
  // get the first char position of the search_string
  int first_char_position = line.find(search_string);
  int i = first_char_position;
  int j = 0;
  
  // addvance i untill we get past search_string
  while (j < search_string.length() && line[i] == search_string[j])
  {
    i++;
    j++;
  }
  
  //create a stringstream to add chars
  std::stringstream ss;
  //as long as we aren't at the end of the line
  while (i < line.length())
  {
    
    // if we find \r or \n character stop adding to ss
    if (line[i] == '\r' || line[i] == '\n')
    {
      break;
    }
    
    // add the char to ss then increment i
    ss << line[i];
    i++;  
  }
  
  // return a string representation of ss
  return ss.str();
}


/**
* Searches line for search_string and returns the next token (delimited by ' ')
* contianed in line
*/
inventory_report::shipment_request get_upc_quantity_warehouse(const std::string & line, 
  const std::string & search_string)
{ 
  // we want the upc, quantity, and warehouse name from this line
  std::string request_data = get_till_end_of_line(line, search_string);
  
  std::vector<std::string> vect;
  
  //create a stringstream to add chars
  std::stringstream ss;
  int i = 0;
  //as long as we aren't at the end of the line
  while (i < request_data.length())
  {

    // if we find \r or \n character stop adding to ss
    if (request_data[i] == ' ')
    {
      std::string token = ss.str();
      vect.push_back(token);
      ss.str("");
      ss.clear();
      i++;
      continue;
    }
    
    // add the char to ss then increment i
    ss << request_data[i];
    i++;  
  }
  
  // make sure the last token is pushed to vector
  std::string token = ss.str();
  vect.push_back(token);
  
  std::vector<std::string>::iterator it = vect.begin();
  std::vector<std::string>::iterator end = vect.end();
 
  // I know I got at least three items
  std::string upc = *it;
  it++;
  int quant = std::atoi(it->c_str());
  it++;
  
  // all last tokens are part of name
  ss.str("");
  ss.clear();
  while (it != end)
  {
    ss << *it;
    it++;
    
    // don't add space to last token
    if (it != end)
    {
      ss << " ";
    }
  }
  
  std::string warehouse_name = ss.str();

  inventory_report::shipment_request request = {warehouse_name, upc, quant};

  return request;
}

