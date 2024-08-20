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

    // These vertices form the top ring of the cylindrical node
    // They will be used to derive most other coordinates
    std::vector<std::shared_ptr<Vertex>> crownVertices;

    /** TODO:
     * 
     * Loop through reach and define the angle at which the channels are positioned -> Topology Analysis.
     *  -> nodeRadius == largest channel width (for now)
     *  -> nodeHeight == largest channel height (for now)
     * Define the vertex positions for node-channel interface
     *  -> Here we check if neighboring channel "intersection" points are > nodeRadius or not.
     *  -> The height is still determined by channe. -> If smaller than node -> special treatment.
     * Define these vertices and store the vertex id's accoringly for the channels later.
     * Close the rest of the node:
     *  -> Sections attached to channel are top-down triangle faces.
     *  -> "Free" sections are top down pizza-pieces, consisting of a large no. of faces.
     */
}

} // namespace stl