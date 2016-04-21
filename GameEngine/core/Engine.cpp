
// Sets up everything we need for OpenGL.
// GLEW allows to extend OpenGL functionality since some OS, like Windows, only
// provide limited functionality for OpenGL
/*
 * GLEW_STATIC is defined for static library.
 * GLEW_BUILD  is defined for building the DLL library.
 */

#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>

#include "Engine.h"
#include "../util/Timer.h"

using std::cout;
using std::endl;
using std::cerr;

// define statics
Display* Engine::display = nullptr;
float Engine::deltaTime = 0;

ComponentManager Engine::componentManager;
unordered_map<GLenum, string> Engine::glTypeNames;

Engine::Engine() : glcontext(nullptr){

}

Engine::~Engine(){
    cleanUp();
}

void Engine::run(){

    Timer timer;
    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        timer.start();

        // Handle input
        while( SDL_PollEvent( &event ) != 0 ){

            // Quit program
            if (event.type == SDL_QUIT)
                quit = true;

            else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_t)
                    Engine::getDisplay()->toggleFullscreen();

                // Terminate program via escape key
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    quit = true;
            }
        }

        Engine::getDisplay()->clear(0, 0, 0, 0);
        Engine::getDisplay()->update();

        // Set delta time
        Engine::deltaTime = timer.getElapsedSeconds();
    }
}

bool Engine::initialize(){

    // Order of function calling matters here. SDL must be initialized so we can create the
    // display and the context for it. The context must be created so GLEW can be initialized.
    bool success = initializeSDL() && createDisplay() && initializeOpenGL() && initializeSubSystems();

    if (!success)
        cerr << "The engine failed to initialize properly.\n";
    else
        cout << "The engine has been successfully initialized.\n";

    return success;
}

// ============================== PRIVATE FUNCTIONS ==============================

bool Engine::initializeGLEW(){

    cout << "Initializing GLEW...\n";

    // Initialize the GLEW library
    glewExperimental = GL_TRUE;
    GLenum glew_error = glewInit();

    if(glew_error != GLEW_OK){
        cerr << "Error. Failed to initialize GLEW. ";
        cerr << glewGetErrorString(glew_error) << endl;
        return false;
    }

    // Check to see if OpenGL 2.1 is supported
    // This will be a minimum requirement for the system.
    if(!GLEW_VERSION_2_1){
        cerr << "Error. OpenGL 2.1 not supported on this system!\n";
        return false;
    }
    // GLEW successfully initialized
    return true;
}

bool Engine::initializeOpenGL(){

    // GLEW failed
    if(!initializeGLEW())
        return false;

    cout << "Initializing OpenGL...\n";

    // Enable depth test for pixels.
    glEnable(GL_DEPTH_TEST);

    // Used to disregard triangular faces based on their orientation.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    return true;
}

bool Engine::initializeSDL(){

    cout << "Initializing SDL...\n";

    // Initialize everything from the SDL libraries
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cerr << "Error: Failed to initialize SDL!\n";
        return false;
    }

    // Set up the pixel and display attributes
    // Each color should have a minimum depth of 8 bits
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

    // Set aside memory for the depth buffer
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Initialize PNG and JPG image loading from SDL_image
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initStatusFlags = IMG_Init(flags);

    // Failed to initialize support for PNG and JPG loading.
    if ( (flags & initStatusFlags) != flags){
        cerr << "Error: SDL_image failed to initialize support for PNG and JPG loading." << IMG_GetError() << endl;
        return false;
    }

    return true;
}

bool Engine::initializeSubSystems(){
    setGlTypeNames();

    return true;
}

bool Engine::createDisplay(){

    // Create a default display
    Engine::display = new Display();

    // The display is invalid
    if(!display->isValid()){
        delete display;
        display = nullptr;
        return false;
    }
    return true;
}

void Engine::cleanUp(){
    cout << "Cleaning up and deallocating...\n";

    delete display;
    SDL_Quit();
}

Display* Engine::getDisplay(){
    return display;
}

float Engine::getDeltaTime(){
    return deltaTime;
}

void Engine::getGlTypeName(const GLenum type, string& name){
    const auto itr = glTypeNames.find(type);
    if (itr != glTypeNames.end()){
        name = itr->second;
    }

    else{
        cerr << "Error. Name does not exist for GLenum type = " << type << endl;
        name = "";
    }
}

void Engine::setGlTypeNames(){

    glTypeNames.insert(std::pair<GLuint, string>(GL_FLOAT_MAT3, "Matrix3"));
    glTypeNames.insert(std::pair<GLuint, string>(GL_FLOAT_MAT4, "Matrix4"));

    glTypeNames.insert(std::pair<GLuint, string>(GL_FLOAT_VEC2, "Vector2"));
    glTypeNames.insert(std::pair<GLuint, string>(GL_FLOAT_VEC3, "Vector3"));
    glTypeNames.insert(std::pair<GLuint, string>(GL_FLOAT_VEC4, "Vector4"));

    glTypeNames.insert(std::pair<GLuint, string>(GL_INT, "Int"));
    glTypeNames.insert(std::pair<GLuint, string>(GL_FLOAT, "Float"));
}
