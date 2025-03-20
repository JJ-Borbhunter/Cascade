#include "SimpleLoopingAnimatedTextRect.hpp"
#include <cstddef>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <algorithm>

SimpleLoopingAnimatedTextRect::SimpleLoopingAnimatedTextRect(
		const char* pathname, 
		int width, 
		int height, 
		std::vector<uint8_t> sequence, 
		std::vector<std::array<float, 8>> tcoords,
		int animation_rate
) : TextRect(pathname, width, height, {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0})  {

	for (int i = 0; i < tcoords.size(); ++i) {
	    texcoords.push_back(std::array<float, 8>{}); // Create an empty std::array<float, 8>
	    std::copy(std::begin(tcoords[i]), std::end(tcoords[i]), texcoords.back().begin());
	}
	for (int i = 0; i < sequence.size(); ++i){
		animation_order.push_back(sequence[i]);
	}

	time = 0;
	previous_index = animation_order[0];

	glBindBuffer(GL_ARRAY_BUFFER, texcoordVBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), &tcoords[0], GL_STATIC_DRAW);

	rate = animation_rate;
	subtime = 0;
}
SimpleLoopingAnimatedTextRect::SimpleLoopingAnimatedTextRect(
		GLuint tID, 
		int width, 
		int height, 
		std::vector<uint8_t> sequence, 
		std::vector<std::array<float, 8>> tcoords,
		int animation_rate
) : TextRect(tID, width, height, {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0})  {

	for (int i = 0; i < tcoords.size(); ++i) {
	    texcoords.push_back(std::array<float, 8>{}); // Create an empty std::array<float, 8>
	    std::copy(std::begin(tcoords[i]), std::end(tcoords[i]), texcoords.back().begin());
	}
	for (int i = 0; i < sequence.size(); ++i){
		animation_order.push_back(sequence[i]);
	}

	time = 0;
	previous_index = animation_order[0];

	glBindVertexArray(vertexAttributeArray);
	glBindBuffer(GL_ARRAY_BUFFER, texcoordVBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), &tcoords[0], GL_STATIC_DRAW);
	glBindVertexArray(0);

	rate = animation_rate;
	subtime = 0;
}

void SimpleLoopingAnimatedTextRect::draw(const Camera& c) {

	glBindVertexArray(vertexAttributeArray);
	if (previous_index != animation_order[time % animation_order.size()]) {
		glBindBuffer(GL_ARRAY_BUFFER, texcoordVBO);
		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), &texcoords[animation_order[time % animation_order.size()]][0], GL_STATIC_DRAW);
	}
	previous_index = animation_order[time % animation_order.size()];
	glUseProgram(c.getShader());

	glBindTexture(GL_TEXTURE_2D, textureID);

	glm::mat4 mat;
    if(reflected){
    	mat = c.getMatrix() * 
    		glm::translate(glm::mat4(1.0f), glm::vec3(position, 0)) * 
    		glm::scale(glm::mat4(1.0f), glm::vec3(-1, 1, 1));
    } else {
    	mat = c.getMatrix() * 
    		glm::translate(glm::mat4(1.0f), glm::vec3(position, 0));
    }

    GLint MatrixID = glGetUniformLocation(c.getShader(), "transformations");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(mat));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    if ((subtime % rate) == 0) {
    	time++;
    }
    ++subtime;
    glBindVertexArray(0);
}


void SimpleLoopingAnimatedTextRect::reverse () {

	std::reverse(animation_order.begin(), animation_order.end());

}

SimpleLoopingAnimatedTextRect::~SimpleLoopingAnimatedTextRect(){

}