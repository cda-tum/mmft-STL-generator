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

private:

    std::shared_ptr<arch::Network> networkPtr;

    std::vector<std::shared_ptr<NodeSTL>> stlNodes;

    NodeSTL nodeToSTL(const arch::Node& node);

    NodeSTL groundNodeToSTL(const arch::Node& node);

    Channel channelToSTL(const arch::Channel& channel);

public:

    NetworkSTL(std::shared_ptr<arch::Network> network);

};

class NodeSTL {

private:

    const int id;
    const int resolution = 100;
    const arch::Node networkNode;
    int topCenterId;
    int bottomCenterId;
    std::vector<arch::RadialPosition> channelOrder;
    /*  The vertexIds are always stored in the same order
        Node A: 0, 1, 5, 4
        Node B: 2, 3, 7, 6  */
    std::unordered_map<int, std::array<int, 4>> channelVertices;   // Channel <channelId, <4 vertexIds>>
    double height;
    double radius;
    std::vector<int> crownVertexIds; // These vertices form the top ring of the STL node.
    std::vector<int> bodyVertexIds;
    std::vector<Face> nodeFaces;

public:

    NodeSTL(const arch::Node& networkNode, const std::unordered_map<int, std::shared_ptr<arch::Channel>>& reach,
            std::vector<std::shared_ptr<Vertex>>& vertices_);

    void extractCrown(std::vector<std::shared_ptr<Vertex>>& vertices_);

    void render();

    std::vector<Face> getFaces() { return nodeFaces; }

    std::vector<Vertex> getVertices() { return bodyVertices; }

    std::array<int, 4> getChannelVertices(int channelId) { return channelVertices.at(channelId); }

};

} // namespace arch