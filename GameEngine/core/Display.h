
/*
    Luis Lopez

    A window to handle the setup for an SDL window to make it function with
    OpenGL rendering.

    This class will initialize
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>

using std::string;

class Display{

public:
    // Creates a centered window with the specified parameters.
    // Takes in: width, height, title, full-screen flag
    Display();
    ~Display();

    void update() const;

    // clear the screen with the specified RGBA values (0-255)
    void clear(unsigned=0, unsigned=0, unsigned=0, unsigned=0) const;
    void centerMouse() const;
    void toggleFullscreen();

    // This function tests if the display we created is valid for use
    bool isValid() const;

    // Set the size the display with the new width and height.
    void setSize(int, int);
    void getSize(int&, int&) const;
    const SDL_PixelFormat* getFormat() const;
    SDL_Window* getSDLWindow() const;

private:

    //The SDL window for rendering.
    SDL_Window* window;
    SDL_GLContext glcontext;

    SDL_DisplayMode desktopDisplay;

    bool fullscreenFlag;

    bool createWindow(int=1200, int=700, const string="Game Engine Window", bool=false);
    bool createContext();
};

#endif // DISPLAY_H


