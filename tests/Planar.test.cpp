/**
 * @brief Tests for planar networks
 */

#include "gtest/gtest.h"

#include "../src/architecture/pNetwork.h"
#include "../src/parser/pjsonParser.h"
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

    networkStl.writeSTL("cubeTest");

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

    EXPECT_EQ(networkStl.getNoVertices(), 14); // two additional vertices for node center
    EXPECT_EQ(networkStl.getNoFaces(), 20);
    EXPECT_EQ(networkStl.getNoPrimitives(), 4);

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

}


TEST(Planar, Kink15) {

    // define network
    stl::Network network;

    // nodes
    auto node1 = network.addNode(std::cos(0.0), std::sin(0.0), 0.0);
    auto node2 = network.addNode(std::cos(M_PI/12.0), std::sin(M_PI/12.0), 0.0); // 15 deg
    auto node3 = network.addNode(0.0, 0.0, 0.0);

    // channels
    network.addChannel(node1->getId(), node3->getId(), 0.2, 0.2);
    network.addChannel(node2->getId(), node3->getId(), 0.2, 0.2);

    network.updateGrounds();

    stl::NetworkSTL networkStl(std::make_shared<stl::Network>(network), 25);

    EXPECT_EQ(networkStl.getNoVertices(), 64);
    EXPECT_EQ(networkStl.getNoFaces(), 124);
    EXPECT_EQ(networkStl.getNoPrimitives(), 31);

}

TEST(Planar, Kink30) {

    // define network
    stl::Network network;

    // nodes
    auto node1 = network.addNode(std::cos(M_PI/12.0), std::sin(M_PI/12.0), 0.0); // 15 deg
    auto node2 = network.addNode(std::cos(0.25*M_PI), std::sin(0.25*M_PI), 0.0); // 45 deg
    auto node3 = network.addNode(0.0, 0.0, 0.0);

    // channels
    network.addChannel(node1->getId(), node3->getId(), 0.5, 0.5);
    network.addChannel(node2->getId(), node3->getId(), 0.5, 0.5);

    network.updateGrounds();

    stl::NetworkSTL networkStl(std::make_shared<stl::Network>(network), 25);

    EXPECT_EQ(networkStl.getNoVertices(), 64);
    EXPECT_EQ(networkStl.getNoFaces(), 124);
    EXPECT_EQ(networkStl.getNoPrimitives(), 31);

}

TEST(Planar, Kink45) {

    // define network
    stl::Network network;

    // nodes
    auto node1 = network.addNode(std::cos(M_PI/6.0), std::sin(M_PI/6.0), 0.0); // 15 deg
    auto node2 = network.addNode(std::cos(M_PI/2.4), std::sin(M_PI/2.4), 0.0); // 75 deg
    auto node3 = network.addNode(0.0, 0.0, 0.0);

    // channels
    network.addChannel(node1->getId(), node3->getId(), 0.5, 0.5);
    network.addChannel(node2->getId(), node3->getId(), 0.5, 0.5);

    network.updateGrounds();

    stl::NetworkSTL networkStl(std::make_shared<stl::Network>(network), 25);

    EXPECT_EQ(networkStl.getNoVertices(), 64);
    EXPECT_EQ(networkStl.getNoFaces(), 124);
    EXPECT_EQ(networkStl.getNoPrimitives(), 31);

}

TEST(Planar, Kink60) {

    // define network
    stl::Network network;

    // nodes
    auto node1 = network.addNode(std::cos(M_PI/12.0), std::sin(M_PI/12.0), 0.0); // 30 deg
    auto node2 = network.addNode(std::cos(M_PI/2.4), std::sin(M_PI/2.4), 0.0); // 75 deg
    auto node3 = network.addNode(0.0, 0.0, 0.0);

    // channels
    network.addChannel(node1->getId(), node3->getId(), 0.5, 0.5);
    network.addChannel(node2->getId(), node3->getId(), 0.5, 0.5);

    network.updateGrounds();

    stl::NetworkSTL networkStl(std::make_shared<stl::Network>(network), 25);

    EXPECT_EQ(networkStl.getNoVertices(), 64);
    EXPECT_EQ(networkStl.getNoFaces(), 124);
    EXPECT_EQ(networkStl.getNoPrimitives(), 31);

}

