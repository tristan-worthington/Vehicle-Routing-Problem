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
#include <fstream>
#include <sstream>
#include <cmath>
#include <chrono>
#include <random>
#include <iomanip>
// Change return types and inputwhen 
// functions have been properly 
// implemented
// - T
bool confirmAllVisited(std::vector<bool>);
double computeSaving(int, int, const std::vector<std::vector<int>>&);
int findRoute(int, const std::vector<std::vector<int>>&);
bool isInterior(int, const std::vector<std::vector<int>>&);
std::list<std::string> clarkWright(std::vector<std::vector<double>>);
std::list<std::string> nearestNeighbor(std::vector<std::vector<double>>);
std::list<std::string> tabuSearch(std::vector<std::vector<double>>);
std::list<std::string> antColony(std::vector<std::vector<double>>);
// If needed, add classes after this point
// or in new .h files
// - T
