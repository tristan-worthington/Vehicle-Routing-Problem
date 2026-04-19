// File Name: vehicleRoutingProblem.h
// Authors: Adam Campbell, Tyler Gill, Tristan Worthington
// Date: 4/19/2026
// Purpose: To house the includes for the necessary
// 	    libraries for our functions to work

#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <ctime>
#include <limits>
#include <algorithm>
#include <deque>

// Change return types and inputwhen 
// functions have been properly 
// implemented
// - T
bool confirmAllVisitied(std::vector<bool>);
void tabuSearch();
std::string toLabel(int);
int computeSaving(int, int, const std::vector<std::vector<int>>&);
int findRoute(int, const std::vector<std::vector<int>>&);
bool isInterior(int, const std::vector<std::vector<int>>&);
std::list<std::string> clarkWright(std::vector<std::vector<int>>);
std::list<std::string> nearestNeighbor(std::vector<std::vector<int>>);
std::list<std::string> tabuSearch(std::vector<std::vector<int>> graph);

// If needed, add classes after this point
// or in new .h files
// - T
