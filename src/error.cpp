#include <iostream>
#include <GL/gl3w.h>

void error_raise(const char* message, const char* info){
	std::cout << message << info << std::endl;
}


char const* gl_error_string(GLenum const err){
  switch (err)
  {
    // opengl 2 errors (8)
    case GL_NO_ERROR:
      return "GL_NO_ERROR";

    case GL_INVALID_ENUM:
      return "GL_INVALID_ENUM";

    case GL_INVALID_VALUE:
      return "GL_INVALID_VALUE";

    case GL_INVALID_OPERATION:
      return "GL_INVALID_OPERATION";

    case GL_STACK_OVERFLOW:
      return "GL_STACK_OVERFLOW";

    case GL_STACK_UNDERFLOW:
      return "GL_STACK_UNDERFLOW";

    case GL_OUT_OF_MEMORY:
      return "GL_OUT_OF_MEMORY";

    // opengl 3 errors (1)
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return "GL_INVALID_FRAMEBUFFER_OPERATION";

    // gles 2, 3 and gl 4 error are handled by the switch above
    default:
      return "UNKNOWN ERROR";
  }
}


void enumerate_opengl_errors(void){
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
	    error_raise("### OpenGL error: \n", gl_error_string(err));
	}
}