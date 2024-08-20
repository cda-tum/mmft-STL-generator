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
 * @brief A trapezoid with a clockwise ordering of vertices, i.e.,
 *   3--2
 *  /   |
 * 0----1
 */
struct Trapezoid : public Primitive{

    std::array<double,3> normal;

    Trapezoid(int id, std::vector<std::shared_ptr<Vertex>> vertices);

    void render() override;

};

}   // namespace stl