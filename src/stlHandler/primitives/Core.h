    /**
 * @file Core.h
 */

#pragma once

#include <cmath>
#include <memory>
#include <stdexcept>
#include <vector>

namespace stl
{
class BaseSTL;

struct Coordinate {
    
    double x;
    double y;
    double z;

    Coordinate() { }

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
        return Coordinate(  (this->y * t.z - this->z * t.y),
                            (this->z * t.x - this->x * t.z),
                            (this->x * t.y - this->y * t.x));
    }

    double dotProduct(const Coordinate& t) const {
        return ((this->x * t.x) + (this->y * t.y) + (this->z * t.z));
    }

    Coordinate translate(std::array<double,3> translation) const {
        double x_ = this->x + translation[0];
        double y_ = this->y + translation[1];
        double z_ = this->z + translation[2];
        return Coordinate(x_, y_, z_);
    }

    Coordinate scale(const Coordinate& center, std::array<double,3> expansion) const {
        double x_ = center.x + (this->x - center.x) * expansion[0];
        double y_ = center.y + (this->y - center.y) * expansion[1];
        double z_ = center.z + (this->z - center.z) * expansion[2];
        return Coordinate(x_, y_, z_);
    }

    Coordinate rotate(const Coordinate& center, std::array<double,3> axis, double rad) const {
        double cost = std::cos(rad);
        double cost1 = 1.0-std::cos(rad);
        double sint = std::sin(rad);
        double length = Coordinate(axis).length();
        Coordinate u = Coordinate(axis[0]/length, axis[1]/length, axis[2]/length);
        Coordinate v = this->operator-(center);
        double x_ = v.x*(u.x*u.x*cost1 + cost) + v.y*(u.x*u.y*cost1 - u.z*sint) + v.z*(u.x*u.z*cost1 + u.y*sint);
        double y_ = v.x*(u.x*u.y*cost1 + u.z*sint) + v.y*(u.y*u.y*cost1 + cost) + v.z*(u.y*u.z*cost1 - u.x*sint);
        double z_ = v.x*(u.x*u.z*cost1 - u.y*sint) + v.y*(u.y*u.z*cost1 + u.x*sint) + v.z*(u.z*u.z*cost1 + cost);
        return Coordinate(x_, y_, z_);
    }

    std::array<double,3> toArray() {
        return std::array<double,3>({x, y, z});
    }

    double length() {
        return sqrt(x*x + y*y + z*z);
    }

    void print() {
        std::cout << "("<<x<<", "<<y<<", "<<z<<")\n";
    }
};

struct Vertex {

    const unsigned int id;
    Coordinate position;

    Vertex(unsigned int id) :
        id (id) { }

    Vertex(unsigned int id, std::array<double,3> position) :
        id(id), position(position) { }
    
    Vertex(unsigned int id, Coordinate c) :
        id(id), position(c) { }

    Vertex(unsigned int id, double x, double y, double z) :
        id(id), position(x, y, z) { }

    void print()
    {
        std::cout << "Vertex id: " << id << "\t";
        position.print();
    }

};

struct Face {

    unsigned int id;     // Mutable due to render() function
    std::array<std::shared_ptr<Vertex>,3> vertices;
    std::array<double,3> normal;

    Face(unsigned int id, std::array<std::shared_ptr<Vertex>,3> vertices) :
        id(id), vertices(vertices) 
    { 
        auto Vec1 = vertices[1]->position - vertices[0]->position;
        auto Vec2 = vertices[2]->position - vertices[0]->position;
        auto n = Vec1.crossProduct(Vec2);

        normal = n.toArray();
    }

    std::array<unsigned int, 3> getVertexIds() {
        std::array<unsigned int, 3> vertexIds ={vertices[0]->id, 
                                                vertices[1]->id,
                                                vertices[2]->id};
        return vertexIds;
    }

    /**
     * @brief returns the angle at vertex[0]
     */
    double getAngle() {
        auto Vec1 = vertices[1]->position - vertices[0]->position;
        auto Vec2 = vertices[2]->position - vertices[0]->position;
        return std::acos(Vec1.dotProduct(Vec2)/(Vec1.length()*Vec2.length()));
    }

    void invert() {
        std::swap(vertices[1], vertices[2]);
        normal[0] = -normal[0];
        normal[1] = -normal[1];
        normal[2] = -normal[2];
    }

    std::string writeFace() const {
        std::string faceString;

        faceString =    "facet normal " + std::to_string(normal[0]) + " " 
                        + std::to_string(normal[1]) + " " 
                        + std::to_string(normal[2]) + "\n"
                        + "\touter loop\n"
                        + "\t\tvertex " + std::to_string(vertices[0]->position.x) + " "
                        + std::to_string(vertices[0]->position.y) + " "
                        + std::to_string(vertices[0]->position.z) + "\n"
                        + "\t\tvertex " + std::to_string(vertices[1]->position.x) + " "
                        + std::to_string(vertices[1]->position.y) + " "
                        + std::to_string(vertices[1]->position.z) + "\n"
                        + "\t\tvertex " + std::to_string(vertices[2]->position.x) + " "
                        + std::to_string(vertices[2]->position.y) + " "
                        + std::to_string(vertices[2]->position.z) + "\n"
                        + "\tendloop\n"
                        + "endfacet\n";

        return faceString;
    }

};

class Primitive {

protected:

    const long unsigned int id;
    std::vector<std::shared_ptr<Vertex>> vertices;
    std::vector<Face> faces;

    Primitive(long unsigned int id) :
        id(id) { }

    bool isParallel(std::array<double,3> p1, std::array<double,3> p2);

    bool isParallel(long unsigned int v1, long unsigned int v2, long unsigned int v3, long unsigned int v4);

    std::array<double,3> getNormal(long unsigned int v1, long unsigned int v2, long unsigned int v3);

public:

    Primitive(int id, std::vector<std::shared_ptr<Vertex>> vertices) :
        id(id), vertices(vertices) 
    { }

    int getId() { return id; }

    std::vector<std::shared_ptr<Vertex>>& getVertices() { return vertices; }

    std::vector<int> getVertexIds();

    std::vector<Face> getFaces() { return faces; }

    virtual void render() {
        throw std::logic_error("Tried to execute undefined render function. 'render()' undefined for primitive.");
    };

friend BaseSTL;
    
};

}   // namespace stl
