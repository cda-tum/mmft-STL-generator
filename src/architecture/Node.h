/**
 * @file Channel.h
 */

#pragma once

#include <memory>

namespace arch
{

class Node {

private:

    int id;
    std::array<double,3> position;
    bool ground = false;

public:

    Node(int id, double x, double y, double z, bool ground=false);

    int getId() const;

    void setGround(bool ground);

    bool getGround() const;

    void setPosition(double position[3]);

    std::array<double,3> getPosition() const;

};

} // namespace arch