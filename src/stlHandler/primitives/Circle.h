/**
 * @file Pizza.h
 */

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>
#include "Core.h"

namespace stl
{

/** 
 * @brief A circle with a clockwise ordering of vertices, i.e.,
 *      <-- 
 *      * *        
 *    *     *
 *   *   c-r-p1
 *    *     * 
 *      * *
 */
class Circle : public Primitive {

private:

    std::shared_ptr<Vertex> center;
    std::array<double,3> normal;
    std::shared_ptr<Vertex> p1;
    double radius;
    int radResolution;  // slices per pi*rad (i.e., 180 deg)

public:

    Circle(int id, std::vector<std::shared_ptr<Vertex>> vertices, std::array<double,3> normal);

    void render() override;

};

}   // namespace stl