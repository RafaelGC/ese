/* 
 * File:   NodeDistance.cpp
 * Author: Rafa
 * 
 * Created on 17 de marzo de 2015, 14:58
 */

#include <ESE/Mesh/NodeDistance.hpp>
#include <ESE/Mesh/Node.hpp>

namespace ESE {

    NodeDistance::NodeDistance(Node *node, float distance) :
    node(node), distance(distance) {
    }

    NodeDistance::~NodeDistance() {
    }

    float NodeDistance::getDistance() const {
        return distance;
    }

    Node * NodeDistance::getNode() {
        return node;
    }

    void NodeDistance::setDistance(float distance) {
        this->distance = distance;
    }

    void NodeDistance::setNode(Node* node) {
        this->node = node;
    }

    float NodeDistance::distanceBetween(Node* node1, Node* node2) {
        float difX = fabs(node1->getX() - node2->getX());
        float difY = fabs(node1->getY() - node2->getY());
        return sqrt(difX * difX + difY * difY);
    }

}