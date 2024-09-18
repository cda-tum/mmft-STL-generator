/**
 * @file Channel.h
 */

#pragma once

#include <memory>

namespace stl
{

class Node {

private:

    int id;
    std::array<double,3> position;
    bool ground = false;

public:

    Node(int id, double x, double y, double z, bool ground=false);

    int getId() const { return id; };

    void setGround(bool ground);

    bool getGround() const { return ground; };

    void setPosition(double x, double y, double z);

    void setPosition(std::array<double,3> position);

    std::array<double,3> getPosition() const { return position; };

};

} // namespace arch