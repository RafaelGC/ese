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
    
    Node ** begin(Mesh & mesh){
        return &mesh[0];
    }
    
    Node ** end(Mesh & mesh){
        return &mesh[0]+mesh.countNodes();
    }

}


