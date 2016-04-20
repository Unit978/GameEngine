
#include "GL/glew.h"
#include <SDL2/SDL_image.h>
#include "Texture.h"
#include "../util/GraphicsUtil.h"

#include <cassert>

#include <iostream>

Texture::Texture(const string& filepath){

   SDL_Surface* image = loadImageSurface(filepath);

    if (image){

        Uint32* image_pixel_data = getSurfacePixelData(image);

        GLenum format;

        // image is in RGBA format
        if (image->format->Rmask == 0x000000ff)
            format = GL_RGBA;

        // has BGRA format
        else format = GL_BGRA;

        int imgW = image->w;
        int imgH = image->h;

        // Have OpenGL generate 1 texture for us.
        glGenTextures(1, &textureID);

        // Bind this texture as a 2D image
        glBindTexture(GL_TEXTURE_2D, textureID);

        //glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA, img_w, img_h);
        //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, img_w, img_h, format, GL_UNSIGNED_BYTE, image_pixel_data);

        // Wrap pixel data on the horizontal and vertical components of the image.
        // If our image has a width of 100 and we want data about pixel 101 (on the horizontal axis),
        // Then that pixel will be interpreted as pixel #1 on the horizontal axis.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Handle linear interpolation if the texture is larger or smaller than the original image resolution.
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // 2nd param (GLint level): If you have multiple resolutions of the same image, some larger and some smaller,
        // this param. can be used to have larger res. images be rendered if they are close to us, and the smaller res.
        // images be used when we are farther from them. "0" is the default level.
        // 3rd param: Is the output format to the screen.
        // The last two parameters are the data type of the pixel data, and the pixel data itself.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgW, imgH, 0, format, GL_UNSIGNED_BYTE, image_pixel_data);

        // We don't need the SDL surface anymore since we now have it in the texture
        SDL_FreeSurface(image);
    }
}

Texture::~Texture(){
    glDeleteTextures(1, &textureID);
}

void Texture::bind(unsigned unit) const{

    // OpenGL can only have up to 32 different textures.
    assert(unit >= 0 && unit <= 31);

    // Activate the default texture, there can be multiple ones.
    glActiveTexture(GL_TEXTURE0 + unit);

    glBindTexture(GL_TEXTURE_2D, textureID);
}
