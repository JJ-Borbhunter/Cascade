#include <GL/gl3w.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "shader_source.hpp"
#include "Display.hpp"
#include "Camera.hpp"
#include "error.hpp"

const float DESIRED_SCREEN_HEIGHT = 900;
const float DESIRED_SCREEN_WIDTH  = 1200;

void checkShaderCompile(GLuint shader) {
    int success;
    char infoLog[1028];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        error_raise("Shader Compilation Error: ", infoLog);
    }
}


GLuint shaders_init() {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VERTEX_SHADER_SOURCE, NULL);
    glCompileShader(vertexShader);
    checkShaderCompile(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FRAGMENT_SHADER_SOURCE, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompile(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}



Camera::Camera(const Display& screen){
	position = {screen.get_width()/2, screen.get_height()/2};

    if (static_cast<float>(screen.get_width())/screen.get_height() >= 4.0/3.0) {  
        float proper_width = DESIRED_SCREEN_HEIGHT * (static_cast<float>(screen.get_width())/screen.get_height());

    	transformation_matrix = glm::ortho(
    	    -proper_width/2.0f, //left
    	    proper_width/2.0f,  //right
    	    -DESIRED_SCREEN_HEIGHT/2.0f,                          //bottom
    	    DESIRED_SCREEN_HEIGHT/2.0f                            //top
    	);
    } else {
        float proper_height = DESIRED_SCREEN_WIDTH * (static_cast<float>(screen.get_height())/screen.get_width());

        transformation_matrix = glm::ortho(
            -DESIRED_SCREEN_WIDTH/2.0f, //left
            DESIRED_SCREEN_WIDTH/2.0f,  //right
            -proper_height/2.0f,                          //bottom
            proper_height/2.0f                            //top
        );
    }
    
	shaderID = shaders_init();
}

Camera::~Camera(){

}


