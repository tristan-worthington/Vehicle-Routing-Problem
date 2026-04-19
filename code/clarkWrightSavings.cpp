// File Name: clarkWrightSavings.cpp
// Author: Adam Campbell
// Date: 4/19/26
// Purpose: Implementing the Clark-Wright Savings Algorithm to find the most efficient 
// route between a set of points

#include "vehicleRoutingProblem.h"

// Convert index to string label
std::string toLabel(int i) {
    return std::string(1, 'A' + i);
}

// Represents a saving: merging the routes that serve
// node i and node j yields a cost reduction of 'saving'
struct Saving {
    int i, j;
    int saving;
};

// Compute the Clark-Wright saving value for nodes i and j
// given depot at index 0
int computeSaving(int i, int j, const std::vector<std::vector<int>>& graph) {
    int depot = 0;
    return graph[depot][i] + graph[depot][j] - graph[i][j];
}

// Find which route a given node belongs to
// Returns the index into 'routes', or -1 if not found
int findRoute(int node, const std::vector<std::vector<int>>& routes) {
    for (int r = 0; r < (int)routes.size(); r++) {
        for (int n : routes[r]) {
            if (n == node) return r;
        }
    }
    return -1;
}

// Check whether a node is an interior node of its route
bool isInterior(int node, const std::vector<int>& route) {
    if (route.empty()) return false;
    return (route.front() != node && route.back() != node);
}

// Clark-Wright Savings Implementation:
// Assumes node 0 is the depot, all other nodes are customers
// Each customer begins on its own route (depot -> customer -> depot)
// Routes are then merged greedily by descending savings value
// Return a list of strings describing each final route
std::list<std::string> clarkWright(std::vector<std::vector<int>> graph) {
    clock_t startTime = clock();

    int n = graph.size();
    int depot = 0;

    // Builds initial savings list
    // the individual routes are merged to compute savings
    std::vector<Saving> savings;
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int s = computeSaving(i, j, graph);
            savings.push_back({i, j, s});
        }
    }

    // Sort savings in descending order
    std::sort(savings.begin(), savings.end(), [](const Saving& a, const Saving& b) {
        return a.saving > b.saving;
    });

    // Initialize Routes
    std::vector<std::vector<int>> routes;
    for (int i = 1; i < n; i++) {
        routes.push_back({i});
    }

    // For each saving (i, j), in descending order:
    // Find which routes i and j currently belong to
    // Skip if they are already on the same route
    // Skip if either node is interior to its route (only endpoints can be joined to another route)
    // append one route onto the end of the other,
    // reversing as needed so the join point is at the boundary
    for (const Saving& sv : savings) {
        int ri = findRoute(sv.i, routes);
        int rj = findRoute(sv.j, routes);

        // If already on the same route merging would create a sub-tour
        if (ri == rj) continue;

        // Both nodes kept at the end/start of their respective routes
        if (isInterior(sv.i, routes[ri])) continue;
        if (isInterior(sv.j, routes[rj])) continue;

        // Normalise so that sv.i is at the BACK of route ri
        // and sv.j is at the FRONT of route rj
        if (routes[ri].front() == sv.i) {
            std::reverse(routes[ri].begin(), routes[ri].end());
        }
        if (routes[rj].back() == sv.j) {
            std::reverse(routes[rj].begin(), routes[rj].end());
        }

        // Merge rj onto the end of ri
        for (int node : routes[rj]) {
            routes[ri].push_back(node);
        }

        // Remove route rj
        routes.erase(routes.begin() + rj);
    }

    // Output strings
    // Each route is expressed as: depot -> A -> B -> ... -> depot
    std::list<std::string> result;
    for (const std::vector<int>& route : routes) {
        std::string routeStr = toLabel(depot);
        for (int node : route) {
            routeStr += "->" + toLabel(node);
        }
        routeStr += "->" + toLabel(depot);
        result.push_back(routeStr);
    }

    std::cout << "Run Time: " << (clock() - startTime) / CLOCKS_PER_SEC << " seconds" << std::endl;
    return result;
}
