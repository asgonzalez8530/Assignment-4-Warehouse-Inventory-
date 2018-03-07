###
# Author: Aaron Bellis and  Anastasia Gonzalez
# UID: u0981638 and u0985898
# Date: 3/8/18
# Class: CS 3505
# Purpose: Make file for CS3505 C++ Assignment 4
# How to run: Default make action compiles a.out file required for assignment
#   submission. Additional rules for convenience in makeing, testing and 
#   submitting code. 
##

###
# Compiles a.out file required for assignment submission.
##
a.out: food_item.o warehouse.o inventory_report.cpp
	g++ *.o 

###
# Compiles food_item class to .o file for partial compilation
##
food_item.o: food_item.h food_item.cpp
	g++ -c food_item.cpp

###
# Compiles warehouse class to .o file for partial compilation
##
warehouse.o: warehouse.h warehouse.cpp
	g++ -c warehouse.cpp

###
# Compiles an executable file named debugger which is the same as the default 
# rule with the addition of debugging flags being turned on
##
debugger: warehouse.cpp food_item.cpp inventory_report.cpp warehouse.h food_item.h
	g++ -o debugger -g warehouse.cpp food_item.cpp inventory_report.cpp 

###
# Compiles an executable file named tester which combines classes with a tester
# file 
##
tester: warehouse.o food_item.o inventory_report.cpp inventory_tester.cpp
	g++ -o tester warehouse.o food_item.o inventory_report.cpp inventory_tester.cpp

###
# Compiles an executable file named debug_tester which combines classes with a 
# tester file along with gdb flags
##
debug_tester: warehouse.o food_item.o inventory_report.cpp inventory_tester.cpp
	g++ -o debug_tester warehouse.cpp food_item.cpp inventory_report.cpp inventory_tester.cpp -g

###
# Cleans this directory of any files which may have been created as a result 
# of running a rule in this makefile
##
clean:
	rm -f a.out debug_tester tester debugger cs3505-assignment4.zip *.o

###
# Zips files for assignment into a single compressed folder ready for turning in
##
zip: Makefile warehouse.h food_item.h warehouse.cpp food_item.cpp inventory_report.cpp
	zip cs3505-assignment4.zip Makefile warehouse.h food_item.h warehouse.cpp food_item.cpp inventory_report.cpp

