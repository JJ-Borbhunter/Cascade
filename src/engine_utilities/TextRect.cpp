
#include <GL/gl3w.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


#include "TextRect.hpp"
#include "texture_load.hpp"
#include "Camera.hpp"
#include "error.hpp"
#include "Display.hpp"

const int INDEX_COUNT = 6;

TextRect::TextRect(const char* pathname, float width, float height, std::array<float, 8> tcoords){

	//Gotta have a single vertex attribute array;
    glGenVertexArrays(1, &vertexAttributeArray);
    glGenBuffers(1, &positionVBO); 
    glGenBuffers(1, &texcoordVBO);
    glGenBuffers(1, &indexVBO); 

    size = glm::vec2(width, height);
    position = glm::vec2(0,0);

    textureID = texture_load::OGL_texture(pathname);

    GLfloat vertices[8] = {
        // Positions
        -size.x / 2.0f, -size.y / 2.0f, 
        -size.x / 2.0f,  size.y / 2.0f,
         size.x / 2.0f,  size.y / 2.0f,
         size.x / 2.0f, -size.y / 2.0f
    };
    GLushort indices[INDEX_COUNT] = {
		0, 1, 2,
		0, 2, 3
	};

	glBindVertexArray(vertexAttributeArray);

	//set up position buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, texcoordVBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), &tcoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glBindVertexArray(0);

	reflected = false;
    isinchargeofowntexture = true;
}


TextRect::TextRect(GLuint tID, float width, float height, std::array<float, 8> tcoords){
	//Gotta have a single vertex attribute array;
    glGenVertexArrays(1, &vertexAttributeArray);
    glGenBuffers(1, &positionVBO); 
    glGenBuffers(1, &texcoordVBO);
    glGenBuffers(1, &indexVBO); 

    size = glm::vec2(width, height);
    position = glm::vec2(0,0);

   	if(tID != -1) {
	    textureID = tID;
	}

    GLfloat vertices[] = {
        // Positions
        -size.x / 2.0f, -size.y / 2.0f, 
        -size.x / 2.0f,  size.y / 2.0f,
         size.x / 2.0f,  size.y / 2.0f,
         size.x / 2.0f, -size.y / 2.0f
    };
    GLushort indices[INDEX_COUNT] = {
		0, 1, 2,
		0, 2, 3
	};

	glBindVertexArray(vertexAttributeArray);

	//set up position buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, texcoordVBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), &tcoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	reflected = false;
    isinchargeofowntexture = false;
	glBindVertexArray(0);
}

void TextRect::draw(const Camera& cam){

	glUseProgram(cam.getShader());

	glBindTexture(GL_TEXTURE_2D, textureID);

    glm::mat4 mat;
    if(reflected){
    	mat = cam.getMatrix() * 
    		glm::translate(glm::mat4(1.0f), glm::vec3(position, 0)) * 
    		glm::scale(glm::mat4(1.0f), glm::vec3(-1, 1, 1));
    } else {
    	mat = cam.getMatrix() * 
    		glm::translate(glm::mat4(1.0f), glm::vec3(position, 0));
    }

    GLint MatrixID = glGetUniformLocation(cam.getShader(), "transformations");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(mat));

    glBindVertexArray(vertexAttributeArray);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}



void TextRect::center(const Display& d){
	setPos(
		(d.get_width()/2.0f - size[0]/2.0f),
		(d.get_height()/2.0f - size[1]/2.0f)
	);
}

void TextRect::centerOver(float x, float y) {
	position = glm::vec2(
		x - size[0]/2.0f,
		y - size[1]/2.0f
	);
}


void TextRect::changeSize(glm::vec2 size){

    GLfloat vertices[] = {
        // Positions
        -size.x / 2.0f, -size.y / 2.0f, 
        -size.x / 2.0f,  size.y / 2.0f,
         size.x / 2.0f,  size.y / 2.0f,
         size.x / 2.0f, -size.y / 2.0f
    };
    glBindVertexArray(vertexAttributeArray);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(0);

}

TextRect::~TextRect(){
	glDeleteBuffers(1, &positionVBO);
	glDeleteBuffers(1, &texcoordVBO);
	glDeleteBuffers(1, &indexVBO);
	glDeleteVertexArrays(1, &vertexAttributeArray);
	if(isinchargeofowntexture) glDeleteTextures(1, &textureID);
}

