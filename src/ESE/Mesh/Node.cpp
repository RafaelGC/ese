/* 
 * File:   Node.cpp
 * Author: Rafa
 * 
 * Created on 17 de marzo de 2015, 13:53
 */

#include <vector>

#include <ESE/Mesh/Node.hpp>

namespace ESE {

    Node::Node(float x, float y, std::wstring name) :
    x(x), y(y), name(name) {
    }

    Node::~Node() {
    }

    void Node::addConnection(Node * destination) {
        connections.push_back(
                NodeDistance(
                destination,
                NodeDistance::distanceBetween(this, destination)
                )
                );
    }

    void Node::addConnection(NodeDistance nodeDistance) {
        connections.push_back(nodeDistance);
    }

    void Node::addMutualConnection(Node* destination) {
        addConnection(destination);
        destination->addConnection(this);
    }

    void Node::addMutualConnection(NodeDistance nodeDistance) {
        addConnection(nodeDistance);
        nodeDistance.getNode()->addConnection(NodeDistance(this, nodeDistance.getDistance()));
    }

    bool Node::isConnectedTo(Node* node) {
        for (NodeDistance &n : connections) {
            if (n.getNode() == node) {
                return true;
            }
        }
        return false;
    }

    float Node::distanceToConnectedNode(Node* node) {
        for (NodeDistance &n : connections) {
            if (n.getNode() == node) {
                return n.getDistance();
            }
        }
        return -1;
    }

    float Node::getX() const {
        return x;
    }

    float Node::getY() const {
        return y;
    }
    
    void Node::setPosition(float x, float y) {
        this->x = x;
        this->y = y;
    }
    
    void Node::move(float dX, float dY) {
        x+=dX;
        y+=dY;
    }

    std::wstring Node::getName() const {
        return name;
    }

    NodeDistance & Node::operator[](int index) {
        return connections[index];
    }

    unsigned int Node::countConnectedNodes() const {
        return connections.size();
    }
    
    /*Compatibilidad con el bucle for de rango*/
    NodeDistance * begin(Node &node) {
        return &node[0];
    }

    NodeDistance * end(Node &node) {
        return &node[0] + node.countConnectedNodes();
    }

}