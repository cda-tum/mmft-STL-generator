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
 * @brief A cuboid with the following ordering of vertices:
 *    7------6    height
 *   /|     /|      z length (normal2)
 *  4------5 |      |  y
 *  | 3----|-2      | /
 *  |/     |/       |/
 *  0------1        0------x width (normal1)
 */

struct Cuboid : public Primitive {

    std::array<double,3> dimension;
    std::array<double,3> normal1;  // points in local positive x direction (dimension[0])
    std::array<double,3> normal2;  // points in local positive y direction (dimension[1])

    Cuboid(int id, std::vector<std::shared_ptr<Vertex>> vertices);

    void render() override;
};

}   // namespace stl