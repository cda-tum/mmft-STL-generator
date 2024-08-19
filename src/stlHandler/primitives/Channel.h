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

struct Channel : public Primitive {

    std::array<double,3> dimension;
    std::array<double,3> normal1;  // points in local positive x direction (dimension[0])
    std::array<double,3> normal2;  // points in local positive y direction (dimension[1])
    unsigned short hollowDir;  // 0, 1, or 2; i.e., 0 -> hollow in dimension[0]

    Channel() {
        /** TODO:
         * 
         */
    }

    void render() override {
    /** TODO:
     * make sure that length of vertices == 8.
     */
    }
};

}   // namespace stl