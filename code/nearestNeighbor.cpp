// File Name: nearestNeighbot.cpp
// Author: Tristan Worthington
// Date: 4/19/2026
// Purpose: To implement the Nearest Neighbor search
//	    algorithm to try to find the most efficient
//	    route between a set of points
//
// "So steel yourself and remember: there can
//  be no bravery without madness."
//    - The Ancestor, Darkest Dungeon (2016) 

// TODO:
// - Make sure this actually works
// - Check and see if this is actually
//   nearest neighbor, 2am me cannot be
//   trusted
// - implement end condition for while
//   loop

#include "vehicleRoutingProblem.h"
using namespace std;

// Implementation of Nearest Neighbor Algorithm
// Finds the first obvious route between each
// point and, while not the most efficient, is
// fairly fast.
//
// NOTE: This was written a ~2am so it may
// 	 not be comprehendable or even right
// 	 I just wanted to have something to
// 	 work off of when I wake up tomorrow
// 	 All of this is subject to change.
// 	 - T
void nearestNeighbor(vector<vector<int>> graph){
	int shortestPath = 255;
	vector<bool> beenVisited(graph.size(), false);
	list<string> pointsVisited;
	int y = 0;
	int nextY;

	//Iterates over the rows before 
	do{
		if(beenVisited[y] == false){ 
			for(int x=0; x < graph[y].size(); x++){
				if(graph[y][x] < shortestPath){
					shortestPath = graph[y][x];
					nextY = Y;

				}
	
			}
			
			beenVisted[y] = true;
			pointsVisited.push_back(y << "->" << x);

		}

	// TODO: Add proper end condition
	//	 to the loop so it doesn't
	//	 possibly error out.
	}while();

}
