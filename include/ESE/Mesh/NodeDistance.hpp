/* 
 * File:   NodeDistance.hpp
 * Author: Rafa
 *
 * Created on 17 de marzo de 2015, 14:58
 */

#ifndef ESE_NODEDISTANCE_HPP
#define	ESE_NODEDISTANCE_HPP

#include <cmath>

class Node;

/**
 * NodeDistance representa la distancia a cierto nodo. Puede ser utilizado para
 * representar las conexiones entre nodos.
 * Al aplicar algoritmos como Dijkstra, realmente no nos interesa en absoluto la
 * posición de un nodo respecto a otro. Lo que nos interesa es saber el coste
 * que tiene llegar a ese nodo. Ese es el objetivo general de esta clase, representar
 * el coste hacia un nodo.
 */
class NodeDistance {
private:
    Node * node;
    float distance;
public:
    NodeDistance(Node *node, float distance);

    virtual ~NodeDistance();

    float getDistance() const;
    Node * getNode();
    
    void setNode(Node *node);
    void setDistance(float distance);
    
    static float distanceBetween(Node *node1, Node* node2);
};

#endif	/* NODEDISTANCE_HPP */

