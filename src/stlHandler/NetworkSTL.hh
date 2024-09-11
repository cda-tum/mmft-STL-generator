#include "NetworkSTL.h"

namespace stl
{

NetworkSTL::NetworkSTL(std::shared_ptr<arch::Network> network) :
    networkPtr(network)
{
    /** TODO:
     * 
     * Define the process that loops through all nodes and converts them
     * into STL format. If node is ground node -> groundNodeToSTL(), otherwise nodeToSTL()
     * Then convert all channels into STL format.
     */

    

    for (auto node : network->getNodes()) {
        // If the node is a ground node, it needs a different treatment.
        if (node.getGround()) {
            stlNodes.push_back(std::make_shared<NodeSTL>(groundNodeToSTL(node)));
        } else {
            std::shared_ptr<NodeSTL> newNode = std::make_shared<NodeSTL>(nodeToSTL(node));
            stlNodes.push_back(newNode);
        }
    }

    for (auto channel: network->getChannels()) {
        channelToSTL(channel);
    }

}

NodeSTL NetworkSTL::nodeToSTL(const arch::Node& node) 
{
    // A node has a set of channels attached to it (reach)
    std::unordered_map<int, std::shared_ptr<arch::Channel>> reach = networkPtr->getReach(node.getId());

    NodeSTL stlNode(node, reach);

    // Sections attached to channel are top-down triangle faces. The remaining "free" sections are pizza-pieces
    stlNode.extractCrown(this->vertices);

    /** TODO: Define the pizza primitives and the connecting rectangle primitives from the stlNode's pizza points
     * The rendering of the remaining triangle-faces connected to the channels, needs to be placed somewhere
     */

    return stlNode;
}

NodeSTL NetworkSTL::groundNodeToSTL(const arch::Node& node)
{
    /** TODO:
     * 
     */
}

Channel NetworkSTL::channelToSTL(const arch::Channel& channel)
{
    std::vector<std::shared_ptr<Vertex>> channelVertices;
    std::array<int, 4> vertexIdsA = stlNodes.at(channel.getNodeA()->getId())->getChannelVertices(channel.getId());
    std::array<int, 4> vertexIdsB = stlNodes.at(channel.getNodeB()->getId())->getChannelVertices(channel.getId());

    channelVertices.push_back(vertices.at(vertexIdsA[0]));
    channelVertices.push_back(vertices.at(vertexIdsA[1]));
    channelVertices.push_back(vertices.at(vertexIdsB[0]));
    channelVertices.push_back(vertices.at(vertexIdsB[1]));
    channelVertices.push_back(vertices.at(vertexIdsA[3]));
    channelVertices.push_back(vertices.at(vertexIdsA[2]));
    channelVertices.push_back(vertices.at(vertexIdsB[3]));
    channelVertices.push_back(vertices.at(vertexIdsB[2]));

    std::shared_ptr<Channel> newChannel = std::make_shared<Channel>(primitives.size(), channelVertices, 1);
    std::shared_ptr<Primitive> newPrimitive = newChannel;
    primitives.push_back(newPrimitive);
    return *newChannel;
}

/**
 * ======================================== NodeSTL ==============================================
 */

NodeSTL::NodeSTL(const arch::Node& networkNode_, const std::unordered_map<int, std::shared_ptr<arch::Channel>>& reach_, 
    std::vector<std::shared_ptr<Vertex>>& vertices_) :
    id(networkNode_.getId()), networkNode(networkNode)
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
    vertices_.push_back(std::make_shared<Vertex>(vertices_.size(), Coordinate(networkNode.getPosition()) + Coordinate(0.0, 0.0, 0.5*height)));
    vertices_.push_back(std::make_shared<Vertex>(vertices_.size()+1, Coordinate(networkNode.getPosition()) + Coordinate(0.0, 0.0, -0.5*height)));


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
    std::sort(channelOrder.begin(), channelOrder.end(), [](auto a&, auto& b) {
        return a.radialAngle < b.radialAngle;   // ascending order
    });
}

