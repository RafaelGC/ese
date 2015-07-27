/* 
 * File:   Dijkstra.hpp
 * Author: Rafa
 *
 * Created on 17 de marzo de 2015, 23:57
 */

#ifndef ESE_DIJKSTRA_HPP
#define	ESE_DIJKSTRA_HPP

#include <ESE/Mesh/Mesh.hpp>
#include <ESE/Mesh/Node.hpp>
#include <ESE/Mesh/NodeDistance.hpp>
#include <ESE/Mesh/NodeLink.hpp>

#include <iostream>
#include <deque>

namespace ESE {

    class Dijkstra {
    private:
        std::vector<NodeLink> nodeLinks;
        NodeLink *currentNodeLink;
    public:
        Dijkstra();
        virtual ~Dijkstra();
        /**
         * Aplica el algoritmo de Dijkstra para encontrar el camino más corto entre
         * dos nodos de una malla.
         * @param origin Nodo origen.
         * @param destination Nodo destino.
         * @return Cola que contiene los nodos que hay que atravesar para llegar desde
         * origin hasta destination, ambos inclusive.
         */
        std::deque<Node*> pathTo(Node * origin, Node *destination);
    protected:
        /**
         * @return Devuelve un vector de NodeLinks de los nodos adyacentes al nodo
         * actual (atributo de la clase). 
         */
        std::vector<NodeLink> getAdjacentNonFixedNodes();

        /**
         * @param node Nodo del que queremos saber si está fijo.
         * @return True si el nodo está fijo. 
         */
        bool isFixedNode(Node *node);
        /**
         * Este método comprueba si hay algún camino mejor hacia los nodos que se
         * pasan como parámetros. De no haber uno mejor, se añade a nodeLinks el nodo
         * que no se ha encontrado.
         * @param nodes Vector de nodos que queremos estudiar.
         */
        void addOrImprovePath(std::vector<NodeLink> &nodes);

        /**
         * @return Devuelve aquel NodeLink de nodeLinks que tiene un coste mejor. 
         */
        NodeLink * getSmallestNotFixedNodeLink();


    };

}

#endif	/* ESE_DIJKSTRA_HPP */

