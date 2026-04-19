// File Name: tabuSearch.cpp
// Author: Tyler Gill
// Date: 4/19/2026
// Purpose: To implement the Tabu Search algorithm to try to find the most efficient route between a set of points
//
// "Do not go gentle into that good night,
// Rage, rage against the dying of the light." 
//      - Dylan Thomas

#include "vehicleRoutingProblem.h"

using namespace std;

const int TABU_TENURE = 7;
const int MAX_ITER = 100;

// Convert index → string label (0 -> "A", 1 -> "B", ...)
string toLabel(int i) {
    return string(1, 'A' + i);
}

// Compute total cost of given route
int computeCost(const vector<int>& route,
                const vector<vector<int>>& graph) {
    int cost = 0;
    //sums distance between consecutive nodes
    for (int i = 0; i < route.size() - 1; i++) {
        cost += graph[route[i]][route[i+1]];
    }
    // return to start
    cost += graph[route.back()][route[0]];
    return cost;
}

// Generate initial solution (0,1,2,...,n-1)
vector<int> initialSolution(int n) {
    vector<int> route(n);
    for (int i = 0; i < n; i++)
        route[i] = i;
    return route;
}

// Check tabu (whether or not move is forbidden)
bool isTabu(pair<int,int> move, const deque<pair<int,int>>& tabuList) {
    for (auto& t : tabuList) {
        if (t == move) return true;
    }
    return false;
}

// Tabu Search function
list<string> tabuSearch(vector<vector<int>> graph) {
    clock_t startTime = clock();

    int n = graph.size();

    vector<int> current = initialSolution(n);
    vector<int> best = current;

    int bestCost = computeCost(best, graph);

    deque<pair<int,int>> tabuList;

    for (int iter = 0; iter < MAX_ITER; iter++) {

        vector<int> bestNeighbor;
        int bestNeighborCost = numeric_limits<int>::max();
        pair<int,int> bestMove = {-1, -1};

        // Explore neighbors (swap i, j)
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                vector<int> neighbor = current;
                swap(neighbor[i], neighbor[j]);

                int cost = computeCost(neighbor, graph);

                pair<int,int> move = {neighbor[i], neighbor[j]};

                // Tabu check with aspiration
                if (isTabu(move, tabuList) && cost >= bestCost)
                    continue;

                if (cost < bestNeighborCost) {
                    bestNeighbor = neighbor;
                    bestNeighborCost = cost;
                    bestMove = move;
                }
            }
        }

        current = bestNeighbor;

        // Update tabu list
        tabuList.push_back(bestMove);
        if (tabuList.size() > TABU_TENURE)
            tabuList.pop_front();

        // Update global best
        if (bestNeighborCost < bestCost) {
            best = bestNeighbor;
            bestCost = bestNeighborCost;
        }
    }

    // Convert result to list<string>
    list<string> result;
    for (int node : best) {
        result.push_back(toLabel(node));
    }
    // optionally return to start
    result.push_back(toLabel(best[0]));
    
    cout << "Run Time: " << (clock() - startTime) / CLOCKS_PER_SEC << " seconds" << endl;

    return result;
}