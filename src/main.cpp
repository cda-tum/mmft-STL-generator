#include <iostream>

#include "architecture/Network.h"
#include "stlHandler/Stl.h"

int main(int argc, char const* argv []) {

    std::string file = argv[1];

    // Load and set the network from a JSON file
    std::cout << "[Main] Create network object..." << std::endl;
    arch::Network network = parser::networkFromJSON<T>(file);

    STL stl = network.toSTL();

    stl.scale(double[]);
    stl.translate(double[]);
    st.rotate(double[]);

    return 0;
}