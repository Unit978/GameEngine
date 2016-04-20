// The source has been obtained from https://github.com/BennyQBD/ModernOpenGLTutorial.
// The code has been modified to work with Cor's math classes

#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <vector>
#include <string>

#include "../math/Vector3.h"
#include "../math/Vector2.h"

struct OBJIndex
{
    unsigned int vertexIndex;
    unsigned int uvIndex;
    unsigned int normalIndex;

    bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
};

class IndexedModel
{
public:
    std::vector<Vector3> positions;
    std::vector<Vector2> texCoords;
    std::vector<Vector3> normals;
    std::vector<unsigned int> indices;

    void CalcNormals();
};

class OBJModel
{
public:
    std::vector<OBJIndex> OBJIndices;
    std::vector<Vector3> vertices;
    std::vector<Vector2> uvs;
    std::vector<Vector3> normals;
    bool hasUVs;
    bool hasNormals;

    OBJModel(const std::string& fileName);

    IndexedModel ToIndexedModel();

private:
    unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result);
    void CreateOBJFace(const std::string& line);

    Vector2 ParseOBJVec2(const std::string& line);
    Vector3 ParseOBJVec3(const std::string& line);
    OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
};

#endif // OBJMODEL_H
