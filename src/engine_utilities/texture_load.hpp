#pragma once

#include "GL/gl3w.h"

namespace texture_load {


GLuint OGL_texture(const char* strFilepath);
void OGL_texture_data(const char* filename);

}