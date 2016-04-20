#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include <string>

using std::string;

class Texture
{
public:
    Texture(const string& filepath);
    ~Texture();

    void bind(unsigned=0) const;

private:
    GLuint textureID;
};

#endif // TEXTURE_H
