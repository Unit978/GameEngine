#include "GL/glew.h"
#include "Display.h"
#include <iostream>
#include <SDL2/SDL_opengl.h>
#include "../util/GraphicsUtil.h"

using std::cout;
using std::endl;
using std::cerr;

Display::Display() : window(nullptr), glcontext(nullptr), fullscreenFlag(false) {
    cout << "Creating display...\n";
    createWindow();

    if (SDL_GetDesktopDisplayMode(0, &desktopDisplay) != 0 )
        cerr << "Error: Failed to obtain data of the desktop display. " << SDL_GetError() << endl;
}

Display::~Display(){
    cout << "Destroying window...\n";
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
}

void Display::update() const{
    SDL_GL_SwapWindow(window);
}

void Display::clear(unsigned r, unsigned g, unsigned b, unsigned a) const{

    if (r <= 255 && g <= 255 && b <= 255 && a <= 255){
        glClearColor(r/255.0f, g/255.0f, b/255.0f, a/255.0f);

        // clear the color buffer bit and the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    else
        cerr << "Invalid color specified to clear the screen.\n";
}

void Display::centerMouse() const{
    int w, h;
    getSize(w, h);
    SDL_WarpMouseInWindow(window, w/2, h/2);
}

void Display::toggleFullscreen(){

    // We are at full screen, we want to go windowed.
    if (fullscreenFlag){
        SDL_SetWindowDisplayMode(window, NULL);
        SDL_SetWindowFullscreen(window, SDL_FALSE);
    }

    // We are windowed and want to go to full screen.
    else{
        SDL_SetWindowDisplayMode(window, &desktopDisplay);
        SDL_SetWindowFullscreen(window, SDL_TRUE);
    }

    // toggle
    fullscreenFlag = !fullscreenFlag;
}

bool Display::isValid() const{
    if (!window || !glcontext)
        return false;
    return true;
}

bool Display::createWindow(int width, int height, const string title, bool fullscreened){

    // Get the centered flag for window positioning.
    int centered = SDL_WINDOWPOS_CENTERED;

    // Get the shown flag in order to show the window when it is created.
    Uint32 shown = SDL_WINDOW_SHOWN;

    //full screen flag
    Uint32 full = 0;
    if (fullscreened)
        full = SDL_WINDOW_FULLSCREEN;

    // OpenGL context flag
    Uint32 opengl = SDL_WINDOW_OPENGL;

    // combine all flags
    Uint32 flags = shown | full | opengl;

    //create the window
    window = SDL_CreateWindow(title.c_str(), centered, centered, width, height, flags);

    // Failed to create a window context
    if (!window){
        cerr << "Error. Failed to create a window. ";
        cerr << SDL_GetError() << endl;
        return false;
    }

    // Check if the context was created successfully
    if (!createContext())
        return false;

    // Enable VSync to synchronize the frame rate of the game
    // with the monitor refresh rate for better stability.
    if(SDL_GL_SetSwapInterval(1) < 0){
        cerr << "Error. Failed to enable VSync. ";
        cerr << SDL_GetError() << endl;
        return false;
    }

    // Successfully created a window
    return true;
}

bool Display::createContext(){

    // Setup the OpenGL context
    // Obtain the version of OpenGL to use from the script.
    int major, minor;
    if(!getOpenGLVersion(major, minor))
        return false;

    // Set the OpenGL version to use.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);

    // Make OpenGL as core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create the SDL/GL context for the display so OpenGL has some control over it
    glcontext = SDL_GL_CreateContext(window);

    // The context failed with the specified OpenGL version
    if(!glcontext){

        cout << "Initial context failed with OpenGL " << major << '.' << minor << endl;
        cout << "Attempting to recreate context with OpenGL 2.1\n";

        // If the context failed, try OpenGL 2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        // Test out the new context
        if(!SDL_GL_CreateContext(window)){
            cerr << "Error. Failed to create an OpenGL context. ";
            cerr << SDL_GetError() << endl;
            return false;
        }
    }

    // Context was successfully created.
    return true;
}

void Display::setSize(int width, int height){
    SDL_SetWindowSize(window, width, height);

    // Make the viewport fit to the new width and height of the screen.
    glViewport(0, 0, width, height);
}

void Display::getSize(int& width, int& height) const{
    SDL_GetWindowSize(window, &width, &height);
}

const SDL_PixelFormat* Display::getFormat() const{
    return SDL_GetWindowSurface(window)->format;
}

SDL_Window* Display::getSDLWindow() const{
    return window;
}
