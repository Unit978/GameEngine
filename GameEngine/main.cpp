
#include "components/Shader.h"
#include "core/Engine.h"

#include "components/ComponentManager.h"
#include "components/Component.h"
#include "components/Transform.h"
#include "entity/Entity.h"

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* args[]){

    Engine engine;
    if (!engine.initialize()){
        cerr << "Failed to initialize engine!\n";
        return -1;
    }

    Entity e;
    e.addComponent<Transform>();
    e.addComponent<Transform>();
    e.addComponent<Component>();

    Component* c = e.getComponent<Component>();
    Transform* t = e.getComponent<Transform>();
    Transform* t2 = e.getComponent<Transform>();

    cout << c->getName() << endl;
    cout << t->getName() << endl;
    cout << t2->getName() << endl;

    Shader shader("shaders/basic_lighting_shader");

    Matrix4 mvp;
    // Vector3 pos;
    shader.setUniformValue("transform", mvp);

/*
    GLint maxAttribNameLen = 0;
    glGetProgramiv(shader.getProgramID(), GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxAttribNameLen);
    vector<GLchar> attribNameData(maxAttribNameLen);

    GLint attribCount = 0;
    glGetProgramiv(shader.getProgramID(), GL_ACTIVE_ATTRIBUTES, &attribCount);

    cout << "attribute count: " << attribCount << endl;

    for (GLint attrib = 0; attrib < attribCount; attrib++){
        GLint arraySize = 0;
        GLenum type = 0;
        GLsizei actualLen = 0;
        glGetActiveAttrib(shader.getProgramID(), attrib, attribNameData.size(), &actualLen, &arraySize, &type, &attribNameData[0]);

        string attribName((char*)&attribNameData[0], actualLen);
        cout << "Attribute name: " << attribName << " type: " << type << endl;
    }

    cout << "mat4: " << GL_FLOAT_MAT4 << endl;
*/
    engine.run();

    /*
    const uint64_t eidMask =  0xFFFFFFFF00000000;
    const uint64_t compMask = 0x00000000FFFFFFFF;

    unsigned eidA = 11;
    unsigned compType = 1;
    uint64_t mask = 0;

    cout << "Mask zeroed: " << mask << endl;

    mask = (mask | eidA) << 32;
    mask = (mask | compType);

    cout << "Mask masked: " << mask << endl;
    cout << "eid: " <<    (int) ( (mask & eidMask)  >> 32) << endl;
    cout << "comp type: " << (int) (mask & compMask) << endl << endl;
    */

    /*
    Engine engine;

    if (!engine.initialize())
        return 1;

    engine.run();
    */

    return 0;
}
