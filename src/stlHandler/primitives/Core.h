/**
 * @file Core.h
 */

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>



namespace stl
{

struct Coordinate {
    
    double x;
    double y;
    double z;

    Coordinate(std::array<double,3> position) : 
        x(position[0]), y(position[1]), z(position[2]) { }
    
    Coordinate(double x, double y, double z) :
        x(x), y(y), z(z) { }

    Coordinate operator+(const Coordinate& t) const {
        return Coordinate(this->x + t.x, this->y + t.y, this->z + t.z);
    }

    Coordinate operator-(const Coordinate& t) const {
        return Coordinate(this->x - t.x, this->y - t.y, this->z - t.z);
    }

    Coordinate operator*(const double& t) const {
        return Coordinate(this->x * t, this->y * t, this->z * t);
    }

    Coordinate operator/(const double& t) const {
        return Coordinate(this->x / t, this->y / t, this->z / t);
    }

    Coordinate crossProduct(const Coordinate& t) const {
        return Coordinate(  (this->y - t.y) * (this->z - t.z) - (this->z - t.z) * (this->y - t.y),
                            (this->z - t.z) * (this->x - t.x) - (this->x - t.x) * (this->z - t.z),
                            (this->x - t.x) * (this->y - t.y) - (this->y - t.y) * (this->x - t.x));
    }

    std::array<double,3> toArray() {
        return std::array<double,3>({x, y, z});
    }

    double length() {
        return sqrt(x*x + y*y + z*z);
    }
};

struct Vertex {

    const int id;
    Coordinate position;

    Vertex(int id, std::array<double,3> position) :
        id(id), position(position) { }

    Vertex(int id, double x, double y, double z) :
        id(id), position(x, y, z) { }

};

struct Face {

    unsigned int id;     // Mutable due to render() function
    std::array<std::shared_ptr<Vertex>,3> vertices;
    std::array<double,3> normal;

    Face(unsigned int id, std::array<std::shared_ptr<Vertex>,3> vertices) :
        id(id), vertices(vertices) { }

    std::array<unsigned int, 3> getVertexIds() {

        std::array<unsigned int, 3> vertexIds = {vertices[0]->id, 
                                                vertices[1]->id,
                                                vertices[2]->id};
        return vertexIds;
    }

};

class Primitive {

protected:

    const unsigned int id;
    std::vector<std::shared_ptr<Vertex>> vertices;
    std::vector<Face> faces;

    Primitive(unsigned int id) :
        id(id) { }

    bool isParallel(std::array<double,3> p1, std::array<double,3> p2);

    bool isParallel(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4);

    std::array<double,3> getNormal(unsigned int v1, unsigned int v2, unsigned int v3);

public:

    Primitive(int id, std::vector<std::shared_ptr<Vertex>> vertices) :
        id(id), vertices(vertices) { }

    int getId() { return id; }

    std::vector<std::shared_ptr<Vertex>>& getVertices() { return vertices; }

    std::vector<int> getVertexIds();

    std::vector<Face> getFaces() { return faces; }

    virtual void render() {
        throw std::logic_error("Tried to execute undefined render function. 'render()' undefined for primitive.");
    };
    
};

}   // namespace stl