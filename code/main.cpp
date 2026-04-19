// File Name: main.cpp
// Author: Adam Campbell, Tyler Gill, Tristan Worthington
// Date: 4/19/2026
// Purpose: This is a brief idea for the main function
// 	    to be built from in the future

#include "vehicleRoutingProblem.h"

using namespace std;

int main(){
	vector<vector<int>> graph = {{0, 29, 82, 74, 32}, {29, 0, 55, 35, 46}, {82, 55, 0, 5, 65}, {74, 35, 5, 0, 70}, {32, 46, 65, 70, 0}};
	
	cout << "Nearest Neighbor Route" << endl;
	list<string> temp1 = nearestNeighbor(graph);
	for(std::string i : temp1){
		cout << i << endl;

	}

	cout << "Clark-Wright Route" << endl;
	list<string> temp2 = clarkWright(graph);
	for(std::string i : temp2){
		cout << i << endl;

	}

	cout << "Tabu Search Route" << endl;
	list<string> temp3 = tabuSearch(graph);
	for(std::string i : temp3){
		cout << i << endl;

	}

}

