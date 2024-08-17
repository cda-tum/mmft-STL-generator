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
struct Rectangle;
struct Trapezoid;
struct Cuboid;
struct Channel;
struct TrapezoidalPrism;
struct TrapezoidalChannel;

class STL {

protected:
    int id;
    std::shared_ptr<std::vector<Vertex>>                vertices;
    std::shared_ptr<std::vector<Face>>                  faces;
    std::shared_ptr<std::vector<Rectangle>>             rectangles;
    std::shared_ptr<std::vector<Trapezoid>>             trapezoids;
    std::shared_ptr<std::vector<Cuboid>>                cuboids;
    std::shared_ptr<std::vector<Channel>>               channels;
    std::shared_ptr<std::vector<TrapezoidalPrism>>      trPrisms;
    std::shared_ptr<std::vector<TrapezoidalChannel>>    trChannels;

public:
    STL();

    STL(arch::Network network);

    int getId() const { return id; };

    std::shared_ptr<Vertex> addVertex(double x, double y, double z);

    std::shared_ptr<Face> addFace();

    std::shared_ptr<Rectangle> addRectangle();

    std::shared_ptr<Cuboid> addCuboid();

    void render();

    void translate(double x, double y, double z);

    void scale(double x, double y, double z, double center[3]);

    void rotate(double x, double y, double z, double center[3]);

    void invertFaces();

    void writeSTL(std::string file);

};

} // namespace arch