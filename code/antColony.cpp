// antColony.cpp
#include "vehicleRoutingProblem.h"

class AntColonyOptimization {
private:
    std::vector<std::vector<double>> graph;
    std::vector<std::vector<double>> pheromone;
    int numNodes;
    int numAnts;
    int maxIterations;
    double alpha;      // Pheromone importance
    double beta;       // Distance importance
    double evaporation; // Pheromone evaporation rate
    double Q;          // Pheromone deposit factor
    std::mt19937 rng;

    // Calculate distance between two nodes
    double distance(int from, int to) const {
        return graph[from][to];
    }

    // Calculate probability of moving from current to next node
    double calculateProbability(int current, int next, const std::vector<bool>& visited) const {
        if (visited[next]) return 0.0;
        
        double pheromone_val = std::pow(pheromone[current][next], alpha);
        double distance_val = std::pow(1.0 / (distance(current, next) + 1e-10), beta);
        return pheromone_val * distance_val;
    }

    // Select next node using roulette wheel selection
    int selectNextNode(int current, const std::vector<bool>& visited) {
        std::vector<double> probabilities(numNodes);
        double totalProbability = 0.0;

        for (int i = 0; i < numNodes; i++) {
            probabilities[i] = calculateProbability(current, i, visited);
            totalProbability += probabilities[i];
        }

        if (totalProbability == 0.0) {
            // No valid moves, select first unvisited node
            for (int i = 0; i < numNodes; i++) {
                if (!visited[i]) return i;
            }
            return -1;
        }

        // Normalize probabilities
        for (int i = 0; i < numNodes; i++) {
            probabilities[i] /= totalProbability;
        }

        // Roulette wheel selection
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        double random = dist(rng);
        double cumulativeProbability = 0.0;

        for (int i = 0; i < numNodes; i++) {
            cumulativeProbability += probabilities[i];
            if (random <= cumulativeProbability) {
                return i;
            }
        }

        return numNodes - 1;
    }

    // Construct a solution using one ant
    std::vector<int> constructSolution() {
        std::vector<int> path;
        std::vector<bool> visited(numNodes, false);

        // Start from random node
        std::uniform_int_distribution<int> startDist(0, numNodes - 1);
        int current = startDist(rng);
        
        path.push_back(current);
        visited[current] = true;

        // Build path
        for (int i = 1; i < numNodes; i++) {
            int next = selectNextNode(current, visited);
            if (next == -1) break;
            
            path.push_back(next);
            visited[next] = true;
            current = next;
        }

        // Return to start
        path.push_back(path[0]);
        
        return path;
    }

    // Calculate total distance of a path
    double calculatePathDistance(const std::vector<int>& path) const {
        double totalDistance = 0.0;
        for (size_t i = 0; i < path.size() - 1; i++) {
            totalDistance += distance(path[i], path[i + 1]);
        }
        return totalDistance;
    }

    // Update pheromones on the path
    void updatePheromone(const std::vector<int>& path, double pathDistance) {
        double deltaPheromone = Q / pathDistance;
        
        for (size_t i = 0; i < path.size() - 1; i++) {
            int from = path[i];
            int to = path[i + 1];
            pheromone[from][to] += deltaPheromone;
            pheromone[to][from] += deltaPheromone;
        }
    }

    // Evaporate pheromone
    void evaporatePheromone() {
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                pheromone[i][j] *= (1.0 - evaporation);
                if (pheromone[i][j] < 0.01) {
                    pheromone[i][j] = 0.01;
                }
            }
        }
    }

public:
    AntColonyOptimization(const std::vector<std::vector<double>>& g)
        : graph(g), numNodes(g.size()), numAnts(std::max(10, numNodes)),
          maxIterations(100), alpha(1.0), beta(2.0), evaporation(0.1), Q(100.0),
          rng(std::random_device{}()) {
        
        // Initialize pheromone matrix
        pheromone.assign(numNodes, std::vector<double>(numNodes, 1.0));
    }

    // Main ACO algorithm
    std::list<std::string> solve() {
        std::vector<int> bestPath;
        double bestDistance = std::numeric_limits<double>::max();

        // Run algorithm for max iterations
        for (int iter = 0; iter < maxIterations; iter++) {
            // Evaporate pheromone
            evaporatePheromone();

            // Construct solutions with multiple ants
            for (int ant = 0; ant < numAnts; ant++) {
                std::vector<int> path = constructSolution();
                double pathDistance = calculatePathDistance(path);

                // Update best solution
                if (pathDistance < bestDistance) {
                    bestDistance = pathDistance;
                    bestPath = path;
                }

                // Update pheromone
                updatePheromone(path, pathDistance);
            }

        }

        // Convert path to list of strings
        std::list<std::string> result;
        for (size_t i = 0; i < bestPath.size(); i++) {
            result.push_back(std::to_string(bestPath[i]) + "->");
        }

	std::cout << "Total Distance: " << bestDistance << std::endl;
        return result;
    }

    // Setter methods for tuning parameters
    void setParameters(int ants, int iterations, double a, double b, double evap, double q) {
        numAnts = ants;
        maxIterations = iterations;
        alpha = a;
        beta = b;
        evaporation = evap;
        Q = q;
    }
};

// Main function to use in your main.cpp
std::list<std::string> antColony(std::vector<std::vector<double>> graph) {
    auto start = std::chrono::high_resolution_clock::now();
    AntColonyOptimization aco(graph); 
    std::list<std::string> returnList = aco.solve();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Run Time: " << elapsed.count() << " seconds" << std::endl;


    return returnList;

}
