#include "Mesh.h"

#include <iostream>

using std::cout;

Mesh::Mesh(const vector<Mesh::Vertex>& vertices, const vector<int>& indices){
    createMesh(vertices, indices);
    wireframe = false;
    cullface = true;
    line = false;
}

Mesh::Mesh(const string& filepath){
    IndexedModel model = OBJModel(filepath).ToIndexedModel();
    createMesh(model);
    wireframe = false;
    cullface = true;
}

Mesh::~Mesh() {
    cout << "Destroying mesh...\n";
    glDeleteVertexArrays(1, &vertexArrayObjectID);
}

void Mesh::createMesh(const vector<Mesh::Vertex>& vertices, const vector<int>& indices){

    unsigned numVertices = vertices.size();

    // draw based on the indices, not how many vertices there are.
    renderCount = indices.size();

    // render_count = num_vertices;

    vector<Vector3> vertexPositions;
    vector<Vector2> uvCoords;
    vertexPositions.reserve(numVertices);
    uvCoords.reserve(numVertices);

    // store all vertex position and tex_coord data in the vectors
    for(unsigned i = 0; i < numVertices; i++){
        vertexPositions.push_back(vertices[i].position);
        uvCoords.push_back(vertices[i].uv);
    }

    // Create a VAO for this mesh
    glGenVertexArrays(1, &vertexArrayObjectID);
    glBindVertexArray(vertexArrayObjectID);

    // Generate the buffers so we can operate on the VAO
    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

    // Tell OpenGL to interpret the POSITION buffer data as an array
    // and bind it.
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION]);

    // Calculate the size (in memory) of the vertices for our buffer.
    // We do this by taking the memory size of an individual vertex and
    // multiplying it by how many there are.
    unsigned size = numVertices * sizeof(vertexPositions.at(0));

    // Place vertex data in the buffer array.
    // 1st param: tell OpenGL to interpret the vertex data as an array.
    // 2nd param: the size (in memory) of the array buffer.
    // 3rd param: the starting point of the source vertex data.
    // 4th param: draw hint - tells OpenGL where to put the data in the GPU.
    // STATIC_DRAW means that the vertex data won't be modified (for optimization reasons).
    glBufferData(GL_ARRAY_BUFFER, size, &vertexPositions.at(0), GL_STATIC_DRAW);

    // Vertex attributes are just data of the vertex. For example, it can be
    //  the position or color of the vertex.
    // We must have these attributes in an array format (sequential in memory)
    //  so OpenGL can process the attributes as an array.
    // For example, all the position attributes are placed sequentially as an array
    //  for OpenGL then all the color attributes are organized in the same way.

    // This tells OpenGL that we are going to specify an attribute array for a
    // certain Vertex data, in this case, the position.
    // "0" is an ID for the attribute we want to specify
    glEnableVertexAttribArray(0);

    // Tell OpenGL to read the position attribute as an array.
    // 1st param: takes the ID of the attribute.
    // 2nd param: how many pieces of data for the attribute - for the position
    //  case, it has 3 (x, y, and z)
    // 3rd param: the data type for those pieces.
    // 4th param: normalize the data
    // 5th param: how much data to skip - 0 since we have position stored continuously in the positions vector
    // 6th param: the starting point of the attribute data, 0 since it is the first
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // For texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXTURE]);
    size = numVertices * sizeof(uvCoords.at(0));
    glBufferData(GL_ARRAY_BUFFER, size, &uvCoords.at(0), GL_STATIC_DRAW);

    // Attribute 1 is for the tex coords since it comes after position in the Vertex class
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Vertex draw order
    // GL Element array is an array that contains data that is part of data in another
    // buffer. In our case, the draw order is for the vertices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX]);
    size = indices.size() * sizeof(indices.at(0));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, &indices.at(0), GL_STATIC_DRAW);

    // Unbind the VAO
    glBindVertexArray(0);
}

void Mesh::createMesh(const IndexedModel& model){

    unsigned num_vertices = model.positions.size();

    renderCount = model.indices.size();

    // Create a VAO for this mesh
    glGenVertexArrays(1, &vertexArrayObjectID);
    glBindVertexArray(vertexArrayObjectID);
    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

    // For vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION]);
    unsigned size = num_vertices * sizeof(model.positions.at(0));
    glBufferData(GL_ARRAY_BUFFER, size, &model.positions.at(0), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // For texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXTURE]);
    size = num_vertices * sizeof(model.texCoords.at(0));
    glBufferData(GL_ARRAY_BUFFER, size, &model.texCoords.at(0), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // For normals
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL]);
    size = model.normals.size() * sizeof(model.normals.at(0));
    glBufferData(GL_ARRAY_BUFFER, size, &model.normals.at(0), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Vertex draw order
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX]);
    size = model.indices.size() * sizeof(model.indices.at(0));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, &model.indices.at(0), GL_STATIC_DRAW);

    // Unbind the VAO
    glBindVertexArray(0);
}

void Mesh::render() const{
    glBindVertexArray(vertexArrayObjectID);

    // 1st param: how to draw the array object of vertices
    // 2nd param: the starting vertex to render from - 0 means from the start of the array
    // 3rd param: how many vertices to render (how much of the mesh)
    //glDrawArrays(GL_TRIANGLES, 0, render_count);

    // draw based on the indices.
    // 3rd param is the data type of the indices
    // 4th param is the starting element - 0 for the beginning of the indices array
    // glDrawElements(GL_LINES, render_count, GL_UNSIGNED_INT, 0)

    // Apply face culling
    if (cullface)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    // Turn wireframe on or off
    if (wireframe){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // To use lines or triangles
    if (line)
        glDrawElements(GL_LINES, renderCount, GL_UNSIGNED_INT, 0);
    else
        glDrawElements(GL_TRIANGLES, renderCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
