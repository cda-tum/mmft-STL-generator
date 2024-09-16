#include "jsonReader.h"

namespace parser {

void readNodes(json jsonString, arch::Network& network) {
    for (auto& node : jsonString["network"]["nodes"]) {
        if (!node.contains("x") || !node.contains("y") || !node.contains("z")) {
            throw std::invalid_argument("Node is ill-defined. Please define:\nx\ny\nz");
        }
        network.addNode(node["x"], node["y"], node["z"]);
    }
}

void readChannels(json jsonString, arch::Network& network) {
    for (auto& channel : jsonString["network"]["channels"]) {
        if (!channel.contains("node1") || !channel.contains("node2") || !channel.contains("height") || !channel.contains("width")) {
            throw std::invalid_argument("Channel is ill-defined. Please define:\nnode1\nnode2\nheight\nwidth");
        }
        network.addChannel(channel["node1"], channel["node2"], channel["width"], channel["height"]);
    }
}

}   // namespace parser
