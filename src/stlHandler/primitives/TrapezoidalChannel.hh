#include "TrapezoidalChannel.h"

namespace stl
{

TrapezoidalChannel::TrapezoidalChannel(int id_, std::vector<std::shared_ptr<Vertex>> vertices_, unsigned short hollowDir_) :
    Primitive(id_, vertices_), hollowDir(hollowDir_)
{
    // check if no. vertices == 8
    if (vertices_.size() != 8) {
        throw std::length_error("Tried to define trapezoidal channel with no. vertices unequal to 8.");
    }

    // check if hollow direction is correct.
    if (hollowDir != 0 && hollowDir != 1 && hollowDir != 2) {
        std::string  errorMessage = "Tried to define trapezoidal channel with invalid hollow direction: " 
                                    + std::to_string(hollowDir) 
                                    + ". Valid options are 0, 1, or 2.";
        throw std::invalid_argument(errorMessage);
    }

    // set channel dimension
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

void TrapezoidalChannel::render() 
{
    std::array<std::array<int,3>,4> frontBack ={std::array<int,3>{0, 1, 5},
                                                std::array<int,3>{0, 5, 4},
                                                std::array<int,3>{2, 3, 7},
                                                std::array<int,3>{2, 7, 6}};
    std::array<std::array<int,3>,4> leftRight ={std::array<int,3>{1, 2, 6},
                                                std::array<int,3>{1, 6, 5},
                                                std::array<int,3>{3, 0, 4},
                                                std::array<int,3>{3, 4, 7}};
    std::array<std::array<int,3>,4> topBottom ={std::array<int,3>{0, 2, 1},
                                                std::array<int,3>{0, 3, 2},
                                                std::array<int,3>{4, 5, 6},
                                                std::array<int,3>{4, 6, 7}};
    if (hollowDir != 1) {
        // Define and add faces of the front and the back
        for (auto p : frontBack) {
            std::array<std::shared_ptr<Vertex>,3> v = {vertices[p[0]], vertices[p[1]], vertices[p[2]]};
            Face face(faces.size(), v);
            this->faces.push_back(face);
        } 
    } 
    if (hollowDir != 0) {
        // Define and add faces of the left and the right
        for (auto p : leftRight) {
            std::array<std::shared_ptr<Vertex>,3> v = {vertices[p[0]], vertices[p[1]], vertices[p[2]]};
            Face face(faces.size(), v);
            this->faces.push_back(face);
        } 
    }                                       
    if (hollowDir != 2) {
        // Define and add faces of the top and the bottom
        for (auto p : topBottom) {
            std::array<std::shared_ptr<Vertex>,3> v = {vertices[p[0]], vertices[p[1]], vertices[p[2]]};
            Face face(faces.size(), v);
            this->faces.push_back(face);
        } 
    }
}


}   // namespace stl