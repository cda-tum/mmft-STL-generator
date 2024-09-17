/**
 * @brief Tests for planar networks
 */

#include "gtest/gtest.h"

#include "../src/architecture/Network.h"
#include "../src/parser/jsonParser.h"
#include "../src/stlHandler/BaseSTL.h"
#include "../src/stlHandler/NetworkSTL.h"

TEST(Planar, Cube) {

    // define network
    stl::Network network;

    // nodes
    auto node1 = network.addNode(-1.0, 0.0, 0.0);
    auto node2 = network.addNode(1.0, 0.0, 0.0);

    // channels
    network.addChannel(node1->getId(), node2->getId(), 1.0, 1.0);

    network.updateGrounds();

    stl::NetworkSTL networkStl(std::make_shared<stl::Network>(network));

    EXPECT_EQ(networkStl.getNoVertices(), 8);
    EXPECT_EQ(networkStl.getNoFaces(), 12);
    EXPECT_EQ(networkStl.getNoPrimitives(), 3);

}

TEST(Planar, Channel) {

    // define network
    stl::Network network;

    // nodes
    auto node1 = network.addNode(-1.0, 0.0, 0.0);
    auto node2 = network.addNode(1.0, 0.0, 0.0);
    auto node3 = network.addNode(0.0, 0.0, 0.0);

    // channels
    network.addChannel(node1->getId(), node3->getId(), 1.0, 1.0);
    network.addChannel(node2->getId(), node3->getId(), 1.0, 1.0);

    network.updateGrounds();

    stl::NetworkSTL networkStl(std::make_shared<stl::Network>(network));

    EXPECT_EQ(networkStl.getNoVertices(), 12);
    EXPECT_EQ(networkStl.getNoFaces(), 20);
    EXPECT_EQ(networkStl.getNoPrimitives(), 4);

    networkStl.printVertices();

}

TEST(Planar, Cross) {

    // define network
    stl::Network network;

    // nodes
    auto node1 = network.addNode(-1.0, 0.0, 0.0);
    auto node2 = network.addNode(1.0, 0.0, 0.0);
    auto node3 = network.addNode(0.0, 0.0, 0.0);
    auto node4 = network.addNode(0.0, -1.0, 0.0);
    auto node5 = network.addNode(0.0, 1.0, 0.0);

    // channels
    network.addChannel(node1->getId(), node3->getId(), 1.0, 1.0);
    network.addChannel(node2->getId(), node3->getId(), 1.0, 1.0);
    network.addChannel(node4->getId(), node3->getId(), 1.0, 1.0);
    network.addChannel(node5->getId(), node3->getId(), 1.0, 1.0);

    network.updateGrounds();

    stl::NetworkSTL networkStl(std::make_shared<stl::Network>(network));

    EXPECT_EQ(networkStl.getNoVertices(), 26);
    EXPECT_EQ(networkStl.getNoFaces(), 48);
    EXPECT_EQ(networkStl.getNoPrimitives(), 8);

    networkStl.printVertices();

}
