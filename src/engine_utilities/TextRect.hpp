#pragma once

#include <GL/gl3w.h>
#include <glm/glm.hpp>
#include "Camera.hpp"
#include "error.hpp"
#include <array>


class TextRect
{
public:
	TextRect(){ error_raise("Default constructor called for TextRect object.", ""); }; // { revisit }
	TextRect(const char* pathname, float size) : TextRect(pathname, size, size) {} ;
	TextRect(const char* pathname, float width, float height) : TextRect(pathname, width, height, {0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0}) {};
	TextRect(const char* pathname, float width, float height, std::array<float, 8> texcoords);
	TextRect(GLuint tID, float width, float height, std::array<float, 8> tcoords);
	TextRect(GLuint tID, float width, float height) : TextRect(tID, width, height, {0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0}) {} ;
	~TextRect();

	void setPos(float x, float y) {position = glm::vec2(x, y);}
	void setPos(glm::vec2 v) {position = v;}
	
	glm::vec2 getPos() const;
	void center(const Display& d);
	void centerOver(float x, float y);
	void reflect() { reflected = !reflected; }
	void setReflected() { reflected = true; }
	void setUnreflected() { reflected = false; }
	void overwriteTexcoords(std::array<float, 8> a){
		glBindVertexArray(vertexAttributeArray);
		glBindBuffer(GL_ARRAY_BUFFER, texcoordVBO);
		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), &a[0], GL_STATIC_DRAW);
		glBindVertexArray(0);
	}
	void overwritePositions(std::array<float, 8> a) {
		glBindVertexArray(vertexAttributeArray);
		glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), &a[0], GL_STATIC_DRAW);
		glBindVertexArray(0);
	}
	void changeSize(glm::vec2 size);
	virtual void draw(const Camera& cam);
protected:
	GLuint textureID;
	glm::vec2 position;
	glm::vec2 size;
	GLuint vertexAttributeArray;
	GLuint positionVBO;
	GLuint texcoordVBO;
	GLuint indexVBO;
	bool reflected;
	bool isinchargeofowntexture;
};