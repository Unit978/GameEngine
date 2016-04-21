
/*
    Binds all systems together, handles the main loop, state machine,
    initializes SDL and OpenGL.
*/

#ifndef ENGINE_H
#define ENGINE_H

#include <unordered_map>
#include <SDL2/SDL_opengl.h>

#include "Display.h"
#include "../components/ComponentManager.h"

using std::unordered_map;

class Engine{

public:
    Engine();
    ~Engine();

    bool initialize();
    void run();

    static Display* getDisplay();
    static float getDeltaTime();

    static ComponentManager componentManager;

    // Sets the string representation of the OpenGL enum type.
    static void getGlTypeName(const GLenum type, string& name);

private:

    // Game window
    static Display* display;

    // The context for SDL/OpenGL
    SDL_GLContext glcontext;

    float static deltaTime;

    static unordered_map<GLenum, string> glTypeNames;
    static void setGlTypeNames();

    bool initializeGLEW();
    bool initializeSDL();
    bool initializeOpenGL();
    bool initializeSubSystems();
    bool createDisplay();
    void cleanUp();
};

#endif // ENGINE_H
