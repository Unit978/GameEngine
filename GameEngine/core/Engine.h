
/*
    Binds all systems together, handles the main loop, state machine,
    initializes SDL and OpenGL.
*/

#ifndef ENGINE_H
#define ENGINE_H

#include "Display.h"
#include <SDL2/SDL_opengl.h>

#include "../components/ComponentManager.h"

class Engine{

public:
    Engine();
    ~Engine();

    bool initialize();
    void run();

    static Display* getDisplay();
    static float getDeltaTime();

    static ComponentManager componentManager;

private:

    // Game window
    static Display* display;

    // The context for SDL/OpenGL
    SDL_GLContext glcontext;

    float static deltaTime;

    //static ComponentManager* componentManager;

    bool initializeGLEW();
    bool initializeSDL();
    bool initializeOpenGL();
    bool createDisplay();
    void cleanUp();
};

#endif // ENGINE_H
