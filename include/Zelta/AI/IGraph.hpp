/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IGraph.hpp
 * Author: rafa
 *
 * Created on May 12, 2018, 1:13 PM
 */

#ifndef ZETALIB_IGRAPH_HPP
#define ZETALIB_IGRAPH_HPP

namespace zt {
    /**
     * 
     */
    template <class NodeType>
    class IGraph {
    public:
        virtual std::vector<NodeType> getAdjacents(const NodeType& node) const = 0;
        virtual float cost(const NodeType& node1, const NodeType& node2) const = 0;
        virtual float estimate(const NodeType &node1, const NodeType& node2) const = 0;
    };

}

#endif /* IGRAPH_HPP */

