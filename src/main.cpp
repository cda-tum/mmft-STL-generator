#include <iostream>

#include "architecture/Network.h"
#include "jsonParser.h"
#include "stlHandler/NetworkSTL.h"

int main(int argc, char const* argv []) {

    std::string file = argv[1];
    std::string stlFile = argv[2];

    // Load and set the network from a JSON file
    std::cout << "[Main] Create network object..." << std::endl;
    std::shared_ptr<arch::Network> network = parser::networkFromJSON(file);

    stl::NetworkSTL networkStl(network);
    networkStl.writeSTL(stlFile);

    return 0;
}