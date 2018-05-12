/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DiscoveredNode.hpp
 * Author: rafa
 *
 * Created on May 12, 2018, 1:01 PM
 */

#ifndef ZETALIB_DISCOVEREDNODE_HPP
#define ZETALIB_DISCOVEREDNODE_HPP

namespace zt {
    /**
     * @brief Represents a discovered node in the A* algorithm. This class is intended for
     * internal use.
     */
    template <class NodeType>
    class DiscoveredNode {
    public:
        float g;
        float h;
        NodeType node, previousNode;
        bool initial;

        DiscoveredNode(const NodeType& node, float g = 0, float h = 0) :
        node(node), g(g), h(h) {
            initial = true;
        }

        DiscoveredNode(const NodeType& node, const NodeType& previousNode, float g = 0, float h = 0) :
        node(node), previousNode(previousNode) {
            this->g = g;
            this->h = h;
            initial = false;
        }

        DiscoveredNode(const DiscoveredNode& other) {
            node = other.node;
            previousNode = other.previousNode;
            g = other.g;
            h = other.h;
            initial = other.initial;
        }
        
        DiscoveredNode() {}

        float f() const {
            return g + h;
        }

        inline bool operator==(const DiscoveredNode& other) const {
            return other.node == this->node;
        }

        bool operator<(const DiscoveredNode& other) const {
            return node < other.node;
        }

    };

}
#endif /* DISCOVEREDNODE_HPP */

