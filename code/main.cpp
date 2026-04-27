// File Name: main.cpp
// Author: Adam Campbell, Tyler Gill, Tristan Worthington
// Date: 4/19/2026
// Purpose: This is a brief idea for the main function
// 	    to be built from in the future

#include "vehicleRoutingProblem.h"

using namespace std;

vector<vector<double>> loadTSPLIB(string filename) {
    ifstream in(filename);
    string line;
    bool read = false;

    vector<vector<double>> coords;

    while (getline(in, line)) {
        if (line.find("NODE_COORD_SECTION") != string::npos) {
            read = true;
            continue;
        }

        if (!read || line == "EOF" || line.empty()) continue;

        int id;
        double x, y;
        stringstream ss(line);
        ss >> id >> x >> y;

        coords.push_back({x, y});
    }

    int n = coords.size();
    vector<vector<double>> graph(n, vector<double>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double dx = coords[i][0] - coords[j][0];
            double dy = coords[i][1] - coords[j][1];
            graph[i][j] = sqrt(dx*dx + dy*dy);
        }
    }

    return graph;
}

int main(){
	// Vector of all datasets to ensure streamlined
	// testing
	vector<string> fileNames = {"berlin52.tsp", "burma14.tsp", "eil76.tsp", "kroA100.tsp", "kroA150.tsp", "kroA200.tsp", "ulysses22.tsp"};

	bool firstTime = true;

	cout << "NOTE: The numbers after the runtime represent the route from one node to the next" << endl;

	for(string fileName : fileNames){
		//New function for loading in dataset files 
		auto graph = loadTSPLIB(fileName);

		cout << "Dataset: " << fileName << endl;
		cout << "------------" << endl;

		cout << "Nearest Neighbor Route" << endl;
		list<string> temp1 = nearestNeighbor(graph);
		for(std::string i : temp1){
			cout << i;
	
		}
		cout << endl;

		cout << endl;
	
		cout << "Clark-Wright Route" << endl;
		list<string> temp2 = clarkWright(graph);
		for(std::string i : temp2){
			cout << i << endl;
	
		}
	
		cout << endl;

		cout << "Tabu Search Route" << endl;
		list<string> temp3 = tabuSearch(graph);
		for(std::string i : temp3){
			cout << i << "->";
	
		}
		cout << endl;
		cout << endl;

		cout << "Ant Colony Optimization" << endl;
		list<string> temp4 = antColony(graph);
		for(std::string i : temp4){
			cout << i;

		}

		cout << endl << endl;
		
	}

}
