/**
 * @file Primitives.h
 */

#pragma once

#include <memory>

namespace stl
{

struct Vertex {

    int id;
    double coordinate[3];

    Vertex() {
        /** TODO:
         * 
         */
    }

};

struct Face {

    int id;
    std::shared_ptr<Vertex> vertices[3];
    double normal[3];

    Face() {
        /** TODO:
         * 
         */
    }

};

struct Rectangle {

    int id;
    std::shared_ptr<Vertex> vertices[4];
    double normal[3];

    Rectangle(Vertex vertices[4]) {
        /** TODO:
         * 
         */
    }

    Rectangle(Face face[2]) {
        /** TODO:
         * 
         */
    }

};

struct Trapezoid {

    int id;
    std::shared_ptr<Vertex> vertices[4];
    double normal[3];

    Trapezoid(Vertex vertices[4]) {
        /** TODO:
         * 
         */
    }

    Trapezoid(Face face[2]) {
        /** TODO:
         * 
         */
    }

};

struct Cuboid {
    
    int id;
    std::shared_ptr<Vertex> vertices[8];
    double dimension[3];
    double normal1[3];  // points in local positive x direction (dimension[0])
    double normal2[3];  // points in local positive y direction (dimension[1])

    Cuboid() {
        /** TODO:
         * 
         */
    }
};

struct Channel {
    
    int id;
    std::shared_ptr<Vertex> vertices[8];
    double dimension[3];
    double normal1[3];  // points in local positive x direction dimension[0]
    double normal2[3];  // points in local positive y direction dimension[1]
    unsigned short hollowDir;  // 0, 1, or 2; i.e., 0 -> hollow in dimension[0]

    Channel() {
        /** TODO:
         * 
         */
    }
};

struct TrapezoidalPrism {
    
    int id;
    std::shared_ptr<Vertex> vertices[8];
    double dimension[3];
    double normal1[3];  // points in local positive x direction (dimension[0])
    double normal2[3];  // points in local positive y direction (dimension[1])

    TrapezoidalPrism() {
        /** TODO:
         * 
         */
    }
};

struct TrapezoidalChannel {
    
    int id;
    std::shared_ptr<Vertex> vertices[8];
    double dimension[3];
    double normal1[3];  // points in local positive x direction (dimension[0])
    double normal2[3];  // points in local positive y direction (dimension[1])
    unsigned short hollowDir;  // 0, 1, or 2; i.e., 0 -> hollow in dimension[0]

    TrapezoidalChannel() {
        /** TODO:
         * 
         */
    }
};

}   // namespace stl