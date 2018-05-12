#include <iostream>
#include <vector>
#include <math.h>
#include <Zelta/AI/Pathfinding.hpp>

class Node : public zt::INode {
public:
    Node() : x(-1), y(-1) { }
    Node(char type, int x, int y) : type(type), x(x), y(y) {
    }
    
    bool operator==(const Node& other) const {
        return x == other.x && y == other.y; 
    }
    
    bool operator<(const Node& other) const {
        if (x < other.x) return true;

        if (x > other.x) return false;

        if (y == other.y) return false;

        return y < other.y;
    }

    float x, y;
    char type;
    
};

class Mesh : public zt::IMesh<Node> {
public:
    Mesh(std::vector<std::vector<Node>>& map) : map(map){
        h = map.size();
        w = map[0].size();
    }
    
    // Helper method to get a Node (a cell in the map)
    // by it's position.
    const Node& at(int x, int y) const {
        return map[y][x];
    }
    
    // Helper method that returns true when the cell at x,y
    // can't be passed through (is solid).
    bool isSolid(int x, int y) const {
        return at(x,y).type == '#'; // '#' represents wall.
    }
    
    // We need to implement this method for the A* algorithm to work.
    // Given a Node of our map, this method must return adjacent
    // Nodes.
    // In essence, this method defines what are your neighbours,
    // where you can and cannot go from a certain node.
    std::vector<Node> getAdjacents(const Node& node) const {
        std::vector<Node> adjacents;
        
        // If the node it's not on the left limit of the map then
        // we have a neighbour on the left.
        if (node.x > 0 && !isSolid(node.x - 1, node.y)) {
            adjacents.push_back(at(node.x - 1, node.y));
        }
        
        // If the node it's not on the right limit of the map then
        // we have a neighbour on the right.
        if (node.x < w - 1 && !isSolid(node.x + 1, node.y)) {
            adjacents.push_back(at(node.x + 1, node.y));
        }
        
        // The same for the vertical position...
         
        if (node.y > 0 && !isSolid(node.x, node.y - 1)) {
            adjacents.push_back(at(node.x, node.y - 1));
        }
        
        if (node.y < h - 1 && !isSolid(node.x, node.y + 1)) {
            adjacents.push_back(at(node.x, node.y + 1));
        }
        
        return adjacents;
    }
    
    // We need to implement this method.
    // Given two nodes, it must return the cost of going from node1
    // to node2.
    // Since in our example the adjacent cells are the ones which
    // are in top, bottom, left and right all of them should have
    // the same cost, 1.
    float cost(const Node& node1, const Node& node2) const {
        return 1;
    }
    
    // We need to implement this method. Represents the heuristic 
    // in the A* algorithm
    // Given two nodes (that may not be neighbours) we
    // must estimate the cost of going from node1 to node2.
    // If you want the path to be optimum the heuristic needs to be
    // admissible. In our case the Pythagorean theorem fits perfectly.
    // If you don't know what heuristic to use you can just return 0,
    // that way it'll be admissible so will return the optimum path,
    // but the algorithm execution will be slower.
    float estimate(const Node &node1, const Node& node2) const {
        /*return std::sqrt((node1.x - node2.x) * (node1.x - node2.x) +
            (node1.y - node2.y) * (node1.y - node2.y));*/
        return 0;
    }
    
private:
    int w, h;
    std::vector<std::vector<Node>> map;
};

int main() {

    // Let's define our map as a 2d char array.
    
    char map[8][8] = {
        {'0', '#', '0', '0', '0', '0', '0', '0'},
        {'0', '#', '0', '#', '#', '0', '0', '0'},
        {'0', '#', '0', '#', '0', '0', '#', '0'},
        {'0', '#', '0', '#', '0', '#', '#', '0'},
        {'0', '#', '0', '#', '0', '0', '#', '0'},
        {'0', '#', '0', '#', '0', '0', '#', '0'},
        {'0', '0', '0', '#', '0', '0', '#', '0'},
        {'0', '#', '0', '#', '0', '0', '0', '0'}
    };
    
    // The Pathfinding class, which implements the A* algorithm,
    // needs that each cell of the map is represented by objects
    // of a class with the == operator implemented. The operator
    // will return true when two Nodes represents the same one
    // in the map.
    // So, the map array is not really useful yet. We will have
    // to define the same map but using objects with the == operator
    // implemented that way.
    
    std::vector<std::vector<Node>> nodeMap;
    
    for (int y = 0; y < 8; y++) {
        // Create a new row:
        nodeMap.push_back(std::vector<Node>());
        
        // Populate that row with the columns:
        for (int x = 0; x < 8; x++) {
            nodeMap.back().push_back(
                Node(
                    map[y][x],
                    x,
                    y)
            );
        
        }
    }
    
    Mesh mesh(nodeMap);
    
    // Let's create a zt::Pathfinding class that implements
    // the search algorithm.
    
    zt::Pathfinding<Node> pathfinding(mesh);
    
    // When a path is not found a exception is thrown.
    try {
        
        // The path is returned as a vector of Nodes.
        // We run the .getPath algorithm passing the origin and destination nodes.
        std::vector<Node> path = pathfinding.getPath(mesh.at(0,0), mesh.at(7, 7));
        std::cout << "Path: " << path.size() << " steps" << std::endl;
        
        
    } catch (std::exception e) {
        std::cout << "No path found." << std::endl;
    }


    return 0;
}
