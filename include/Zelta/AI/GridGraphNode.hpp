/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GridGraphNode.hpp
 * Author: rafa
 *
 * Created on May 14, 2018, 10:54 PM
 */

#ifndef ZELTALIB_GRIDGRAPHNODE_HPP
#define ZELTALIB_GRIDGRAPHNODE_HPP

namespace zt {

    class GridGraphNode {
    public:
        GridGraphNode() : x(-1), y(-1) { }
        GridGraphNode(int cost, int x, int y) : cost(cost), x(x), y(y) {
        }

        bool operator==(const GridGraphNode& other) const {
            return x == other.x && y == other.y; 
        }

        bool operator<(const GridGraphNode& other) const {
            if (x < other.x) return true;

            if (x > other.x) return false;

            if (y == other.y) return false;

            return y < other.y;
        }

        int x, y;
        int cost;

    };

}

#endif /* GRIDGRAPHNODE_HPP */

