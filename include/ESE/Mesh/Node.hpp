/* 
 * File:   Node.h
 * Author: Rafa
 *
 * Created on 17 de marzo de 2015, 13:53
 */

#ifndef ESE_NODE_H
#define	ESE_NODE_H

#include <vector>
#include <string>
#include <iostream>

#include <ESE/Mesh/NodeDistance.hpp>

/**
 * Un nodo es cada uno de los vértices de los que se compone la malla. Cada nodo
 * tiene una posición y una serie de conexiones a otros nodos.
 */

namespace ESE {

    class Node {
    private:
        float x, y;
        std::string name;
        /*
         * La conexión a otros nodos se puede representar con NodeDistances.
         */
        std::vector<NodeDistance> connections;
    public:
        /**
         * Crea un nodo sin nombre y con posición nula.
         */
        Node();
        /**
         * @param x Posición horizontal del nodo.
         * @param y Posición vertical del nodo.
         * @param name Nombre del nodo.
         */
        Node(float x, float y, std::string name);
        virtual ~Node();

        /**
         * Añade un camino desde este nodo al nodo destination. El coste será
         * la distancia que hay entre ambos. <b>Nota:</b> Este nodo estará conectado
         * al nodo destination, pero destination no estará conectado a este nodo.
         * Si quieres hacer una conexión mutua @see addMutualConnection().
         * @param destination Nodo de destino.
         */
        void addConnection(Node * destination);
        /**
         * Añade una conexión entre este nodo y el nodo vinculado  nodeDistance con
         * el coste vinculado a nodeDistance. @see addConnection() @see addMutualConnection()
         * @param nodeDistance
         */
        void addConnection(NodeDistance nodeDistance);

        /**
         * Añade una conexión desde este nodo a destination y desde destination hacia
         * este nodo.
         * @param destination Nodo con el que vamos a conectar y que se conectará al
         * objeto en curso.
         */
        void addMutualConnection(Node * destination);
        /**
         * @see addMusutalConnection()
         * @see addConnection()
         * @param nodeDistance
         */
        void addMutualConnection(NodeDistance nodeDistance);

        /**
         * @return True si el nodo en curso está conectado a node. 
         */
        bool isConnectedTo(Node * node);
        /**
         * @return Devuelve la distancia a la que se encuentra el nodo conectado node.
         * Devolverá -1 si no hay conexión. 
         */
        float distanceToConnectedNode(Node * node);

        float getX() const;
        float getY() const;
        
        void setPosition(float x, float y);
        void move(float dX, float dY);

        std::string getName() const;

        unsigned int countConnectedNodes() const;

        /**
         * Operador sobrecargado para dar acceso directo a las conexiones del nodo.
         * @param Conexión que queremos obtener.
         * @return Referencia a la conexión que queremos obtener.
         */
        NodeDistance & operator[](int index);

    };
    
    NodeDistance * begin(Node &node);
    NodeDistance * end(Node &node);

}

#endif	/* NODE_H */

