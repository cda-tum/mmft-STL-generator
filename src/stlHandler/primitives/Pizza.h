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
 * @brief A pizza slice with a clockwise ordering of vertices, i.e.,
 *   p2__
 *   /   *
 *  /     \
 * c------p1
 */
class Pizza : public Primitive {

private:

    std::shared_ptr<Vertex> center;
    std::shared_ptr<Vertex> p1;
    std::shared_ptr<Vertex> p2;
    std::shared_ptr<Vertex> centerOfCurvature;
    double radResolution;  // angle of 1 slice in radial.
    double radius;
    std::array<double,3> normal;

public:

    /**
     * @brief Defines the coordinates of the 'cornicione' (crust of pizza slice) for the given set of vertices
     * where v[0] is the center, v[1] is p1 and v[2] is p2 which are all three pre-defined.
     */
    Pizza(long unsigned int id, std::vector<std::shared_ptr<Vertex>> v);

    Pizza(long unsigned int id, std::vector<std::shared_ptr<Vertex>> v, const Pizza& mirror, double distance);

    void render() override;

    double getResolution() { return radResolution; }

    std::array<double,3>& getNormal() { return normal; }

    std::vector<Coordinate> getCornicione ();
};

}   // namespace stl