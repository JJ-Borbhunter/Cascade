#pragma once
#include "Display.hpp"
#include <glm/glm.hpp>

void change_single_index_to_screen_coordinates(glm::vec2& c);

glm::ivec2 getIndexFromScreenPos(float x, float y);
glm::ivec2 getIndexFromScreenPos(glm::vec2 v);

glm::vec2 getScreenPosFromIndex(int u, int v);
glm::vec2 getScreenPosFromIndex(glm::ivec2 c);