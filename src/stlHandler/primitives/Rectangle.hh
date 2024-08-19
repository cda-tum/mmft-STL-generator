#include "Rectangle.h"

namespace stl
{

Rectangle::Rectangle(int id_, std::vector<std::shared_ptr<Vertex>> vertices_) :
    Primitive(id_, vertices_)
    {
        /** TODO:
         * check if #vertices == 4
         * create two faces and see if they are in the same plane
         * check if the two faces constitute a rectangle (i.e. borders are parallel)
         * set normal value
         */
    }

Rectangle::Rectangle(int id_, std::vector<Face> faces) :
    Primitive(id_) 
    {
        /** TODO:
         * check if #faces == 2
         * check if the two faces are in the same plane, i.e. normals are close enough
         * check if the two faces share two vertices
         * check if the two faces constitute a rectangle (i.e. borders are parallel)
         * set normal value
         */
    }

void Rectangle::render() {
    /** TODO:
     * If we don't have two faces yet,
     * create the two faces that consitute this rectangle.
     */
}

}   // namespace stl