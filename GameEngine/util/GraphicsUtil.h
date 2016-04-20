#ifndef GRAPHICSUTIL_H
#define GRAPHICSUTIL_H

#include <string>
#include <SDL2/SDL.h>

using std::string;

// Gets the major/minor version of OpenGL to use from a file
bool getOpenGLVersion(int&, int&);

// Loads an image file and returns an SDL_Surface with that image data
SDL_Surface* loadImageSurface(const string& filepath);

// Get the pixel data as a Uint32 of the specified image after loading it
Uint32* getSurfacePixelData(const SDL_Surface*);

#endif // GRAPHICSUTIL_H
