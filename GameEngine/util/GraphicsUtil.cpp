#include "GraphicsUtil.h"

#include <fstream>
#include <iostream>

#include <SDL2/SDL_image.h>
#include "../core/Engine.h"

using std::ifstream;
using std::cerr;
using std::endl;

bool getOpenGLVersion(int& major, int& minor){

    // Get OpenGL version from the setup file.
    string filepath = "setup_scripts/opengl_version.txt";
    ifstream versionFile(filepath.c_str());

    // Failed to open the specified file.
    if(!versionFile){
        cerr << "Error: Unable to open " << filepath << endl;
        return false;
    }
    versionFile >> major >> minor;
    versionFile.close();
    return true;
}

SDL_Surface* loadImageSurface(const string& filepath){

    // This surface will contain the image formatted to the display's format
    // for optimization reasons.
    SDL_Surface* formattedSurface = nullptr;

    SDL_Surface* unformattedSurface = IMG_Load(filepath.c_str());

    if(unformattedSurface){
        formattedSurface = SDL_ConvertSurface(unformattedSurface, Engine::getDisplay()->getFormat(), 0);

        // Failed to convert into a formatted surface
        if(!unformattedSurface)
            cerr << "Error: Failed to convert the image into the display's format. " << SDL_GetError() << endl;

        // Delete the old image surface
        else
            SDL_FreeSurface(unformattedSurface);
    }
    // Failed to load the image from the file
    else
        cerr << "Error: Failed to load the image from this path: " << filepath << ", " << IMG_GetError() << endl;

    return formattedSurface;
}

Uint32* getSurfacePixelData(const SDL_Surface* surface){
    if(surface)
        // Convert the pixel data to Uint32 and return it
        return static_cast<Uint32*>(surface->pixels);

    // failed to obtain the pixel data
    else return nullptr;
}



