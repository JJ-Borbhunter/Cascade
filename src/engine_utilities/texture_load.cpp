#include "texture_load.hpp"
#include "GL/gl3w.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "error.hpp"
#include <iostream>

GLuint texture_load::OGL_texture(const char* strFilepath) {
	// Create one OpenGL texture
    GLuint textureID;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL, loding it via stb_image
    texture_load::OGL_texture_data(strFilepath);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    return textureID;
}


void texture_load::OGL_texture_data(const char* filename){
    unsigned char* data;
    int width;
    int height;
    int nrcomponents;

    data = stbi_load(filename, &width, &height, &nrcomponents, 0);
    if(!data) {
        error_raise("Failed to load texture: ", filename);
    }

    if (nrcomponents == 3){
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, data);
    } else if (nrcomponents == 4) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, data);
    }


    stbi_image_free(data);
}