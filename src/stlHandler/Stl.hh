# include "Stl.h"

namespace stl {

    STL::STL() {
        /** TODO:
         * 
         */
    }

    STL::STL(arch::Network network) {
        /** TODO:
         * 
         */
    }

    std::shared_ptr<Vertex> STL::addVertex(double x, double y, double z) {
        /** TODO:
         * 
         */
    }

    std::shared_ptr<Face> STL::addFace() {
        /** TODO:
         * 
         */
    }

    std::shared_ptr<Rectangle> STL::addRectangle() {
        /** TODO:
         * 
         */
    }

    std::shared_ptr<Cuboid> STL::addCuboid() {
        /** TODO:
         * 
         */
    }

    void STL::render() {
        /** TODO:
         * 
         * Loop through all primitives and add the composing faces to the faces vector.
         * Erase the processed primitives.
         */
    }

    void STL::translate(double x, double y, double z) {
        /** TODO:
         * 
         * Loop through all vertices and translate their coordinates according to translation coordinates.
         */
    }

    void STL::scale(double x, double y, double z, double center[3]) {
        /** TODO:
         * 
         * Loop through all vertices and translate their coordinates according to scaling.
         */
    }

    void STL::rotate(double x, double y, double z, double center[3]) {
        /** TODO:
         * 
         * Loop through all vertices and translate their coordinates according to rotation.
         */
    }

    void invertFaces() {
        /** TODO:
         * 
         * Loop through all faces and invert their normal direction and the vertex order.
         */
    }

    void STL::writeSTL(std::string file) {
        /** TODO:
         * 
         * Loop through all the faces and generate the STL file
         */
    }
    
}   // namespace stl