void NodeSTL::extractCrown(std::vector<std::shared_ptr<Vertex>>& vertices_)
{

    for (auto channel = channelOrder.begin(); channel != channelOrder.end(); ++channel) {

        auto nextChannel = channelOrder.begin();
        if (channel != channelOrder.end()) {
            auto nextChannel = channel + 1;
        }
        double angle = std::fmod(nextChannel->radialAngle - channel->radialAngle, 2*M_PI);

        channelVertices.try_emplace(channel->channelId, std::array<int, 4>());
        channelVertices.try_emplace(nextChannel->channelId, std::array<int, 4>());
        
        double pointX = 0.5*channel->channelPtr->getWidth()*std::sin(channel->radialAngle) +
                        0.5*nextChannel->channelPtr->getWidth()*std::sin(nextChannel->radialAngle);
        double pointY = - 0.5*channel->channelPtr->getWidth()*std::cos(channel->radialAngle) -
                        0.5*nextChannel->channelPtr->getWidth()*std::cos(nextChannel->radialAngle);

        if ( sqrt(pointX*pointX + pointY*pointY) >= radius && angle <= M_PI) {
            /* We add a single coordinate to the sequence*/
            int vertexId = vertices_.size();
            Coordinate newPointTop = Coordinate(pointX, pointY, 0.5*height) + Coordinate(networkNode.getPosition());
            Coordinate newPointBottom = Coordinate(pointX, pointY, -0.5*height) + Coordinate(networkNode.getPosition());
            vertices_.push_back(std::make_shared<Vertex>(vertexId, newPointTop));
            vertices_.push_back(std::make_shared<Vertex>(vertexId+1, newPointBottom));
            crownVertexIds.push_back(vertexId);
            bodyVertexIds.push_back(vertexId);
            bodyVertexIds.push_back(vertexId+1);
            /* The single coordinate is referenced to the current and next channel as:
                points 0, 4 and 1, 5 if we are currently at node A
                points 2, 6 and 3, 7 if we are currently at node B */
            if (id == channel->channelPtr->getNodeA()->getId()) {
                channelVertices.at(channel->channelId)[0] = vertexId+1;
                channelVertices.at(channel->channelId)[4] = vertexId;
            } else if (id == channel->channelPtr->getNodeB()->getId()) {
                channelVertices.at(channel->channelId)[2] = vertexId+1;
                channelVertices.at(channel->channelId)[6] = vertexId;
            }
            if (id == nextChannel->channelPtr->getNodeA()->getId()) {
                channelVertices.at(nextChannel->channelId)[1] = vertexId+1;
                channelVertices.at(nextChannel->channelId)[5] = vertexId;
            } else if (id == nextChannel->channelPtr->getNodeB()->getId()) {
                channelVertices.at(nextChannel->channelId)[3] = vertexId+1;
                channelVertices.at(nextChannel->channelId)[7] = vertexId;
            }
        } else {
            double angle1 = channel->radialAngle + std::atan2(channel->channelPtr->getWidth(), radius);
            Coordinate p1 = Coordinate(networkNode.getPosition()) + Coordinate(radius*std::cos(angle1), radius*std::sin(angle1), 0.5*height);
            Coordinate p1_m = Coordinate(networkNode.getPosition()) + Coordinate(radius*std::cos(angle1), radius*std::sin(angle1), -0.5*height);

            double angle2 = nextChannel->radialAngle - std::atan2(nextChannel->channelPtr->getWidth(), radius);
            Coordinate p2 = Coordinate(networkNode.getPosition()) + Coordinate(radius*std::cos(angle2), radius*std::sin(angle2), 0.5*height);
            Coordinate p2_m = Coordinate(networkNode.getPosition()) + Coordinate(radius*std::cos(angle2), radius*std::sin(angle2), -0.5*height);

            auto topPizza = Pizza({vertices_[topCenterId]->position, p1, p2}, resolution);

            /* We add the cornicione set of coordinates to the sequence */
            /* The start of the cornicione is point 4 (nodeA) or point 6 (nodeB) of the current channel
                The end of the cornicione is point 5 (nodeA) or point 7 (nodeB) of the next channel */

            /**
             * TODO: Simply store the center, p1 and p2 values for pizzas, top and bottom. Store triangles for channel attachments.
             * The primitives will be constructed in NetworkSTL::nodeToSTL
             */

            int v1 = vertices_.size();
            int v1_m = vertices_.size()+1;
            vertices_.push_back(std::make_shared<Vertex>(v1, p1));
            vertices_.push_back(std::make_shared<Vertex>(v1_m, p1_m));

            int v2 = vertices_.size();
            int v2_m = vertices_.size()+1;
            vertices_.push_back(std::make_shared<Vertex>(v2, p2));
            vertices_.push_back(std::make_shared<Vertex>(v2_m, p2_m));

            Pizza(0, std::vector<std::shared_ptr<Vertex>>{center, v1, v2});
            Pizza.getCornicione(resolution);
        }
    }
}

void NodeSTL::render()
{
    /** TODO:
     * Close the node by defining the faces based on the entire state.
     *  -> Node sections (circular section) that is attachd to node is a top-down triangle face.
     *  -> "Free" Node sections are top down pizza-slices, consisting of circ. resolution no. pizzas.
     */
}

} // namespace stl