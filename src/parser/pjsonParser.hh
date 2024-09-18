#include "pjsonParser.h"

#include "pjsonReader.hh"

namespace stl {

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

Network networkFromJSON(std::string jsonFile) {

    std::ifstream f(jsonFile);
    json jsonString = json::parse(f);

    Network network = networkFromJSON(jsonString);

    return network;
}

void networkFromJSON(std::string jsonFile, Network& network) {

    std::ifstream f(jsonFile);
    json jsonString = json::parse(f);

    readNodes(jsonString, network);
    readChannels(jsonString, network);
}

Network networkFromJSON(json jsonString) {

    Network network;

    readNodes(jsonString, network);
    readChannels(jsonString, network);
    network.updateGrounds();

    return network;
}

}   // namespace parser
