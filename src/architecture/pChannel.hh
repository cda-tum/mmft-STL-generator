#include "pChannel.h"

namespace stl {

Channel::Channel(int id_, std::shared_ptr<Node> nodeA_, std::shared_ptr<Node> nodeB_, ChannelShape shape_) :
    id(id_), nodeA(nodeA_), nodeB(nodeB_), shape(shape_) { }

void Channel::setChannelShape(ChannelShape shape_) 
{
    shape = shape_;
}

void Channel::setNodeA(const std::shared_ptr<Node>& nodeA_) 
{
    nodeA = nodeA_;
}

void Channel::setNodeB(const std::shared_ptr<Node>& nodeB_) 
{
    nodeB = nodeB_;
}

//=====================================================================================
//=========================  RectangularChannel =======================================
//=====================================================================================

RectangularChannel::RectangularChannel(int id_, std::shared_ptr<Node> nodeA_, std::shared_ptr<Node> nodeB_) :
    Channel(id_, nodeA_, nodeB_, ChannelShape::RECTANGULAR) { }

void RectangularChannel::setHeight(double height_) 
{
    height = height_;
}

void RectangularChannel::setWidth(double width_) 
{
    width = width_;
}

}   // namespace arch