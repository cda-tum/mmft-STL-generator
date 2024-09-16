#include "NetworkSTL.h"

namespace stl
{

NetworkSTL::NetworkSTL(std::shared_ptr<arch::Network> network) :
    networkPtr(network)
{
    for (auto node : network->getNodes()) {
        // If the node is a ground node, it needs a different treatment.
        if (node->getGround()) {
            stlNodes.try_emplace(node->getId(), std::make_shared<NodeSTL>(groundNodeToSTL(*node)));
        } else {
            stlNodes.try_emplace(node->getId(), std::make_shared<NodeSTL>(nodeToSTL(*node)));
        }
    }

    for (auto channel: network->getChannels()) {
        channelToSTL(*channel);
    }

    for (auto primitive : this->primitives) {
        primitive->render();
    }

}

NodeSTL NetworkSTL::nodeToSTL(const arch::Node& node) 
{
    // A node has a set of channels attached to it (reach)
    std::unordered_map<int, std::shared_ptr<arch::Channel>> reach = networkPtr->getReach(node.getId());

    NodeSTL stlNode(node, reach, vertices);

    // Sections attached to channel are top-down triangle faces. The remaining "free" sections are pizza-pieces
    stlNode.constructCrown();

    // Generate all vertices for this node
    int i = 0;
    for (auto& p : stlNode.nodePoints) {
        stlNode.p2Vertex.try_emplace(i, int(vertices.size()));
        vertices.push_back(std::make_shared<Vertex>(vertices.size(), p.toArray()));
        i++;
    }

    // Generate all primitves for the node's "pizza"-sections
    for (auto pizzaPoints : stlNode.pizzaPointIds) {
        // Add the remaining vertices on the cornicione
        auto topPizza = addPizza(std::array<int,3>({stlNode.topCenterId, pizzaPoints[0], pizzaPoints[1]}), nodeResolution);
        auto bottomPizza = addPizza(std::array<int,3>({stlNode.bottomCenterId, pizzaPoints[3], pizzaPoints[2]}), nodeResolution);
        // Add the rectangle primitives for the node side
        for (int j=0; j < nodeResolution; j++) {
            int topStart = vertices.size() -2*nodeResolution +3;
            int bottomStart = vertices.size() -1;
            addRectangle({bottomStart-j, bottomStart-j-1, topStart+j+1, topStart+j});
        }
    }

    // Generate all primitives for the node's "triangles"
    for (auto trianglePoints : stlNode.trianglePointIds) {
        std::cout << "Adding faces" << std::endl;
        addFace(stlNode.topCenterId, stlNode.p2Vertex[trianglePoints[0]], stlNode.p2Vertex[trianglePoints[1]]);
        addFace(stlNode.bottomCenterId, stlNode.p2Vertex[trianglePoints[3]], stlNode.p2Vertex[trianglePoints[2]]);
    }

    return stlNode;
}

NodeSTL NetworkSTL::groundNodeToSTL(const arch::Node& node)
{
    // A ground node has only one channel attached to it (reach)
    std::unordered_map<int, std::shared_ptr<arch::Channel>> reach = networkPtr->getReach(node.getId());
    if (reach.size() > 1) {
        throw std::domain_error("Tried to treat regular node as ground node.");
    }
    std::shared_ptr<arch::Channel> channel;
    for (auto& [key, channel_] : reach) {
        channel = channel_;
    }

    NodeSTL stlNode(node, channel);

    // Generate all vertices for this node
    int i = 0;
    for (auto& p : stlNode.nodePoints) {
        stlNode.p2Vertex.try_emplace(i, int(vertices.size()));
        vertices.push_back(std::make_shared<Vertex>(vertices.size(), p.toArray()));
        i++;
    }

    // Generate the rectangular face primitive of the groundNode
    addRectangle({stlNode.p2Vertex[3], stlNode.p2Vertex[1], stlNode.p2Vertex[0], stlNode.p2Vertex[2]});

    return stlNode;
}

Channel NetworkSTL::channelToSTL(const arch::Channel& channel)
{
    std::array<int, 8> channelVertexIds;
    std::shared_ptr<NodeSTL> stlNodeA = stlNodes.at(channel.getNodeA()->getId());
    std::shared_ptr<NodeSTL> stlNodeB = stlNodes.at(channel.getNodeB()->getId());
    std::array<int, 4> pointIdsA = stlNodes.at(channel.getNodeA()->getId())->channelPoints.at(channel.getId());
    std::array<int, 4> pointIdsB = stlNodes.at(channel.getNodeB()->getId())->channelPoints.at(channel.getId());

    channelVertexIds[0] = stlNodeA->p2Vertex.at(pointIdsA[0]);
    channelVertexIds[1] = stlNodeA->p2Vertex.at(pointIdsA[1]);
    channelVertexIds[2] = stlNodeB->p2Vertex.at(pointIdsB[0]);
    channelVertexIds[3] = stlNodeB->p2Vertex.at(pointIdsB[1]);
    channelVertexIds[4] = stlNodeA->p2Vertex.at(pointIdsA[3]);
    channelVertexIds[5] = stlNodeA->p2Vertex.at(pointIdsA[2]);
    channelVertexIds[6] = stlNodeB->p2Vertex.at(pointIdsB[3]);
    channelVertexIds[7] = stlNodeB->p2Vertex.at(pointIdsB[2]);

    auto newChannel = addChannel(channelVertexIds, 1);

    return *newChannel;
}

/**
 * ======================================== NodeSTL ==============================================
 */

NodeSTL::NodeSTL(const arch::Node& networkNode_, const std::unordered_map<int, std::shared_ptr<arch::Channel>>& reach_, 
    std::vector<std::shared_ptr<Vertex>>& vertices_) :
    id(networkNode_.getId()), networkNode(networkNode_), ground(false)
{   
    // Loop through reach and set this node's height and radius.
    height = 0.0;
    radius = 0.0;
    for (auto& [key, channel] : reach_) {
        if (channel->getHeight() > height) { height = channel->getHeight(); }
        if (channel->getWidth() > 2*radius) { radius = 0.5*channel->getWidth(); }
    }

    // Define the two vertices that form the center point on the top and bottom surface of this node
    int vertexId = vertices_.size();
    topCenterId = vertexId;
    bottomCenterId = vertexId+1;
    vertices_.push_back(std::make_shared<Vertex>((unsigned int) vertices_.size(), Coordinate(networkNode.getPosition()) + Coordinate(0.0, 0.0, 0.5*height)));
    vertices_.push_back(std::make_shared<Vertex>((unsigned int) vertices_.size()+1, Coordinate(networkNode.getPosition()) + Coordinate(0.0, 0.0, -0.5*height)));


    // Loop through reach and set the radial angles at which the channels are connected to this node.
    for (auto& [key, channel] : reach_) {
        std::shared_ptr<arch::Node> nodeA = channel->getNodeA();
        std::shared_ptr<arch::Node> nodeB = channel->getNodeB();
        double dx = ( id == nodeA->getId() ) ? nodeB->getPosition()[0]-nodeA->getPosition()[0] : nodeA->getPosition()[0]-nodeB->getPosition()[0];
        double dy = ( id == nodeA->getId() ) ? nodeB->getPosition()[1]-nodeA->getPosition()[1] : nodeA->getPosition()[1]-nodeB->getPosition()[1];
        if (std::abs(nodeA->getPosition()[2] - nodeB->getPosition()[2]) > 1e-9) {
            throw std::domain_error("Tried to define planar network with nodes out of plane.");
        }
        double angle = std::fmod(atan2(dy,dx)+2*M_PI,2*M_PI);
        arch::RadialPosition newPosition ({key, angle, channel});
        channelOrder.push_back(newPosition);
    }

    // Loop through channelOrder and sort by radial position 0 -> 2*pi
    std::sort(channelOrder.begin(), channelOrder.end(), [](auto& a, auto& b) {
        return a.radialAngle < b.radialAngle;   // ascending order
    });
}

NodeSTL::NodeSTL(const arch::Node& networkGroundNode_, std::shared_ptr<arch::Channel> channel_) :
    id(networkGroundNode_.getId()), networkNode(networkGroundNode_), ground(true)
{   
    // Loop through reach and set this node's height and radius.
    height = channel_->getHeight();
    radius = channel_->getWidth();

    // Set the radil angle at which the channel is connected to this node
    std::shared_ptr<arch::Node> nodeA = channel_->getNodeA();
    std::shared_ptr<arch::Node> nodeB = channel_->getNodeB();
    double dx = ( id == nodeA->getId() ) ? nodeB->getPosition()[0]-nodeA->getPosition()[0] : nodeA->getPosition()[0]-nodeB->getPosition()[0];
    double dy = ( id == nodeA->getId() ) ? nodeB->getPosition()[1]-nodeA->getPosition()[1] : nodeA->getPosition()[1]-nodeB->getPosition()[1];
    if (std::abs(nodeA->getPosition()[2] - nodeB->getPosition()[2]) > 1e-9) {
        throw std::domain_error("Tried to define planar network with nodes out of plane.");
    }
    double angle = std::fmod(atan2(dy,dx)+2*M_PI,2*M_PI);
    arch::RadialPosition channelPosition ({channel_->getId(), angle, channel_});

    double pointX = 0.5*radius*std::sin(channelPosition.radialAngle);
    double pointY = -0.5*radius*std::cos(channelPosition.radialAngle);

    Coordinate topRight = Coordinate(pointX, pointY, 0.5*height) + Coordinate(networkNode.getPosition());
    Coordinate bottomRight = Coordinate(pointX, pointY, -0.5*height) + Coordinate(networkNode.getPosition());
    Coordinate topLeft = Coordinate(-pointX, -pointY, 0.5*height) + Coordinate(networkNode.getPosition());
    Coordinate bottomLeft = Coordinate(-pointX, -pointY, -0.5*height) + Coordinate(networkNode.getPosition());

    nodePoints.push_back(topRight);
    nodePoints.push_back(bottomRight);
    nodePoints.push_back(topLeft);
    nodePoints.push_back(bottomLeft);

    if (id == channel_->getNodeA()->getId()) {
        channelPoints.try_emplace(channel_->getId(), std::array<int, 4>({3, 1, 0, 2}));
    }
    else if (id == channel_->getNodeB()->getId()) {
        channelPoints.try_emplace(channel_->getId(), std::array<int, 4>({3, 1, 0, 2}));
    }

}

void NodeSTL::constructCrown()
{

    for (auto channel = channelOrder.begin(); channel != channelOrder.end(); channel++) {

        auto nextChannel = channelOrder.begin();
        if (channel+1 != channelOrder.end()) {
            nextChannel = channel + 1;
        }

        double angle = std::fmod(nextChannel->radialAngle - channel->radialAngle + 2*M_PI, 2*M_PI);

        channelPoints.try_emplace(channel->channelId, std::array<int, 4>());
        channelPoints.try_emplace(nextChannel->channelId, std::array<int, 4>());

        std::cout << "radialAngle = " << channel->radialAngle << std::endl;
        std::cout << "next radialAngle = " << nextChannel->radialAngle << std::endl;
        std::cout << "Angle is " << angle << std::endl;
        std::cout << "radius is " << radius << std::endl;

        double pointX = 0.0;
        double pointY = 0.0;

        if (angle < M_PI) {
            double alpha = 0.5*channel->channelPtr->getWidth()/(std::sin(angle));
            double beta = 0.5*nextChannel->channelPtr->getWidth()/(std::sin(angle));
            pointX = std::cos(nextChannel->radialAngle)*alpha + std::cos(channel->radialAngle)*beta;
            pointY = std::sin(nextChannel->radialAngle)*alpha + std::sin(channel->radialAngle)*beta;
        } else if (angle == M_PI) {
            std::cout << "Getting here" << std::endl;
            std::cout << "channelWidth " << channel->channelPtr->getWidth() << std::endl;
            std::cout << "nextChannelWidth " << nextChannel->channelPtr->getWidth() << std::endl;
            if (std::abs(0.5*channel->channelPtr->getWidth() - radius) < 1e-15 && std::abs(0.5*nextChannel->channelPtr->getWidth() - radius) < 1e-15) {
                pointX = -std::sin(channel->radialAngle)*channel->channelPtr->getWidth()*0.5;
                pointY = std::cos(channel->radialAngle)*channel->channelPtr->getWidth()*0.5;
            }
        }
        
        std::cout << "pointX = " << pointX << std::endl;
        std::cout << "pointY = " << pointY << std::endl;

        std::cout << "Intersection is at " << sqrt(pointX*pointX + pointY*pointY) << std::endl;

        if ( sqrt(pointX*pointX + pointY*pointY) >= radius) {
            std::cout << "Adding single coordinate to crown" << std::endl;
            /* We add a single coordinate to the sequence*/
            int pointId = nodePoints.size();
            Coordinate newPointTop = Coordinate(pointX, pointY, 0.5*height) + Coordinate(networkNode.getPosition());
            Coordinate newPointBottom = Coordinate(pointX, pointY, -0.5*height) + Coordinate(networkNode.getPosition());
            nodePoints.push_back(newPointTop);
            nodePoints.push_back(newPointBottom);
            if (channel != channelOrder.begin() && channelOrder.size() > 2) {
                std::cout << "Doing this" << std::endl;
                trianglePointIds.push_back({pointId-2, pointId, pointId-1, pointId+1});
            }
            /* The single coordinate is referenced to the current and next channel as:
                points 0, 4 and 1, 5 if we are currently at node A
                points 2, 6 and 3, 7 if we are currently at node B */
            channelPoints.at(channel->channelId)[0] = pointId+1;
            channelPoints.at(channel->channelId)[3] = pointId;
            channelPoints.at(nextChannel->channelId)[1] = pointId+1;
            channelPoints.at(nextChannel->channelId)[2] = pointId;

        } else {
            std::cout << "Adding pizza coordinates to crown" << std::endl;
            double angle1 = channel->radialAngle + std::atan2(channel->channelPtr->getWidth(), radius);
            Coordinate p1 = Coordinate(networkNode.getPosition()) + Coordinate(radius*std::cos(angle1), radius*std::sin(angle1), 0.5*height);
            Coordinate p1_m = Coordinate(networkNode.getPosition()) + Coordinate(radius*std::cos(angle1), radius*std::sin(angle1), -0.5*height);

            double angle2 = nextChannel->radialAngle - std::atan2(nextChannel->channelPtr->getWidth(), radius);
            Coordinate p2 = Coordinate(networkNode.getPosition()) + Coordinate(radius*std::cos(angle2), radius*std::sin(angle2), 0.5*height);
            Coordinate p2_m = Coordinate(networkNode.getPosition()) + Coordinate(radius*std::cos(angle2), radius*std::sin(angle2), -0.5*height);

            int pointId = nodePoints.size();
            nodePoints.push_back(p1);
            nodePoints.push_back(p1_m);
            nodePoints.push_back(p2);
            nodePoints.push_back(p2_m);
            pizzaPointIds.push_back({pointId, pointId+2, pointId+1, pointId+3});

            /* The single coordinate is referenced to the current and next channel as:
                points 0, 4 and 1, 5 if we are currently at node A
                points 2, 6 and 3, 7 if we are currently at node B */
            channelPoints.at(channel->channelId)[0] = pointId+1;
            channelPoints.at(channel->channelId)[3] = pointId;
            channelPoints.at(nextChannel->channelId)[1] = pointId+3;
            channelPoints.at(nextChannel->channelId)[2] = pointId+2;

        }
    }
    if (channelOrder.size() > 2) {
        int pointId = nodePoints.size();
        trianglePointIds.push_back({pointId-2, 0, pointId-1, 1});
    }
}

} // namespace stl