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

namespace stl
{

struct RadialPosition {
    int channelId;
    double radialAngle;
    std::shared_ptr<Channel> channelPtr;
};

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

    std::shared_ptr<Network> networkPtr;

    const int radialResolution;

    std::unordered_map<int, std::shared_ptr<NodeSTL>> stlNodes;

    NodeSTL nodeToSTL(const Node& node);

    NodeSTL groundNodeToSTL(const Node& node);

    StlChannel channelToSTL(const Channel& channel);

public:

    NetworkSTL(std::shared_ptr<Network> network, int radialResolution=25);

    std::vector<double> getNodeNormalVector(int nodeId);

    double getChannelWidthAtNode(int nodeId);

};

class NodeSTL {

private:

    const int id;
    const Node networkNode;
    const bool ground;
    std::array<double, 3> groundNormalVector;
    double height;
    double radius;
    int topCenterId;
    int bottomCenterId;
    std::vector<RadialPosition> channelOrder;
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

    NodeSTL(const Node& networkNode, const std::unordered_map<int, std::shared_ptr<Channel>>& reach,
            std::vector<std::shared_ptr<Vertex>>& vertices_);

    NodeSTL(const Node& networkGroundNode, std::shared_ptr<Channel> channel);

    void constructCrown();

    std::vector<double> getGroundNormalVector();

    void setGroundNormalVector(std::array<double,3> normal) { groundNormalVector = normal; }

    double getGroundChannelWidth();

friend class NetworkSTL;

};

} // namespace stl