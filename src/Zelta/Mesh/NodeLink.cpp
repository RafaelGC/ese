/* 
 * File:   NodeLink.cpp
 * Author: Rafa
 * 
 * Created on 20 de marzo de 2015, 2:07
 */

#include <Zelta/Mesh/NodeLink.hpp>

namespace zt {

    NodeLink::NodeLink() :
    representingNode(nullptr), previousNode(nullptr), accumulatedCost(0.f), fixed(false) {
    }

    NodeLink::NodeLink(Node *representingNode, Node *previousNode, float accumulatedCost, bool fixed) :
    representingNode(representingNode),
    previousNode(previousNode),
    accumulatedCost(accumulatedCost),
    fixed(fixed) {
    }

    NodeLink::~NodeLink() {
    }

    void NodeLink::setRepresentingNode(Node* node) {
        representingNode = node;
    }

    void NodeLink::setPreviousNode(Node* node) {
        previousNode = node;
    }

    void NodeLink::setAccumulatedCost(float cost) {
        accumulatedCost = cost;
    }

    void NodeLink::setFixed(bool fixed) {
        this->fixed = fixed;
    }

    Node * NodeLink::getRepresentingNode() {
        return representingNode;
    }

    Node * NodeLink::getPreviousNode() {
        return previousNode;
    }

    float NodeLink::getAccumulatedCost() const {
        return accumulatedCost;
    }

    bool NodeLink::isFixed() const {
        return fixed;
    }

    bool NodeLink::operator<(const NodeLink& other) const {
        return getAccumulatedCost() < other.getAccumulatedCost();
    }

    bool NodeLink::operator>(const NodeLink& other) const {
        return getAccumulatedCost() > other.getAccumulatedCost();
    }

}