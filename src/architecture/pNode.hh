#include "pNode.h"

namespace stl {

Node::Node(int id_, double x_, double y_, double z_, bool ground_) :
    id(id_), position({x_, y_, z_}), ground(ground_) { }

void Node::setGround(bool ground_) 
{
    ground = ground_;
}

void Node::setPosition(double x_, double y_, double z_) 
{
    setPosition({x_, y_, z_});
}

void Node::setPosition(std::array<double,3> position_) 
{
    position = position_;
}

}   // namespace arch