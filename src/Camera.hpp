#pragma once
#include <GL/gl3w.h>
#include <glm/glm.hpp>
#include "Display.hpp"


class Camera {
public:
	Camera(const Display& screen);
	~Camera();

	glm::mat4 getMatrix() const {return transformation_matrix;}
	const float* getMatrixStart() const {return &transformation_matrix[0][0];}
	GLuint getShader() const { return shaderID; }
private:
	glm::mat4 transformation_matrix;
	glm::vec2 position;
	GLuint shaderID;
};