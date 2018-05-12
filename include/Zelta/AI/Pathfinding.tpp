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
        openList.insert(origin);

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
        
        auto best = (openList.begin());
        float minF = (*best).f();
        
        for (auto it = openList.begin(); it != openList.end(); ++it) {
            if ((*it).f() < minF) {
                best = it;
                minF = (*it).f();
            }
        }
        
        DiscoveredNode<NodeType> res = *best;
        openList.erase(best);
        
        return res;

    }

    template <class NodeType>
    void Pathfinding<NodeType>::addOrUpdateOpenList(const NodeType& node, const NodeType& previous, float g, float h) {
        
        auto it = openList.find(DiscoveredNode<NodeType>(node));
        
        // Not found, add the node to the list
        if (it == openList.end()) {
            openList.insert(DiscoveredNode<NodeType>(node, previous, g, h));
        }
        else {
            // Found. Update if better.
            // Since we cannot update a set we remove and add.
            if (g < (*it).g) {
                DiscoveredNode<NodeType> updated = (*it);
                updated.previousNode = previous;
                updated.g = g;
                
                openList.erase(it);
                openList.insert(updated);
            }
        }


    }

    template <class NodeType>
    bool Pathfinding<NodeType>::isClosed(const NodeType& node) {
        return closedList.count(DiscoveredNode<NodeType>(node));
    }

}