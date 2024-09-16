#include "jsonParser.h"

#include "jsonReader.hh"

namespace parser {

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

arch::Network networkFromJSON(std::string jsonFile) {

    std::ifstream f(jsonFile);
    json jsonString = json::parse(f);

    arch::Network network = networkFromJSON(jsonString);

    return network;
}

void networkFromJSON(std::string jsonFile, arch::Network& network) {

    std::ifstream f(jsonFile);
    json jsonString = json::parse(f);

    readNodes(jsonString, network);
    readChannels(jsonString, network);
}

arch::Network networkFromJSON(json jsonString) {

    arch::Network network;

    readNodes(jsonString, network);
    readChannels(jsonString, network);

    return network;
}

}   // namespace parser
