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
            groundNodeToSTL(node);
            return;
        } else {
            nodeToSTL(node);
        }
    }

    for (auto channel: network->getChannels()) {
        channelToSTL(channel);
    }

}

void NetworkSTL::nodeToSTL(const arch::Node& node) 
{
    // A node has a set of channels attached to it (reach)
    std::unordered_map<int, std::shared_ptr<arch::Channel>> reach = networkPtr->getReach(node.getId());

    NodeSTL stlNode(node, reach);

    stlNode.extractCrown();

    stlNode.extrapolateVertices();

    stlNode.render();

    /** TODO:
     * Close the rest of the node:
     *  -> Sections attached to channel are top-down triangle faces.
     *  -> "Free" sections are top down pizza-pieces, consisting of a large no. of faces.
     */
}

NodeSTL::NodeSTL(const arch::Node& networkNode_, const std::unordered_map<int, std::shared_ptr<arch::Channel>>& reach_) :
    id(networkNode_.getId()), networkNode(networkNode)
{   
    // Loop through reach and set this node's height and radius.
    height = 0.0;
    radius = 0.0;
    for (auto& [key, channel] : reach_) {
        if (channel->getHeight() > height) { height = channel->getHeight(); }
        if (channel->getWidth() > 2*radius) { radius = 0.5*channel->getWidth(); }
    }

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

void NodeSTL::extractCrown()
{

    for (auto channel = channelOrder.begin(); channel != channelOrder.end(); ++channel) {

        auto nextChannel = channelOrder.begin();
        if (channel != channelOrder.end()) {
            auto nextChannel = channel + 1;
        }
        
        double pointX = 0.5*channel->channelPtr->getWidth()*std::sin(channel->radialAngle) +
                        0.5*nextChannel->channelPtr->getWidth()*std::sin(nextChannel->radialAngle);
        double pointY = - 0.5*channel->channelPtr->getWidth()*std::cos(channel->radialAngle) -
                        0.5*nextChannel->channelPtr->getWidth()*std::cos(nextChannel->radialAngle);

        if ( sqrt(pointX*pointX + pointY*pointY) >= radius) {
            /* We add a single coordinate to the sequence*/
            crownVertices.push_back(Coordinate(pointX, pointY, 0.5*height) + Coordinate(networkNode.getPosition()));
            /* The single coordinate is referenced to the current and next channel as:
                points 4 and 5 if we are currently at node A
                points 6 and 7 if we are currently at node B*/
        } else {
            /* We add the cornicione set of coordinates to the sequence */
            /* The start of the cornicione is point 4 (nodeA) or point 6 (nodeB) of the current channel
                The end of the cornicione is point 5 (nodeA) or point 7 (nodeB) of the next channel*/
        }
    }
}

void NodeSTL::extrapolateVertices() 
{
    /** TODO:
     * Define the remaining vertices in bodyVertices
     *  -> I.e., mirror the bottom ring of vertices and extrapolate eventual additional vertices for channels
     *      with channelHeight < nodeHeight.
     *  -> Define and store the vertices that are shared between the current node and each channel.
     */
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