/**
 * @file Rectangle.h
 */

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>
#include "Core.h"

namespace stl
{

/** 
 * @brief A rectangle with a clockwise ordering of vertices, i.e.,
 * 3---2
 * |   |
 * 0---1
 */
class Rectangle : public Primitive {

private:

    std::array<double,3> normal;

public:

    Rectangle(int id, std::vector<std::shared_ptr<Vertex>> vertices);

    Rectangle(int id, std::vector<Face> faces);

    std::array<double, 3> getNormal() { return normal; }

    void render() override;

};

}   // namespace stl