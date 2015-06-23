/* 
 * File:   Dijkstra.cpp
 * Author: Rafa
 * 
 * Created on 17 de marzo de 2015, 23:57
 */

#include <ESE/Mesh/Dijkstra.hpp>

namespace ESE {

    Dijkstra::Dijkstra() {
    }

    Dijkstra::~Dijkstra() {
    }

    std::deque<Node*> Dijkstra::pathTo(Node* origin, Node* destination) {
        //Paso sistemático: añadir al vector de NodeLink
        //el nodo de origen.

        //Bucle: mientras haya un nodo no fijo.

        nodeLinks.push_back(NodeLink(origin, nullptr, 0, true));
        currentNodeLink = &nodeLinks[0];

        while (true) {
            //Búsqueda de adyacentes.
            std::vector<NodeLink> adjacentNodes = getAdjacentNonFixedNodes();

            addOrImprovePath(adjacentNodes);
            currentNodeLink = getSmallestNotFixedNodeLink();
            //No se ha encontrado ningún NodeLink no fijo. Fin del algoritmo.
            if (!currentNodeLink) {
                break;
            }

            currentNodeLink->setFixed(true);
            if (currentNodeLink->getRepresentingNode() == destination) {
                break;
            }

        }

        std::deque<Node*> returnPath;

        Node* lookingNode = destination;
        for (auto it = nodeLinks.rbegin(); it != nodeLinks.rend(); ++it) {

            if (it->getRepresentingNode() == lookingNode) {
                returnPath.push_front(lookingNode);
                lookingNode = it->getPreviousNode();
                if (it->getRepresentingNode() == nullptr) {
                    break;
                }
                it = nodeLinks.rbegin(); //Reiniciar búsqueda.

            }
        }
        return returnPath;

    }

    std::vector<NodeLink> Dijkstra::getAdjacentNonFixedNodes() {
        std::vector<NodeLink> output;
        //Para trabajar con más comodidad y para evitar excesivas llamadas a métodos
        //guardo los atributos en dos variables locales.
        float baseCost = currentNodeLink->getAccumulatedCost();
        Node *currentNode = currentNodeLink->getRepresentingNode();

        //Para cada nodo adyacente a currentNode.
        for (NodeDistance & nodeDistance : *(currentNode)) {
            //Miramos si no está fijo. Si está fijo se ignora.
            if (!isFixedNode(nodeDistance.getNode())) {
                //Cuando no lo está, guardamos la información relevante en el vector
                //de salida. La información será interpretada después.
                output.push_back(
                        NodeLink(nodeDistance.getNode(),
                        currentNode,
                        baseCost + nodeDistance.getDistance()));
            }
        }

        return output;
    }

    bool Dijkstra::isFixedNode(Node* node) {
        for (NodeLink & nodeLink : nodeLinks) {
            if (nodeLink.getRepresentingNode() == node) {
                return nodeLink.isFixed();
            }
        }
        return false;
    }

    void Dijkstra::addOrImprovePath(std::vector<NodeLink>& nodes) {
        //Buscar si ya hay un representing node que coincida con alguno de los de nodes.
        //Si no, añadir.

        for (NodeLink &node : nodes) {
            bool found = false;
            for (NodeLink &nodeLink : nodeLinks) {

                if (node.getRepresentingNode() == nodeLink.getRepresentingNode()) {
                    if (node.getAccumulatedCost() < nodeLink.getAccumulatedCost()) {
                        //Update.
                        nodeLink.setPreviousNode(node.getPreviousNode());
                        nodeLink.setAccumulatedCost(node.getAccumulatedCost());
                    }
                    found = true;
                    break;
                }

            }

            if (!found) {
                nodeLinks.push_back(node);
            }

        }
    }

    NodeLink * Dijkstra::getSmallestNotFixedNodeLink() {
        NodeLink * smallest = nullptr;
        for (NodeLink & nodeLink : nodeLinks) {
            if (!nodeLink.isFixed()) {
                if (smallest == nullptr) {
                    smallest = &nodeLink;
                    continue;
                }
                if (nodeLink < (*smallest)) {
                    smallest = &nodeLink;
                }
            }
        }
        return smallest;
    }

}