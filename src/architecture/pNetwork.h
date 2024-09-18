/**
 * @file Network.h
 */

#pragma once

#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

#include "pNode.h"
#include "pChannel.h"

namespace stl
{

class Node;

class Channel;

class Network {

private:

    std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::shared_ptr<Channel>> channels;

    std::set<int> groundNodeIds;

    std::unordered_map<int, std::unordered_map<int, std::shared_ptr<Channel>>> reach;

public:

    Network();

    std::shared_ptr<Node> addNode(double x, double y, double z, bool ground=false);

    std::shared_ptr<Channel> addChannel(int nodeIdA, int nodeIdB, double width, double height);

    std::vector<std::shared_ptr<Node>>& getNodes() { return nodes; }

    std::shared_ptr<Node> getNode(int nodeId) { return nodes[nodeId]; }

    std::vector<std::shared_ptr<Channel>>& getChannels() { return channels; }

    std::shared_ptr<Channel> getChannel(int channelId) { return channels[channelId]; }

    std::unordered_map<int, std::unordered_map<int, std::shared_ptr<Channel>>>& getReach() { return reach; }

    std::unordered_map<int, std::shared_ptr<Channel>>& getReach(int nodeId) { return reach[nodeId]; }

    void updateGrounds();

};

} // namespace arch