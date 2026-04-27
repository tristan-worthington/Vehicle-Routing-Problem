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

// Compute total cost of given route
double computeCost(const std::vector<int>& route,
                const std::vector<std::vector<double>>& graph) {
    double cost = 0;
    //sums distance between consecutive nodes
    for (int i = 0; i < route.size() - 1; i++) {
        cost += graph[route[i]][route[i+1]];
    }
    // return to start
    cost += graph[route.back()][route[0]];
    return cost;
}

// Generate initial solution (0,1,2,...,n-1)
std::vector<int> initialSolution(int n) {
    std::vector<int> route(n);
    for (int i = 0; i < n; i++)
        route[i] = i;
    return route;
}

// Check tabu (whether or not move is forbidden)
bool isTabu(pair<int,int> move, const std::deque<pair<int,int>>& tabuList) {
    for (auto& t : tabuList) {
        if (t == move) return true;
    }
    return false;
}

string toLabel(int node) {
    return to_string(node);
}

// Tabu Search function
std::list<string> tabuSearch(std::vector<std::vector<double>> graph) {
    clock_t startTime = clock();

    int n = graph.size();

    std::vector<int> current = initialSolution(n);
    std::vector<int> best = current;

    double bestCost = computeCost(best, graph);

    std::deque<pair<int,int>> tabuList;

    for (int iter = 0; iter < MAX_ITER; iter++) {

        std::vector<int> bestNeighbor;
        double bestNeighborCost = numeric_limits<double>::max();
        pair<int,int> bestMove = {-1, -1};

        // Explore neighbors (swap i, j)
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                std::vector<int> neighbor = current;
                swap(neighbor[i], neighbor[j]);

                int cost = computeCost(neighbor, graph);

                pair<int,int> move = {current[i], current[j]};

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
    std::list<string> result;
    for (int node : best) {
        result.push_back(toLabel(node));
    }
    // optionally return to start
    result.push_back(toLabel(best[0]));
    
    int finalCost = computeCost(best, graph);
    std::cout << "Total distance: " << finalCost << std::endl;
    cout << "Run Time: " << (clock() - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    
    return result;
}
