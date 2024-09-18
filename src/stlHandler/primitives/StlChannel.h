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
 * @brief A channel with the following ordering of vertices:
 *    7------6    height
 *   /|     /|      z length
 *  4------5 |      |  y
 *  | 3----|-2      | /
 *  |/     |/       |/
 *  0------1        0------x width
 * 
 * A channel is hollow and has a set of two traversal faces that are empty
 */

struct StlChannel : public Primitive {

    std::array<double,3> dimension;
    std::array<double,3> normal1;  // points in local positive x direction (dimension[0])
    std::array<double,3> normal2;  // points in local positive y direction (dimension[1])
    unsigned short hollowDir;  // 0, 1, or 2; i.e., 0 -> hollow in dimension[0]

    StlChannel(int id, std::vector<std::shared_ptr<Vertex>> vertices, unsigned short hollowDir);

    void render() override;
};

}   // namespace stl