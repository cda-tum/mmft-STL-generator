/**
 * @file Stl.h
 */

#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <vector>
#include <unordered_map>

#include "BaseSTL.h"

namespace arch {

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
class NodeSTL;

class NetworkSTL : public BaseSTL {

private:

    const int nodeResolution = 25; //< Hardcoded

    std::shared_ptr<arch::Network> networkPtr;

    std::unordered_map<int, std::shared_ptr<NodeSTL>> stlNodes;

    NodeSTL nodeToSTL(const arch::Node& node);

    NodeSTL groundNodeToSTL(const arch::Node& node);

    Channel channelToSTL(const arch::Channel& channel);

public:

    NetworkSTL(std::shared_ptr<arch::Network> network);

};

class NodeSTL {

private:

    const int id;
    const arch::Node networkNode;
    const bool ground;
    double height;
    double radius;
    int topCenterId;
    int bottomCenterId;
    std::vector<arch::RadialPosition> channelOrder;
    std::vector<Coordinate> nodePoints;
    std::map<int, int> p2Vertex;
    /*  For triangle- and pizzaPointIds, the points are stored as
        Top first, bottom first, top second, bottom second */
    std::vector<std::array<int,4>> trianglePointIds;
    std::vector<std::array<int,4>> pizzaPointIds;
    /*  The vertexIds are always stored in the same order
        Bottom left, right, Top right, left */
    std::unordered_map<int, std::array<int, 4>> channelPoints;   // Channel <channelId, <4 pointIds>>

public:

    NodeSTL(const arch::Node& networkNode, const std::unordered_map<int, std::shared_ptr<arch::Channel>>& reach,
            std::vector<std::shared_ptr<Vertex>>& vertices_);

    NodeSTL(const arch::Node& networkGroundNode, std::shared_ptr<arch::Channel> channel);

    void constructCrown();

friend class NetworkSTL;

};

} // namespace arch