/**
 * @file Network.h
 */

#pragma once

#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

namespace arch
{

class Node;

class Channel;

class Network {

private:

    std::vector<Node> nodes;
    std::vector<Channel> channels;

    std::set<int> groundNodeIds;

    std::unordered_map<int, std::unordered_map<int, std::shared_ptr<Channel>> reach;

public:
    Network();

};

} // namespace arch