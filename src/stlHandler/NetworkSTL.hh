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
    id(networkNode_.getId()), networkNode(networkNode), reach(reach_) 
{
    /** TODO:
     * Loop through reach and define the angle at which the channels are positioned -> Topology Analysis.
     *  -> nodeRadius == largest channel width (for now)
     *  -> nodeHeight == largest channel height (for now)
     */
}

void NodeSTL::extractCrown()
{
    /** TODO:
     * Based on the node position and channel height, set the height for crown vertices.
     * Define the crown vertex positions for top-down node-channel interface, also store in bodyVertices
     *  -> Here we check if neighboring channel "intersection" points are > nodeRadius or not.
     */
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