/* 
 * File:   Mesh.h
 * Author: Rafa
 *
 * Created on 17 de marzo de 2015, 13:49
 */

#ifndef ZELTALIB_MESH_H
#define	ZELTALIB_MESH_H

#include <vector>

#include <Zelta/Mesh/Node.hpp>

/**
 * Representa un conjunto de nodos. La clase contiene un vector de punteros.
 * La propia clase se encargará de eliminarlos.
 */
namespace zt{
    class Mesh {
    private:
        std::vector<Node*> nodes;
        bool deleteNodesInDestructor;
    public:
        Mesh();
        virtual ~Mesh();

        void addNode(Node * node);
        unsigned int countNodes();

        Node * &operator[](int index);
        Node * closestNodeTo(float x, float y);
        Node * getNodeByName(const std::wstring & name);
        
        void move(float dX, float dY);

    };
    
    /*
    * Compatibilidad con el for de rango.
    */
   Node ** begin(Mesh & mesh);
   Node ** end(Mesh & mesh);

}

#endif	/* MESH_H */

