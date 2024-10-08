#include <iostream>

#include "architecture/pNetwork.hh"
#include "parser/pjsonParser.hh"
#include "stlHandler/BaseSTL.hh"
#include "stlHandler/NetworkSTL.hh"

int main(int argc, char const* argv []) {

    std::string file = argv[1];
    std::string stlFile = argv[2];

    // Load and set the network from a JSON file
    std::cout << "[Main] Create network object..." << std::endl;
    auto network = std::make_shared<stl::Network>(stl::networkFromJSON(file));

    std::cout << "[Main] Create STL object..." << std::endl;
    stl::NetworkSTL networkStl(network);

    std::cout << "[Main] Write STL..." << std::endl;
    networkStl.writeSTL(stlFile);

    std::cout << "[Main] ...done" << std::endl;

    return 0;
}