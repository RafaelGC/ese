/* 
 * File:   Mesh.cpp
 * Author: Rafa
 * 
 * Created on 17 de marzo de 2015, 13:49
 */

#include <ESE/Mesh/Mesh.hpp>

namespace ESE{

    Mesh::Mesh() {
        deleteNodesInDestructor = true;
    }

    Mesh::~Mesh() {
        if (deleteNodesInDestructor){
            for (Node * node : nodes){
                delete node;
            }
        }
    }

    void Mesh::addNode(Node* node){
        nodes.push_back(node);
    }

    Node * &Mesh::operator [](int index){
        return nodes[index];
    }

    unsigned int Mesh::countNodes(){
        return nodes.size();
    }
    
    Node * Mesh::closestNodeTo(float x, float y) {
        Node * closest = nullptr;
        float currClosestSqDist = -1.f;
        for (auto i : *this) {
            if (currClosestSqDist==-1.f) {
                closest = i;
                currClosestSqDist = fabs(x-i->getX())*fabs(x-i->getX()) +
                                    fabs(y-i->getY())*fabs(y-i->getY());
            }
            else {
                float tmp = fabs(x-i->getX())*fabs(x-i->getX()) +
                                    fabs(y-i->getY())*fabs(y-i->getY());
                if (tmp<currClosestSqDist) {
                    closest = i;
                    currClosestSqDist = tmp;
                }
            }
        }
        
        return closest;
    }
    
    void Mesh::move(float dX, float dY) {
        for (auto node : nodes) {
            node->move(dX,dY);
        }
    }
    
    Node ** begin(Mesh & mesh){
        return &mesh[0];
    }
    
    Node ** end(Mesh & mesh){
        return &mesh[0]+mesh.countNodes();
    }

}


