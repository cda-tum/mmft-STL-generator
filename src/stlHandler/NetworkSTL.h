/**
 * @file Stl.h
 */

#pragma once

#include <memory>
#include <vector>

#include "BaseSTL.h"

namespace arch {

class Network;

}

namespace stl
{

struct Vertex;
struct Face;
struct Rectangle;
struct Trapezoid;
struct Cuboid;
struct Channel;
struct TrapezoidalPrism;
struct TrapezoidalChannel;

class NetworkSTL : public BaseSTL {

protected:

    std::shared_ptr<arch::Network> networkPtr;

public:
    NetworkSTL(std::shared_ptr<arch::Network> network);

};

} // namespace arch