#include "Core.h"

namespace stl
{

bool Primitive::isParallel(std::array<double,3> p1, std::array<double,3> p2) {

    double len1 = sqrt(p1[0]*p1[0] + p1[1]*p1[1] + p1[2]*p1[2]);
    double len2 = sqrt(p2[0]*p2[0] + p2[1]*p2[1] + p2[2]*p2[2]);

    if (len1 <= 1e-12 || len2 <= 1e-12) {
        throw std::domain_error("Edge or normal with no length defined.");
    }

    double uvec1[3];
    double uvec2[3];

    uvec1[0] = p1[0]/len1;
    uvec1[1] = p1[1]/len1;
    uvec1[2] = p1[2]/len1;

    uvec2[0] = p2[0]/len2;
    uvec2[1] = p2[1]/len2;
    uvec2[2] = p2[2]/len2;

    if (std::abs(uvec1[0]-uvec2[0]) < 1e-12 && std::abs(uvec1[1]-uvec2[1]) < 1e-12 && std::abs(uvec1[2]-uvec2[2]) < 1e-12) {
        return true;
    } 
    if (std::abs(uvec1[0]+uvec2[0]) < 1e-12 && std::abs(uvec1[1]+uvec2[1]) < 1e-12 && std::abs(uvec1[2]+uvec2[2]) < 1e-12) {
        return true;
    } 

    return false;
}

bool Primitive::isParallel (unsigned long int v1, unsigned long int v2, unsigned long int v3, unsigned long int v4) {

    if (vertices.size() <= v1 || 
        vertices.size() <= v2 ||
        vertices.size() <= v3 ||
        vertices.size() <= v4) {
        throw std::out_of_range("Tried to read non-existant vertex for primitive.");
    }

    std::array<double,3> p1 = (vertices[v2]->position-vertices[v1]->position).toArray();
    std::array<double,3> p2 = (vertices[v4]->position-vertices[v3]->position).toArray();
    return isParallel(p1, p2);
}

std::array<double,3> Primitive::getNormal(unsigned long int v1, unsigned long int v2, unsigned long int v3) {
    if (vertices.size() <= v1 ||
        vertices.size() <= v2 ||
        vertices.size() <= v3) {
        throw std::out_of_range("Tried to read non-existant vertex for primitive.");
    }

    auto Vec1 = vertices[v2]->position - vertices[v1]->position;
    auto Vec2 = vertices[v3]->position - vertices[v1]->position;

    auto normal = Vec1.crossProduct(Vec2);

    return normal.toArray();
}

std::vector<int> Primitive::getVertexIds() {
    std::vector<int> vertexIds;
    for (auto vertex : vertices) {
        vertexIds.push_back(vertex->id);
    }
    return vertexIds;
}

}   // namespace stl