#include <iostream>
#include <vector>
#include <math.h>
#include <Zelta/AI/Pathfinding.hpp>
#include <Zelta/AI/GridGraph.hpp>

int main() {

    // Let's define our map as a 2d int array.
    
    std::vector<std::vector<int>> map = {
        { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
        { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
        { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
        { 1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1,  1},
        { 1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1,  1},
        { 1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1,  1},
        { 1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1,  1},
        { 1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1,  1},
        {-1, -1, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1},
        { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
        { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
    };
    
    
    // zt::GridGraph represents our map.
    zt::GridGraph graph(map);
    graph.setNeighborhood(zt::GridGraph::Connections::EIGHT);
    
    // zt::Pathfinding is the algorithm that will find the path.
    zt::Pathfinding<zt::GridGraphNode> pathfinding(graph);
    
    // When a path is not found a exception is thrown.
    try {
        
        // We run the algorithm by calling getPath() and passing the origin and
        // destination nodes.
        // The path is returned as a vector of Nodes.
        std::vector<zt::GridGraphNode> path = pathfinding.getPath(graph.at(0,0), graph.at(10, 10));
        std::cout << "Path: " << path.size() << " steps" << std::endl;
        
        // Modify the array with the path and print it.
        
        for (const zt::GridGraphNode& step : path) {
            map[step.y][step.x] = 8; // We'll mark with a 8 the path.
        }
        
        for (auto& row : map) {
            for (auto& col : row) {
                if (col >= 0) std::cout << " ";
                std::cout << col;
            }
            std::cout << std::endl;
        }
        
        
        
        
    } catch (std::exception e) {
        std::cout << "No path found." << std::endl;
    }


    return 0;
}
