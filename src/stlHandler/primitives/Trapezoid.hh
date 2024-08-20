#include "Trapezoid.h"

namespace stl
{

Trapezoid::Trapezoid(int id_, std::vector<std::shared_ptr<Vertex>> vertices_) :
    Primitive(id_, vertices_)
{
    // check if no. vertices == 4
    if (vertices_.size() != 4) {
        throw std::length_error("Tried to define trapezoid with no. vertices unequal to 4.");
    }

    // check if all vertices lie on a single plane 
    auto n1 = this->getNormal(0, 1, 2);
    auto n2 = this->getNormal(0, 2, 3);
    if (!this->isParallel(n1, n2)) {
        throw std::domain_error("Tried to define planar rectangle with vertex out-of-plane.");
    }

    // set normal value
    normal = n1;
}

void Trapezoid::render() 
{
    std::array<std::array<int,3>,12> vertexIds =   {std::array<int,3>{0, 1, 2},
                                                    std::array<int,3>{0, 2, 3}};
    // Define and add faces
    for (auto p : vertexIds) {
        std::array<std::shared_ptr<Vertex>,3> vertices = {vertices[p[0]], vertices[p[1]], vertices[p[2]]};
        Face face(faces.size(), vertices);
        this->faces.push_back(face);
    } 
}

}   // namespace stl