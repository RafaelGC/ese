/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AStarAlgorithm.hpp
 * Author: rafa
 *
 * Created on January 2, 2018, 8:15 PM
 */

#ifndef ZELTALIB_PATHFINDING_HPP
#define ZELTALIB_PATHFINDING_HPP

#include <vector>
#include <set>

namespace zt {

    /**
     * @brief Represents a node in the A* algorithm. This class is intended for
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

    class INode {
    public:
        //virtual bool operator==(const INode& other) const = 0;
    };

    template <class NodeType>
    class IMesh {
    public:
        virtual std::vector<NodeType> getAdjacents(const NodeType& node) const = 0;
        virtual float cost(const NodeType& node1, const NodeType& node2) const = 0;
        virtual float estimate(const NodeType &node1, const NodeType& node2) const = 0;
    };

    /**
     * @brief A* algorithm implementation.
     */
    template <class NodeType>
    class Pathfinding {
    public:
        Pathfinding(const IMesh<NodeType>& mesh);
        std::vector<NodeType> getPath(NodeType origin, NodeType destination);
        virtual ~Pathfinding();
    private:
        const IMesh<NodeType>& mesh;
        std::set<DiscoveredNode<NodeType>> closedList;
        std::set<DiscoveredNode<NodeType>> openList;

        DiscoveredNode<NodeType> popOpenList();
        void addOrUpdateOpenList(const NodeType& node, const NodeType& previous, float g, float h);

        bool isClosed(const NodeType& node);

    };

}
#include <Zelta/AI/Pathfinding.tpp>

#endif /* ASTARALGORITHM_HPP */

