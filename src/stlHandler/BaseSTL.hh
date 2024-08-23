# include "BaseSTL.h"

namespace stl {

BaseSTL::BaseSTL() { }

std::tuple<bool, unsigned int> BaseSTL::findDuplicate(Coordinate c) 
{
    for (auto v : vertices) {
        if (std::abs(v->position.x - c.x) < resolution) {
            if (std::abs(v->position.x - c.x) < resolution) {
                if (std::abs(v->position.x - c.x) < resolution) {
                    return {true, v->id};
                }
            }
        }
    }
    return {false, 0};
}

std::shared_ptr<Vertex> BaseSTL::addVertex(std::array<double,3> position) 
{
    int vertexId = vertices.size();
    std::shared_ptr<Vertex> newVertex = std::make_shared<Vertex>(vertexId, position);
    vertices.push_back(newVertex);

    return newVertex;
}

std::shared_ptr<Vertex> BaseSTL::addVertex(double x, double y, double z) 
{
    int vertexId = vertices.size();
    std::shared_ptr<Vertex> newVertex = std::make_shared<Vertex>(vertexId, x, y, z);
    vertices.push_back(newVertex);

    return newVertex;
}

std::shared_ptr<Face> BaseSTL::addFace(unsigned int v1, unsigned int v2, unsigned int v3) {
    if (vertices.size() <= v1 ||
        vertices.size() <= v2 ||
        vertices.size() <= v3) {
        throw std::out_of_range("Tried to instantiate face with non-existent vertex.");
    }
    int faceId = faces.size();
    std::array<std::shared_ptr<Vertex>,3> v = {vertices[v1], vertices[v2], vertices[v3]};
    std::shared_ptr<Face> newFace = std::make_shared<Face>(faceId, v);
    faces.push_back(newFace);

    return newFace;
}

Face& BaseSTL::addFace(Face& addFace) {
    // Reset the id of the face, to conform with index in faces vector
    int faceId = faces.size();
    addFace.id = faceId;
    faces.push_back(std::make_shared<Face>(addFace));

    return addFace;
}

std::shared_ptr<Rectangle> BaseSTL::addRectangle(std::array<Coordinate,4> c) 
{
    std::vector<std::shared_ptr<Vertex>> corners;
    for (auto p : c) {
        unsigned int id;
        auto result = findDuplicate(p);
        if (std::get<0>(result)) {
            id = std::get<1>(result);
            corners.push_back(vertices[id]);
        } else {
            id = vertices.size();
            vertices.push_back(std::make_shared<Vertex>(id, p));
            corners.push_back(vertices[id]);
        }
    }
    std::shared_ptr<Rectangle> newRectangle = std::make_shared<Rectangle>(primitives.size(), corners);
    std::shared_ptr<Primitive> newPrimitive = newRectangle;
    primitives.push_back(newPrimitive);
    return newRectangle;
}

std::shared_ptr<Trapezoid> BaseSTL::addTrapezoid(std::array<Coordinate,4> c)
{
    std::vector<std::shared_ptr<Vertex>> corners;
    for (auto p : c) {
        unsigned int id;
        auto result = findDuplicate(p);
        if (std::get<0>(result)) {
            id = std::get<1>(result);
            corners.push_back(vertices[id]);
        } else {
            id = vertices.size();
            vertices.push_back(std::make_shared<Vertex>(id, p));
            corners.push_back(vertices[id]);
        }
    }
    std::shared_ptr<Trapezoid> newTrapezoid = std::make_shared<Trapezoid>(primitives.size(), corners);
    std::shared_ptr<Primitive> newPrimitive = newTrapezoid;
    primitives.push_back(newPrimitive);
    return newTrapezoid;
}

std::shared_ptr<Pizza> BaseSTL::addPizza(std::array<Coordinate,3> c, std::array<double,3> normal, int radResolution)
{
    std::vector<std::shared_ptr<Vertex>> v;
    for (auto n : {0,1,2}) {
        unsigned int id;
        auto result = findDuplicate(c[n]);
        if (std::get<0>(result)) {
            id = std::get<1>(result);
            v.push_back(vertices[id]);
        } else {
            id = vertices.size();
            vertices.push_back(std::make_shared<Vertex>(id, c[n]));
            v.push_back(vertices[id]);
        }
    }

    // Add the remaining vertices on the cornicione
    int i = 0;
    while (i < radResolution-1) {
        v.push_back(std::make_shared<Vertex>(vertices.size()));
        ++i;
    }
    
    std::shared_ptr<Pizza> newPizza = std::make_shared<Pizza>(primitives.size(), v);
    std::shared_ptr<Primitive> newPrimitive = newPizza;
    primitives.push_back(newPrimitive);
    return newPizza;
}

std::shared_ptr<Pizza> BaseSTL::addPizza(const std::shared_ptr<Pizza>& mirror, double d)
{
    std::vector<std::shared_ptr<Vertex>> v;   

    // Add all necessary vertices
    int i = 0;
    while (i < mirror->getResolution()+1) {
        v.push_back(std::make_shared<Vertex>(vertices.size()));
        ++i;
    }
    
    std::shared_ptr<Pizza> newPizza = std::make_shared<Pizza>(primitives.size(), v, mirror, d);
    std::shared_ptr<Primitive> newPrimitive = newPizza;
    primitives.push_back(newPrimitive);
    return newPizza;
}

std::shared_ptr<Circle> BaseSTL::addCircle(Coordinate c, std::array<double,3> normal, double radius, int radResolution)
{
    // Normalize normal vector 
    double l = Coordinate(normal).length();
    Coordinate n(normal[0]/l, normal[1]/l, normal[2]/l);

    // Find a vector with length = radius that is orthogonal to n
    double r2 = radius*radius;
    double nznx2 = (n.z*n.z)/(n.x*n.x);
    double nynx2 = (n.y*n.y)/(n.x*n.x);
    double nynznx2 = (2*n.y*n.z)/(n.x*n.x);

    double uy = sqrt(r2 * (1 + nznx2)) / (2 * (1 + nynx2 + nznx2));
    double uz = (sqrt((r2/2) * (1 + nznx2)) - uy * nynznx2) / (2 + 2*nznx2);
    double ux = sqrt(r2 -uy*uy - uz*uz);

    Coordinate u(ux, uy, uz);

    std::vector<std::shared_ptr<Vertex>> v;
    for (Coordinate p : {c, c+u}) {
        unsigned int id;
        auto result = findDuplicate(p);
        if (std::get<0>(result)) {
            id = std::get<1>(result);
            v.push_back(vertices[id]);
        } else {
            id = vertices.size();
            vertices.push_back(std::make_shared<Vertex>(id, p));
            v.push_back(vertices[id]);
        }
    }

    // Add the remaining vertices on the cornicione
    int i = 0;
    while (i < radResolution-1) {
        v.push_back(std::make_shared<Vertex>(vertices.size()));
        ++i;
    }

    std::shared_ptr<Circle> newCircle = std::make_shared<Circle>(primitives.size(), v);
    std::shared_ptr<Primitive> newPrimitive = newCircle;
    primitives.push_back(newPrimitive);
    return newCircle;
    
}

std::shared_ptr<Circle> BaseSTL::addCircle(const std::shared_ptr<Circle> mirror, double d)
{
    /** TODO:
     * 
     * This function is not a priority.
     */
}

std::shared_ptr<Cuboid> BaseSTL::addCuboid(std::array<Coordinate,8> c) 
{
    std::vector<std::shared_ptr<Vertex>> corners;
    for (auto p : c) {
        unsigned int id;
        auto result = findDuplicate(p);
        if (std::get<0>(result)) {
            id = std::get<1>(result);
            corners.push_back(vertices[id]);
        } else {
            id = vertices.size();
            vertices.push_back(std::make_shared<Vertex>(id, p));
            corners.push_back(vertices[id]);
        }
    }
    std::shared_ptr<Cuboid> newCuboid = std::make_shared<Cuboid>(primitives.size(), corners);
    std::shared_ptr<Primitive> newPrimitive = newCuboid;
    primitives.push_back(newPrimitive);
    return newCuboid;
}

std::shared_ptr<Channel> BaseSTL::addChannel(std::array<Coordinate,8> c, unsigned int hollowDir) 
{
    std::vector<std::shared_ptr<Vertex>> corners;
    for (auto p : c) {
        unsigned int id;
        auto result = findDuplicate(p);
        if (std::get<0>(result)) {
            id = std::get<1>(result);
            corners.push_back(vertices[id]);
        } else {
            id = vertices.size();
            vertices.push_back(std::make_shared<Vertex>(id, p));
            corners.push_back(vertices[id]);
        }
    }
    std::shared_ptr<Channel> newChannel = std::make_shared<Channel>(primitives.size(), corners, hollowDir);
    std::shared_ptr<Primitive> newPrimitive = newChannel;
    primitives.push_back(newPrimitive);
    return newChannel;
}

std::shared_ptr<TrapezoidalPrism> BaseSTL::addTrapezoidalPrism(std::array<Coordinate,8> c) 
{
    std::vector<std::shared_ptr<Vertex>> corners;
    for (auto p : c) {
        unsigned int id;
        auto result = findDuplicate(p);
        if (std::get<0>(result)) {
            id = std::get<1>(result);
            corners.push_back(vertices[id]);
        } else {
            id = vertices.size();
            vertices.push_back(std::make_shared<Vertex>(id, p));
            corners.push_back(vertices[id]);
        }
    }
    std::shared_ptr<TrapezoidalPrism> newPrism = std::make_shared<TrapezoidalPrism>(primitives.size(), corners);
    std::shared_ptr<Primitive> newPrimitive = newPrism;
    primitives.push_back(newPrimitive);
    return newPrism;
}

std::shared_ptr<TrapezoidalChannel> BaseSTL::addTrapezoidalChannel(std::array<Coordinate,8> c, unsigned int hollowDir) 
{
    std::vector<std::shared_ptr<Vertex>> corners;
    for (auto p : c) {
        unsigned int id;
        auto result = findDuplicate(p);
        if (std::get<0>(result)) {
            id = std::get<1>(result);
            corners.push_back(vertices[id]);
        } else {
            id = vertices.size();
            vertices.push_back(std::make_shared<Vertex>(id, p));
            corners.push_back(vertices[id]);
        }
    }
    std::shared_ptr<TrapezoidalChannel> newChannel = std::make_shared<TrapezoidalChannel>(primitives.size(), corners, hollowDir);
    std::shared_ptr<Primitive> newPrimitive = newChannel;
    primitives.push_back(newPrimitive);
    return newChannel;
}

void BaseSTL::render() {
    for (auto primitive : primitives) {
        primitive->render();
        for (auto face : primitive->getFaces()) {
            addFace(face);
        }
    }
    primitives.clear();
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

std::array<double,3> BaseSTL::getMin() {
    /** TODO:
     * 
     * Return the minimal x, y, and z coordinates of all vertices
     */
}

std::array<double,3> BaseSTL::getMax() {
    /** TODO:
     * 
     * Return the maximal x, y, and z coordinates of all vertices
     */
}

std::tuple<std::array<double,3>, std::array<double,3>> getBoundingBox() {
    /** TODO:
     * 
     * Return the cartesian dimensions that form the bounding box of the STL object.
     */
}

void BaseSTL::writeSTL(std::string file) {
    /** TODO:
     * 
     * Loop through all the faces and generate the STL file
     */
}

}   // namespace stl