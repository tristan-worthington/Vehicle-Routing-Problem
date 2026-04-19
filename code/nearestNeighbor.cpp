// File Name: nearestNeighbot.cpp
// Author: Tristan Worthington
// Date: 4/19/2026
// Purpose: To implement the Nearest Neighbor search
//	    algorithm to try to find the most efficient
//	    route between a set of points
//
// NOTE: No code used in these functions were AI
// 	 generated. These were made by solely me,
// 	 the author, at 4:40 something AM.
//
// "So steel yourself and remember: there can
//  be no bravery without madness."
//    - The Ancestor, Darkest Dungeon (2016) 

#include "vehicleRoutingProblem.h"

// Confirms that all elements in the
// given vector are true
bool confirmAllVisited(std::vector<bool> beenVisited){
	for(bool temp : beenVisited){
		if(temp == false){
			return false;

		}

	}

	return true;

}

// Implementation of Nearest Neighbor Algorithm
// Finds the first obvious route between each
// point and, while not the most efficient, is
// fairly fast. Do note that this attempt at
// Nearest Neighbor does not play well with elemenents
// that have no neighbors. (eg some vertex H that
// shares no connections with any other vertex.)
std::list<std::string> nearestNeighbor(std::vector<std::vector<int>> graph){	
	// variables uses throughout function
	clock_t startTime = clock();
	int cost;
	int currRow = 0;
	int currShortestPath = 99999999999999999999999999999999999999999999999999999999;
	int next;
	std::list<std::string> pointsVisited;
	std::vector<bool> beenVisited(graph.size(), false);		

	// At least one time, each line of the 2D
	// vector will be run through this while loop
	do{
		// Each element in a row will be run through
		// this for-loop. If the element currently
		// "focused" on is less than the current shortest
		// path (as represented by a smaller number),
		// has NOT been visited yet, AND doesn't equal 0
		// (what I used to represent no border/the current
		// element) then it is made the next element and
		// variables are adjusted accordingly
		for(int currCol=0; currCol < graph[currRow].size(); currCol++){
			if(graph[currRow][currCol] < currShortestPath && graph[currRow][currCol] != 0 && beenVisited[currCol] == false){
				currShortestPath = graph[currRow][currCol];
				next=currCol;
				cost = graph[currRow][currCol];

			}

		}

		// If we are not on the last item, then this
		// if-statement runs, essentially resetting
		// the shortest path, setting the current row
		// to the next one, and adding the movement to
		// the list for the record.
		if(next != currRow){
			// The print statement below was used for testing, please ignore
			// std::cout << currRow << "->" << next << "; cost: " << cost << std::endl;
			pointsVisited.push_back(currRow + "->" + next);
			beenVisited[currRow] = true;
			currRow = next;
			currShortestPath = 99999999999999999999999999999999999999999999999999999999;

		// If we ARE on the last item, then "end" is
		// added to the end of the list and all elements
		// are marked as visited
		} else {
			std::cout << "End" << std::endl;
			pointsVisited.push_back("end");
			beenVisited[currRow] = true;


		}

	}while(confirmAllVisited(beenVisited) == false);

	// Prints the runtime of the function in seconds 
	// before returning the final list of elements
	std::cout << "Run Time: " << (clock() - startTime) / CLOCKS_PER_SEC << " seconds" << std::endl;
	return pointsVisited;

}