TEST(Planar, Kink90) {

    // define network
    stl::Network network;

    // nodes
    auto node1 = network.addNode(std::cos(M_PI), std::sin(M_PI), 0.0);  // 180 deg
    auto node2 = network.addNode(std::cos(1.5*M_PI), std::sin(1.5*M_PI), 0.0); // 270 deg
    auto node3 = network.addNode(0.0, 0.0, 0.0);

    // channels
    network.addChannel(node1->getId(), node3->getId(), 0.5, 0.5);
    network.addChannel(node2->getId(), node3->getId(), 0.5, 0.5);

    network.updateGrounds();

    stl::NetworkSTL networkStl(std::make_shared<stl::Network>(network), 25);

    EXPECT_EQ(networkStl.getNoVertices(), 64);
    EXPECT_EQ(networkStl.getNoFaces(), 124);
    EXPECT_EQ(networkStl.getNoPrimitives(), 31);

}

TEST(Planar, Kink135) {

    // define network
    stl::Network network;

    // nodes
    auto node1 = network.addNode(std::cos(M_PI), std::sin(M_PI), 0.0); // 180 deg
    auto node2 = network.addNode(std::cos(0.25*M_PI), std::sin(0.25*M_PI), 0.0); // 45 deg
    auto node3 = network.addNode(0.0, 0.0, 0.0);

    // channels
    network.addChannel(node1->getId(), node3->getId(), 0.5, 0.5);
    network.addChannel(node2->getId(), node3->getId(), 0.5, 0.5);

    network.updateGrounds();

    stl::NetworkSTL networkStl(std::make_shared<stl::Network>(network), 25);

    EXPECT_EQ(networkStl.getNoVertices(), 64);
    EXPECT_EQ(networkStl.getNoFaces(), 124);
    EXPECT_EQ(networkStl.getNoPrimitives(), 31);

}

TEST(Planar, ThreeWay1) {

    // define network
    stl::Network network;

    // nodes
    auto node1 = network.addNode(std::cos(M_PI/6.0), std::sin(M_PI/6.0), 0.0); // 30 deg
    auto node2 = network.addNode(std::cos(0.75*M_PI), std::sin(0.75*M_PI), 0.0); // 135 deg
    auto node3 = network.addNode(std::cos(1.5*M_PI), std::sin(1.5*M_PI), 0.0); // 270 deg
    auto node4 = network.addNode(0.0, 0.0, 0.0);

    // channels
    network.addChannel(node1->getId(), node4->getId(), 0.2, 0.2);
    network.addChannel(node2->getId(), node4->getId(), 0.2, 0.2);
    network.addChannel(node3->getId(), node4->getId(), 0.2, 0.2);

    network.updateGrounds();

    stl::NetworkSTL networkStl(std::make_shared<stl::Network>(network), 25);

    EXPECT_EQ(networkStl.getNoVertices(), 20);
    EXPECT_EQ(networkStl.getNoFaces(), 36);
    EXPECT_EQ(networkStl.getNoPrimitives(), 6);

}

TEST(Planar, ThreeWay2) {

    // define network
    stl::Network network;

    // nodes
    auto node1 = network.addNode(std::cos(M_PI/6.0), std::sin(M_PI/6.0), 0.0); // 30 deg
    auto node2 = network.addNode(std::cos(0.75*M_PI), std::sin(0.75*M_PI), 0.0); // 135 deg
    auto node3 = network.addNode(std::cos(0.5*M_PI), std::sin(0.5*M_PI), 0.0); // 90 deg
    auto node4 = network.addNode(0.0, 0.0, 0.0);

    // channels
    network.addChannel(node1->getId(), node4->getId(), 0.2, 0.2);
    network.addChannel(node2->getId(), node4->getId(), 0.2, 0.2);
    network.addChannel(node3->getId(), node4->getId(), 0.2, 0.2);

    network.updateGrounds();

    stl::NetworkSTL networkStl(std::make_shared<stl::Network>(network), 25);

    EXPECT_EQ(networkStl.getNoVertices(), 70);
    EXPECT_EQ(networkStl.getNoFaces(), 136);
    EXPECT_EQ(networkStl.getNoPrimitives(), 33);

}