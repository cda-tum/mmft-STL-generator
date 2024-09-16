#include <iostream>

#include "architecture/Network.hh"
#include "parser/jsonParser.hh"
#include "stlHandler/BaseSTL.hh"
#include "stlHandler/NetworkSTL.hh"

int main(int argc, char const* argv []) {

    std::string file = argv[1];
    std::string stlFile = argv[2];

    // Load and set the network from a JSON file
    std::cout << "[Main] Create network object..." << std::endl;
    auto network = std::make_shared<arch::Network>(parser::networkFromJSON(file));

    stl::NetworkSTL networkStl(network);
    networkStl.writeSTL(stlFile);

    return 0;
}