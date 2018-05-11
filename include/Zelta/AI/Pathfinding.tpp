/* 
 * File:   Pathfinding.cpp
 * Author: rafa
 * 
 * Created on January 2, 2018, 8:15 PM
 */

namespace zt {
    template <class NodeType>
    Pathfinding<NodeType>::Pathfinding(const IMesh<NodeType>& mesh) : mesh(mesh){
    }

    template <class NodeType>
    Pathfinding<NodeType>::~Pathfinding() {
    }

    template <class NodeType>
    std::vector<NodeType> Pathfinding<NodeType>::getPath(NodeType originNode, NodeType destination) {
        openList.clear();
        closedList.clear();

        DiscoveredNode<NodeType> origin(originNode, 0, mesh.estimate(originNode, destination));
        openList.push_back(origin);

        bool success = false;

        DiscoveredNode<NodeType> lastNode; // Use to build the path.
        
        while (!openList.empty()) {

            DiscoveredNode<NodeType> cf = popOpenList();

            closedList.insert(cf);
            lastNode = cf;

            if (cf == destination) {
                success = true;
                break;
            }

            std::vector<NodeType> adjs = mesh.getAdjacents(cf.node);

            for (NodeType adj : adjs) {
                bool closed = isClosed(adj);

                if (!closed) {
                    float g = cf.g + mesh.cost(cf.node, adj);
                    float h = mesh.estimate(adj, destination);

                    this->addOrUpdateOpenList(adj, cf.node, g, h);
                }
            }

        }

        std::vector<NodeType> path;
        if (success) {

            DiscoveredNode<NodeType>& f = lastNode;

            NodeType nt = f.previousNode;

            path.insert(path.begin(), f.node);

            bool initial = f.initial;

            while (!initial) {
                for (auto it = closedList.begin(); it != closedList.end(); ++it) {
                    if ((*it).node == nt) {
                        initial = (*it).initial;
                        nt = (*it).previousNode;
                        path.insert(path.begin(), (*it).node);
                        break;
                    }
                }
            }
        }
        else {
            throw std::exception();
        }


        return path;
    }

    template <class NodeType>
    DiscoveredNode<NodeType> Pathfinding<NodeType>::popOpenList() {
        // We assume that the open list is not empty.
        
        int index = -1;
        float minF = 0;
        for (int i = 0; i < openList.size(); i++) {
            if (index == -1 || openList[i].f() < minF) {
                minF = openList[i].f();
                index = i;
            }
        }

        DiscoveredNode<NodeType> res = openList[index];
        openList.erase(openList.begin() + index);

        return res;
    }

    template <class NodeType>
    void Pathfinding<NodeType>::addOrUpdateOpenList(const NodeType& node, const NodeType& previous, float g, float h) {
        bool already = false;
        for (DiscoveredNode<NodeType>& fr : openList) {
            if (fr.node == node) {
                already = true;
                if (g < fr.g) {
                    fr.previousNode = previous;
                    fr.g = g;
                }

                break;
            }
        }

        if (!already) {
            openList.push_back(DiscoveredNode<NodeType>(node, previous, g, h));
        }



    }

    template <class NodeType>
    bool Pathfinding<NodeType>::isClosed(const NodeType& node) {
        return closedList.count(DiscoveredNode<NodeType>(node));
    }

}