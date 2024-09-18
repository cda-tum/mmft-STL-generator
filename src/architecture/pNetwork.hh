#include "pNetwork.h"

#include "pChannel.hh"
#include "pNode.hh"

namespace stl {

Network::Network() { }

std::shared_ptr<Node> Network::addNode(double x, double y, double z, bool ground)
{
    int nodeId = nodes.size();
    auto newNode = std::make_shared<Node>(nodeId, x, y, z, ground);
    nodes.push_back(newNode);
    if (ground) 
    {
        groundNodeIds.emplace(nodeId);
    }
    reach.try_emplace(nodeId, std::unordered_map<int, std::shared_ptr<Channel>>());
    
    return newNode;
}

std::shared_ptr<Channel> Network::addChannel(int nodeIdA, int nodeIdB, double width, double height) 
{
    int channelId = channels.size();
    if (nodeIdA >= nodes.size() || nodeIdB >= nodes.size()) 
    {
        throw std::invalid_argument("Tried to create channel to undefined node.");
    }
    else 
    {
        auto newChannel = std::make_shared<RectangularChannel>(channelId, nodes[nodeIdA], nodes[nodeIdB]);
        newChannel->setWidth(width);
        newChannel->setHeight(height);
        channels.push_back(newChannel);
        reach.at(nodeIdA).try_emplace(channelId, newChannel);
        reach.at(nodeIdB).try_emplace(channelId, newChannel);
        
        return newChannel;
    }
}

void Network::updateGrounds() {
    for (auto node : nodes) {
        if (reach.at(node->getId()).size() == 1) {
            node->setGround(true);
        }
    }
}

}   // namespace arch