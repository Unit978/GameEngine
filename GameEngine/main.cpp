
#include "components/Shader.h"
#include "core/Engine.h"

#include "components/ComponentManager.h"
#include "components/Component.h"
#include "components/Transform.h"
#include "entity/Entity.h"

#include <iostream>

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

    //Shader shader("shaders/basic_shader");

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
