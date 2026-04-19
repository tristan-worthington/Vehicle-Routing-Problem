// File Name: nearestNeighbot.cpp
// Author: Tristan Worthington
// Date: 4/19/2026
// Purpose: To implement the Nearest Neighbor search
//	    algorithm to try to find the most efficient
//	    route between a set of points
//
// NOTE:
// Within this function file, no code
// was written with generative AI and
// was written by a human.
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
	// Variables uses throughout function
	clock_t startTime = clock();
	int cost;
	int currRow = 0;
	const int DEFAULT_SHORTEST_PATH = 9999999;
	int currShortestPath = DEFAULT_SHORTEST_PATH;
	int next;
	std::list<std::string> pointsVisited;
	std::vector<bool> beenVisited(graph.size(), false);

	// At least one time, each line of the 2D
	// vector will be run through this while loop
	do{
		// Iterates over each column in a given row
		for(int currCol=0; currCol < graph[currRow].size(); currCol++){
			// If a shortest path is found, sets the next target
			// row to the column that has the shortest path
			if(graph[currRow][currCol] < currShortestPath && graph[currRow][currCol] != 0 && beenVisited[currCol] == false){
				currShortestPath = graph[currRow][currCol];
				next=currCol;
				cost = graph[currRow][currCol];

			}

		}

		// If the current row isn't the last:
		//  - Resets currShortestPath and next row is set
		//  - updates the current row to true in beenVisited
		//  - pointsVisited list is updated
		if(next != currRow){
			// The print statement below was used for testing, please ignore
			// std::cout << currRow << "->" << next << "; cost: " << cost << std::endl;
			pointsVisited.push_back(toLabel(currRow) + "->" + toLabel(next));
			beenVisited[currRow] = true;
			currRow = next;
			currShortestPath = DEFAULT_SHORTEST_PATH;

		// If the current row is the last:
		//  - pointsVisited is updated
		//  - current row is marked as true in beenVisited
		} else {
			//std::cout << "End" << std::endl;
			pointsVisited.push_back("end");
			beenVisited[currRow] = true;

		}

	}while(confirmAllVisited(beenVisited) == false);

	// Prints the runtime of the function in seconds 
	// before returning the final list of elements
	std::cout << "Run Time: " << (clock() - startTime) / CLOCKS_PER_SEC << " seconds" << std::endl;
	return pointsVisited;

}
