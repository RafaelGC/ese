/* 
 * File:   NodeLink.h
 * Author: Rafa
 *
 * Created on 20 de marzo de 2015, 2:07
 */

#ifndef ZELTALIB_NODELINK_H
#define	ZELTALIB_NODELINK_H

#include <Zelta/Mesh/Node.hpp>

namespace zt {

    class NodeLink {
    private:
        Node * representingNode;
        Node * previousNode;
        float accumulatedCost;
        bool fixed;

    public:
        NodeLink();
        NodeLink(Node *representingNode, Node *previousNode, float accumulatedCost, bool fixed = false);
        virtual ~NodeLink();

        void setRepresentingNode(Node* node);
        void setPreviousNode(Node* node);
        void setAccumulatedCost(float cost);
        void setFixed(bool fixed);

        Node * getRepresentingNode();
        Node * getPreviousNode();
        float getAccumulatedCost() const;
        bool isFixed() const;

        bool operator<(const NodeLink &other) const;
        bool operator>(const NodeLink &other) const;

    };

}

#endif	/* NODELINK_H */

