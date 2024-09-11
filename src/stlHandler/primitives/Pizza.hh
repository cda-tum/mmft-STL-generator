#include "Pizza.h"

namespace stl
{

Pizza::Pizza(int id_, std::vector<std::shared_ptr<Vertex>> v_) :
    Primitive(id_, v_), center(v_[0]), p1(v_[1]), p2(v_[2])
{
    double radius = (p1->position - center->position).length();
    if (std::abs(radius - (p2->position - center->position).length()) > 1e-9) 
    {
        throw std::domain_error("Tried to define pizza slice with sides of unequal length.");
    }
    Face temp = Face(0, std::array<std::shared_ptr<Vertex>,3>({center, p1, p2}));
    normal = temp.normal;
    radResolution = temp.getAngle() / (vertices.size() - 3);

    int i = 1;
    for (auto vertice = vertices.begin()+3; vertice!=vertices.end(); ++vertice) {
        (*vertice)->position = p1->position.rotate(center->position, normal, i*radResolution);
        i++;
    }
}

Pizza::Pizza(int id_, std::vector<std::shared_ptr<Vertex>> v_, const Pizza& mirror_, double distance_) :
    Primitive(id_, v_), center(v_[0]), p1(v_[1]), p2(v_[2]), radResolution(mirror_.radResolution), radius(mirror_.radius)
{
    normal = {-mirror_.normal[0], -mirror_.normal[1], -mirror_.normal[2]};

    v_[0]->position = Coordinate(mirror_.center->position.x + distance_*normal[0],
                                mirror_.center->position.y + distance_*normal[1],
                                mirror_.center->position.z + distance_*normal[2]);

    v_[1]->position = Coordinate(mirror_.p2->position.x + distance_*normal[0],
                                mirror_.p2->position.y + distance_*normal[1],
                                mirror_.p2->position.z + distance_*normal[2]);

    v_[2]->position = Coordinate(mirror_.p1->position.x + distance_*normal[0],
                                mirror_.p1->position.y + distance_*normal[1],
                                mirror_.p1->position.z + distance_*normal[2]);

    int i = 1;
    for (auto vertice = vertices.begin()+3; vertice!=vertices.end(); ++vertice) {
        (*vertice)->position = p1->position.rotate(center->position, normal, i*radResolution);
        i++;
    }
}

void Pizza::render() 
{
    // Define and add faces
    for (auto vertice = vertices.begin()+1; vertice!=vertices.end()-1; ++vertice) {
        std::array<std::shared_ptr<Vertex>,3> v = {vertices[0], *vertice, *(vertice+1)};
        Face face(faces.size(), v);
        this->faces.push_back(face);
    }
}

std::vector<Coordinate> Pizza::getCornicione() {
    std::vector<Coordinate> Cornicione;
    for (auto vertice = vertices.begin()+1; vertice!=vertices.end(); ++vertice) {
        Cornicione.push_back(Coordinate((*vertice)->position));
    }
    return Cornicione;
}

}   // namespace stl