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

struct TrapezoidalPrism : public Primitive {

    std::array<double,3> dimension;
    std::array<double,3> normal1;  // points in local positive x direction (dimension[0])
    std::array<double,3> normal2;  // points in local positive y direction (dimension[1])

    TrapezoidalPrism() {
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