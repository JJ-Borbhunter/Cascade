#include "GridUtilities.hpp"
#include <glm/glm.hpp>


void change_single_index_to_screen_coordinates(glm::vec2& c){
	const float grid_size = 75.0f;// * d.get_height()/900.0f;

	float a = (c.x + -10) * grid_size;
	float b = (c.y + -10) * grid_size;
	c.y = -0.5f * a + 0.5f * b;
	c.x = 0.8660254038 * a + 0.8660254038f * b;
	c.x += (grid_size) * 0.8660254038;
}

glm::vec2 getScreenPosFromIndex(glm::ivec2 c){
	const float grid_size = 75.0f;// * d.get_height()/900.0f;
	glm::vec2 vec;

	float a = (float)(c.x + -10) * grid_size;
	float b = (float)(c.y + -10) * grid_size;
	vec.y = -0.5f * a + 0.5f * b;
	vec.x = 0.8660254038 * a + 0.8660254038f * b;
	vec.x += (grid_size) * 0.8660254038;
	return vec;
}

glm::vec2 getScreenPosFromIndex(int u, int v){
	const float grid_size = 75.0f;// * d.get_height()/900.0f;
	glm::vec2 vec;

	float a = (float)(u + -10) * grid_size;
	float b = (float)(v + -10) * grid_size;
	vec.y = -0.5f * a + 0.5f * b;
	vec.x = 0.8660254038 * a + 0.8660254038f * b;
	vec.x += (grid_size) * 0.8660254038;
	return vec;
}

glm::ivec2 getIndexFromScreenPos(float x, float y) {

	const float grid_size = 75.0f;
	float a = x * 0.5773502691896258f - y;
	float b = x * 0.5773502691896258f + y;
	a /= grid_size;
	b /= grid_size;
	return glm::ivec2(floor(a) + 10, floor(b) + 10);
	//+10 is for the oddities of 0,0 being like offscreen and not in the center
}

glm::ivec2 getIndexFromScreenPos(glm::vec2 v) {

	const float grid_size = 75.0f;
	float a = v.x * 0.5773502691896258f - v.y;
	float b = v.x * 0.5773502691896258f + v.y;
	a /= grid_size;
	b /= grid_size;
	//std::cout << floor(a) + 10 << " : " << floor(b) + 10 << std::endl;
	return glm::ivec2(floor(a) + 10, floor(b) + 10);
	//+10 is for the oddities of 0,0 being like offscreen and not in the center
}