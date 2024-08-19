/**
 * @file Core.h
 */

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

namespace stl
{

struct Vertex {

    const int id;
    std::array<double,3> position;

    Vertex(int id, std::array<double,3> position) :
        id(id), position(position) { }

    Vertex(int id, double x, double y, double z) :
        id(id)
        {
            position = {x, y, z};
        }

};

struct Face {

    int id;     // Mutable due to render() function
    std::array<std::shared_ptr<Vertex>,3> vertices;
    std::array<double,3> normal;

    Face(int id, std::array<std::shared_ptr<Vertex>,3> vertices) :
        id(id), vertices(vertices) { }

    std::array<int, 3> getVertexIds() {

        std::array<int, 3> vertexIds = {vertices[0]->id, 
                                        vertices[1]->id,
                                        vertices[2]->id};
        return vertexIds;
    }

};

class Primitive {

protected:

    const int id;
    std::vector<std::shared_ptr<Vertex>> vertices;
    std::vector<Face> faces;

    Primitive(int id) :
        id(id) { }

public:

    Primitive(int id, std::vector<std::shared_ptr<Vertex>> vertices) :
        id(id), vertices(vertices) { }

    int getId() { return id; }

    std::vector<std::shared_ptr<Vertex>>& getVertices() { return vertices; }

    std::vector<int> getVertexIds() {

        std::vector<int> vertexIds;
        for (auto vertex : vertices) {
            vertexIds.push_back(vertex->id);
        }
        return vertexIds;
    }

    std::vector<Face> getFaces() { return faces; }

    virtual void render() {
        throw std::logic_error("Tried to execute undefined render function. 'render()' undefined for primitive.");
    };
    
};

}   // namespace stl