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

#include <Zelta/AI/DiscoveredNode.hpp>
#include <Zelta/AI/IGraph.hpp>

namespace zt {
    /**
     * @brief A* algorithm implementation.
     */
    template <class NodeType>
    class Pathfinding {
    public:
        Pathfinding(const IGraph<NodeType>& graph);
        std::vector<NodeType> getPath(NodeType origin, NodeType destination);
        virtual ~Pathfinding();
    private:
        const IGraph<NodeType>& graph;
        std::set<DiscoveredNode<NodeType>> closedList;
        std::set<DiscoveredNode<NodeType>> openList;

        DiscoveredNode<NodeType> popOpenList();
        void addOrUpdateOpenList(const NodeType& node, const NodeType& previous, float g, float h);

        bool isClosed(const NodeType& node);

    };

}
#include <Zelta/AI/Pathfinding.tpp>

#endif /* ASTARALGORITHM_HPP */

