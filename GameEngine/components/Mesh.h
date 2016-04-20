// OpenGL requires a mesh of vertices in order to render objects.

#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "../math/Vector3.h"
#include "../math/Vector2.h"
#include <vector>
#include <string>

#include "../util/OBJModel.h"

using std::vector;
using std::string;

class Mesh{

public:

    // Vertex class for the mesh geometry
    class Vertex{

    public:
        // The position of the vertex in 3D space
        Vector3 position;

        // UV texture coordinate. The position of the texture that will be mapped to the vertex.
        Vector2 uv;

        // The normal vector. Vector used to determine light reflection from mesh surface.
        Vector3 normal;

        Vertex(const Vector3& position, const Vector2& uv, const Vector3& normal = Vector3(0, 0, 1)){
            this->position = position;
            this->uv = uv;
            this->normal = normal;
        }
    };

    Mesh(const vector<Vertex>& vertices, const vector<int>& indices);

    // File path of the model.
    Mesh(const string& filepath);
    ~Mesh();

    void render() const;

    // Flag to tell OpenGL to render the mesh using lines.
    bool wireframe;

    // Flag to tell OpenGL to apply face culling on the mesh.
    bool cullface;

    // If the mesh should represent a line
    bool line;

private:

    // Create the mesh from a list of vertices and indices
    void createMesh(const vector<Vertex>&, const vector<int>&);

    // Create the mesh from an indexed model
    void createMesh(const IndexedModel&);

    // Enumerations for the different types of buffers.
    // INDEX represents the draw order of a vertex.
    enum { POSITION, TEXTURE, NORMAL, INDEX, NUM_BUFFERS };

    // This will refer to mesh data on GPU
    GLuint vertexArrayObjectID;
    GLuint vertexArrayBuffers[NUM_BUFFERS];

    // specifies how much of the mesh we need to render
    unsigned renderCount;
};

#endif // MESH_H
