/**
 * @file Stl.h
 */

#pragma once

#include <float.h>
#include <memory>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "primitives/Core.h"
#include "primitives/Channel.h"
#include "primitives/Circle.h"
#include "primitives/Cuboid.h"
#include "primitives/Pizza.h"
#include "primitives/Rectangle.h"
#include "primitives/Trapezoid.h"
#include "primitives/TrapezoidalChannel.h"
#include "primitives/TrapezoidalPrism.h"

namespace stl
{

struct Vertex;
struct Face;
class Primitive;
class Rectangle;
class Trapezoid;
class Pizza;
class Circle;
class Cuboid;
class Channel;
class TrapezoidalPrism;
class TrapezoidalChannel;

class BaseSTL {

protected:

    double resolution = 1e-9;

    std::vector<std::shared_ptr<Vertex>>                vertices;
    std::vector<std::shared_ptr<Face>>                  faces;
    std::vector<std::shared_ptr<Primitive>>             primitives;

public:

    BaseSTL();

    std::tuple<bool, unsigned int> findDuplicate(Coordinate c);

    std::shared_ptr<Vertex> addVertex(std::array<double,3> position);

    std::shared_ptr<Vertex> addVertex(double x, double y, double z);

    std::shared_ptr<Face> addFace(unsigned int v1, unsigned int v2, unsigned int v3);

    Face& addFace(Face& addFace);

    std::shared_ptr<Rectangle> addRectangle(std::array<int,4> c);

    std::shared_ptr<Rectangle> addRectangle(std::array<Coordinate,4> c);

    std::shared_ptr<Trapezoid> addTrapezoid(std::array<Coordinate,4> c);

    std::shared_ptr<Pizza> addPizza(std::array<int,3> c, int radResolution);

    std::shared_ptr<Pizza> addPizza(std::array<Coordinate,3> c, int radResolution);

    std::shared_ptr<Pizza> addPizza(const std::shared_ptr<Pizza>& mirror, double distance);

    std::shared_ptr<Circle> addCircle(Coordinate c, std::array<double,3> normal, double radius, int radResolution);

    std::shared_ptr<Circle> addCircle(const std::shared_ptr<Circle> mirror, double d);

    std::shared_ptr<Cuboid> addCuboid(std::array<Coordinate,8> c);
    
    std::shared_ptr<Channel> addChannel(std::array<int,8> c, unsigned int hollowDir=1);

    std::shared_ptr<Channel> addChannel(std::array<Coordinate,8> c, unsigned int hollowDir=1);

    std::shared_ptr<TrapezoidalPrism> addTrapezoidalPrism(std::array<Coordinate,8> c);

    std::shared_ptr<TrapezoidalChannel> addTrapezoidalChannel(std::array<Coordinate,8> c, unsigned int hollowDir=1);

    /**
     * @brief Loop through all primitives and add the composing faces to the faces vector.
     */
    void render();

    void translate(std::array<double,3> translation);

    void scale(std::array<double,3> expansion, const Coordinate& center);

    void rotate(double rad, std::array<double,3> rotationalAxis, const Coordinate& center);

    void invertFaces();

    std::array<double,3> getMin();

    std::array<double,3> getMax();

    std::tuple<std::array<double,3>, std::array<double,3>> getBoundingBox();

    void writeSTL(std::string file);

};

} // namespace arch