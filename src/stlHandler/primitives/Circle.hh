#include "Circle.h"

namespace stl
{

Circle::Circle(int id_, std::vector<std::shared_ptr<Vertex>> v_, std::array<double,3> normal_) :
    Primitive(id_, v_), center(v_[0]), normal(normal_), p1(v_[1])
{
    double radius = (p1->position - center->position).length();

    radResolution = 6.28318530718 / (vertices.size() - 1);

    int i = 1;

    for (auto vertice = vertices.begin()+2; vertice!=vertices.end(); ++vertice) {
        (*vertice)->position = p1->position.rotate(center->position, normal, i*radResolution);
        i++;
    }

}

void Circle::render() 
{
    // Define and add faces
    for (auto vertice = vertices.begin()+1; vertice!=vertices.end()-1; ++vertice) {
        std::array<std::shared_ptr<Vertex>,3> v = {vertices[0], *vertice, *(vertice+1)};
        Face face(faces.size(), v);
        this->faces.push_back(face);
    }
    // Define and add last face and close the circle
    std::array<std::shared_ptr<Vertex>,3> v = {vertices[0], *vertices.end(), vertices[1]};
    Face face(faces.size(), v);
    this->faces.push_back(face);
}

}   // namespace stl