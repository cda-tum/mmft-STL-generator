/**
 * @file Stl.h
 */

#pragma once

#include <memory>
#include <vector>

namespace arch {

class Network;

}

namespace stl
{

struct Vertex;
struct Face;
class Primitive;
class Rectangle;
class Trapezoid;
class Cuboid;
class Channel;
class TrapezoidalPrism;
class TrapezoidalChannel;

class BaseSTL {

protected:

    int id;
    std::vector<std::shared_ptr<Vertex>>                vertices;
    std::vector<std::shared_ptr<Face>>                  faces;
    std::vector<std::shared_ptr<Primitive>>             primitives;

public:

    BaseSTL();

    int getId() const { return id; };

    std::shared_ptr<Vertex> addVertex(double x, double y, double z);

    std::shared_ptr<Face> addFace();

    std::shared_ptr<Rectangle> addRectangle();

    std::shared_ptr<Trapezoid> addTrapezoid();

    std::shared_ptr<Cuboid> addCuboid();
    
    std::shared_ptr<Channel> addChannel();

    std::shared_ptr<TrapezoidalPrism> addTrapezoidalPrism();

    std::shared_ptr<TrapezoidalChannel> addTrapezoidalChannel();

    void render();

    void translate(double x, double y, double z);

    void scale(double x, double y, double z, double center[3]);

    void rotate(double x, double y, double z, double center[3]);

    void invertFaces();

    std::array<double,3> getMin();

    std::array<double,3> getMax();

    std::tuple<std::array<double,3>, std::array<double,3>> getBoundingBox();

    void writeSTL(std::string file);

};

} // namespace arch