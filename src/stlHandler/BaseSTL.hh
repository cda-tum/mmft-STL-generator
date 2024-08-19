# include "BaseSTL.h"

namespace stl {

    BaseSTL::BaseSTL() {
        /** TODO:
         * 
         */
    }

    BaseSTL::STL(arch::Network network) {
        /** TODO:
         * 
         */
    }

    std::shared_ptr<Vertex> BaseSTL::addVertex(double x, double y, double z) {
        /** TODO:
         * 
         */
    }

    std::shared_ptr<Face> BaseSTL::addFace() {
        /** TODO:
         * Reset id of face to its vector position
         */
    }

    std::shared_ptr<Rectangle> BaseSTL::addRectangle() {
        /** TODO:
         * 
         */
    }

    std::shared_ptr<Cuboid> BaseSTL::addCuboid() {
        /** TODO:
         * 
         */
    }

    void BaseSTL::render() {
        /** TODO:
         * 
         * Loop through all primitives and add the composing faces to the faces vector.
         * Erase the processed primitives.
         */
    }

    void BaseSTL::translate(double x, double y, double z) {
        /** TODO:
         * 
         * Loop through all vertices and translate their coordinates according to translation coordinates.
         */
    }

    void BaseSTL::scale(double x, double y, double z, double center[3]) {
        /** TODO:
         * 
         * Loop through all vertices and translate their coordinates according to scaling.
         */
    }

    void BaseSTL::rotate(double x, double y, double z, double center[3]) {
        /** TODO:
         * 
         * Loop through all vertices and translate their coordinates according to rotation.
         */
    }

    void BaseSTL::invertFaces() {
        /** TODO:
         * 
         * Loop through all faces and invert their normal direction and the vertex order.
         */
    }

    void BaseSTL::writeSTL(std::string file) {
        /** TODO:
         * 
         * Loop through all the faces and generate the STL file
         */
    }
    
}   // namespace stl