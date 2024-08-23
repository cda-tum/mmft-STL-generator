#include "TrapezoidalPrism.h"

namespace stl
{

TrapezoidalPrism::TrapezoidalPrism(int id_, std::vector<std::shared_ptr<Vertex>> vertices_) :
    Primitive(id_, vertices_)
{
    // check if no. vertices == 8
    if (vertices_.size() != 8) {
        throw std::length_error("Tried to define trapezoidal channel with no. vertices unequal to 8.");
    }

    // set prism dimension
    double width = (vertices[1]->position - vertices[0]->position).length();
    double length = (vertices[3]->position - vertices[0]->position).length();
    double height = (vertices[4]->position - vertices[0]->position).length();
    dimension = {width, length, height};

    // set normal values
    auto dir1 = (vertices[1]->position - vertices[0]->position) / width;
    auto dir2 = (vertices[3]->position - vertices[0]->position) / length;
    normal1 = dir1.toArray();
    normal2 = dir2.toArray();
}

void TrapezoidalPrism::render() 
{
    std::array<std::array<int,3>,12> vertexIds =   {std::array<int,3>{0, 1, 5},
                                                    std::array<int,3>{0, 5, 4},
                                                    std::array<int,3>{1, 2, 6},
                                                    std::array<int,3>{1, 6, 5},
                                                    std::array<int,3>{2, 3, 7},
                                                    std::array<int,3>{2, 7, 6},
                                                    std::array<int,3>{3, 0, 4},
                                                    std::array<int,3>{3, 4, 7},
                                                    std::array<int,3>{0, 2, 1},
                                                    std::array<int,3>{0, 3, 2},
                                                    std::array<int,3>{4, 5, 6},
                                                    std::array<int,3>{4, 6, 7}};
    // Define and add faces
    for (auto p : vertexIds) {
        std::array<std::shared_ptr<Vertex>,3> v = {vertices[p[0]], vertices[p[1]], vertices[p[2]]};
        Face face(faces.size(), v);
        this->faces.push_back(face);
    } 
}


}   // namespace stl