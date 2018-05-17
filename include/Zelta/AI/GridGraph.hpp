/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GridGraph.hpp
 * Author: rafa
 *
 * Created on May 14, 2018, 10:53 PM
 */

#ifndef ZELTALIB_GRIDGRAPH_HPP
#define ZELTALIB_GRIDGRAPH_HPP

#include <Zelta/AI/GridGraphNode.hpp>
#include <vector>
#include <math.h>

namespace zt {

    class GridGraph : public zt::IGraph<GridGraphNode> {
    public:
        enum class Connections { FOUR, EIGHT };
        
        GridGraph() {
            w = h = 0;
            neighborhood = Connections::EIGHT;
        }
        
        GridGraph(std::vector<std::vector<int>>& map) {
            neighborhood = Connections::EIGHT;
            setMap(map);
            
        }

        GridGraph(std::vector<std::vector<GridGraphNode>>&map) {
            neighborhood = Connections::EIGHT;
            setMap(map);
        }
        
        void setMap(std::vector<std::vector<GridGraphNode>>&map) {
            h = map.size();
            w = map[0].size();
            this->map = map;
        }
        
        void setMap(std::vector<std::vector<int>>& map) {
            this->map.clear();
            h = map.size();
            w = map[0].size();
            
            for (int y = 0; y < h; y++) {
                // Create a new row:
                this->map.push_back(std::vector<GridGraphNode>());

                // Populate that row with the columns:
                for (int x = 0; x < w; x++) {
                    this->map.back().push_back(
                            GridGraphNode(
                            map[y][x], x, y));

                }
            }
            
        }
        
        void setNeighborhood(Connections neighborhood) {
            this->neighborhood = neighborhood;
        }

        // Helper method to get a Node (a cell in the map)
        // by it's position.

        const GridGraphNode& at(int x, int y) const {
            return map[y][x];
        }

        // Helper method that returns true when the cell at x,y
        // can't be passed through (is solid).

        bool isSolid(int x, int y) const {
            return at(x, y).cost == -1; // '-1' represents solid tile.
        }

        // We need to implement this method for the A* algorithm to work.
        // Given a Node of our map, this method must return adjacent
        // Nodes.
        // In essence, this method defines what are your neighbours,
        // where you can and cannot go from a certain node.

        std::vector<GridGraphNode> getAdjacents(const GridGraphNode& node) const {
            std::vector<GridGraphNode> adjacents;

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
            
            // If the neighborhood is set to EIGHT we must also consider
            // diagonal nodes.
            if (neighborhood == Connections::EIGHT) {
                if (node.x > 0 && node.y > 0 && !isSolid(node.x - 1, node.y - 1)) {
                    adjacents.push_back(at(node.x - 1, node.y - 1));
                }

                if (node.x < w - 1 && node.y > 0 && !isSolid(node.x + 1, node.y - 1)) {
                    adjacents.push_back(at(node.x + 1, node.y - 1));
                }

                if (node.x < w - 1 && node.y < h  - 1 && !isSolid(node.x + 1, node.y + 1)) {
                    adjacents.push_back(at(node.x + 1, node.y + 1));
                }

                if (node.x > 0 && node.y < h - 1 && !isSolid(node.x - 1, node.y + 1)) {
                    adjacents.push_back(at(node.x - 1, node.y + 1));
                }
            }

            return adjacents;
        }

        float cost(const GridGraphNode& node1, const GridGraphNode& node2) const {
            return ((node1.x == node2.x || node1.y == node2.y) ? 1 : 1.4142) + node2.cost;
        }

        float estimate(const GridGraphNode &node1, const GridGraphNode& node2) const {
            return std::sqrt((node1.x - node2.x) * (node1.x - node2.x) +
                    (node1.y - node2.y) * (node1.y - node2.y));

        }

    private:
        int w, h;
        Connections neighborhood;
        std::vector<std::vector<GridGraphNode>> map;
    };

}

#endif /* GRIDGRAPH_HPP */

