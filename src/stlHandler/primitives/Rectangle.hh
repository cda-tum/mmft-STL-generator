#include "Rectangle.h"

namespace stl
{

Rectangle::Rectangle(int id_, std::vector<std::shared_ptr<Vertex>> vertices_) :
    Primitive(id_, vertices_)
{
    // check if no. vertices == 4
    if (vertices_.size() != 4) {
        throw std::length_error("Tried to define rectangle with no. vertices unequal to 4.");
    }

    // check if the vertices constitute a rectangle (i.e. borders are parallel)
    if (!this->isParallel(0, 1, 3, 2) || !this->isParallel(0, 3, 1, 2)) {
        throw std::domain_error("Tried to define rectangle with non-parallel edges.");
    }

    // check if all vertices lie on a single plane 
    auto n1 = this->getNormal(0, 1, 2);
    auto n2 = this->getNormal(0, 2, 3);
    if (!this->isParallel(n1, n2)) {
        std::cout << "The normals of this rectangle are: " << n1[0] << ", " << n1[1] << ", " << n1[2] << std::endl;
        std::cout << "The normals of this rectangle are: " << n2[0] << ", " << n2[1] << ", " << n2[2] << std::endl;
        throw std::domain_error("Tried to define planar rectangle with vertex out-of-plane.");
    }

    // set normal value
    normal = n1;
}

void Rectangle::render() 
{
    std::array<std::array<int,3>,12> vertexIds =   {std::array<int,3>{0, 1, 2},
                                                    std::array<int,3>{0, 2, 3}};
    // Define and add faces
    for (auto p : vertexIds) {
        std::array<std::shared_ptr<Vertex>,3> v = {vertices[p[0]], vertices[p[1]], vertices[p[2]]};
        Face face(faces.size(), v);
        this->faces.push_back(face);
    } 
}

}   // namespace stl