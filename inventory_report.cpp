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

#include "warehouse.h"
#include "food_item.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>
#include <fstream>

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
  while (in_file.getline(line,line_size))
  {
    std::string line_string(line);
    std::string token = line_string.substr(0, line_string.find(word_delimiter));
    
    if (token == "FoodItem")
    {
      
    }
    else if (token == "Warehouse")
    {

    }
    else if (token == "Start")
    {
      
    }
    else if (token == "Receive:")
    {
      
    }
    else if (token == "Request:")
    {
    
    }
    else if (token == "Next")
    {
      
    }
    else if (token == "End")
    {
    
    }
    
  }
  
  // file must be closed when done
  in_file.close();
}

