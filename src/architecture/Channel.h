/**
 * @file Channel.h
 */

#pragma once

#include <memory>
#include <stdexcept>

namespace arch
{

class Node;

/**
 * @brief An enum to specify the shape of channel.
 */
enum class ChannelShape {
    NONE,
    RECTANGULAR, ///< A channel with a rectangular cross-section
    CYLINDRICAL  ///< A channel with a circular cross-section
};

class Channel {

protected:
    int id;
    std::shared_ptr<Node> nodeA;
    std::shared_ptr<Node> nodeB;
    ChannelShape shape = ChannelShape::NONE;

public:
    Channel();

    int getId() const;

    void setChannelShape(ChannelShape shape);

    ChannelShape getChannelShape() const;

    void setNodeA(const std::shared_ptr<Node>& node);

    std::shared_ptr<Node> getNodeA() const;

    void setNodeB(const std::shared_ptr<Node>& node);

    std::shared_ptr<Node> getNodeB() const;

    virtual double getHeight() const {
        throw std::runtime_error("Tried to obtain channel height from non-Rectangular channel");
    };

    virtual double getWidth() const {
        throw std::runtime_error("Tried to obtain channel width from non-Rectangular channel");
    };
};


class RectangularChannel : public Channel {

private:
    double height;
    double width;

public:

    void setHeight(double height);

    double getHeight() const override { return height; }

    void setWidth(double width);

    double getWidth() const override { return width; }
};

} // namespace arch