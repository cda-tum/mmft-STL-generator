/**
 * @file Stl.h
 */

#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "BaseSTL.h"
#include "../architecture/Node.h"
#include "../architecture/Channel.h"
#include "../architecture/Network.h"

namespace arch {

class Network;

class Node;

struct RadialPosition {
    int channelId;
    double radialAngle;
    std::shared_ptr<Channel> channelPtr;
};

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

class NetworkSTL : public BaseSTL {

protected:

    std::shared_ptr<arch::Network> networkPtr;

public:
    NetworkSTL(std::shared_ptr<arch::Network> network);

    void nodeToSTL(int nodeId);

    void nodeToSTL(const arch::Node& node);

    void groundNodeToSTL(const arch::Node& node);

    void channelToSTL(const arch::Channel& channel);
};

class NodeSTL {

private:

    const int id;
    const arch::Node networkNode;
    std::vector<arch::RadialPosition> channelOrder;
    double height;
    double radius;
    std::vector<std::shared_ptr<Vertex>> crownVertices; // These vertices form the top ring of the STL node.
    std::vector<Vertex> bodyVertices;
    std::vector<Face> nodeFaces;

public:

    NodeSTL(const arch::Node& networkNode, const std::unordered_map<int, std::shared_ptr<arch::Channel>>& reach);

    void extractCrown();

    void extrapolateVertices();

    void render();

    std::vector<Face> getFaces() { return nodeFaces; }

    std::vector<Vertex> getVertices() { return bodyVertices; }

};

} // namespace arch