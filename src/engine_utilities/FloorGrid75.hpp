#pragma once
#include "Display.hpp"
#include "Camera.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <array>
#include "TextRect.hpp"

class Node75 {
public:
	Node75() : active(false), special({}) {};
	Node75(bool a, std::vector<glm::ivec2> v) : active(a), special(v) {};

	void setActive() {active = true; }
	void setInactive() {active = false;}
	bool isActive() { return active; }

	~Node75() {};

	std::vector<glm::ivec2> special;
private:
	bool active;
};

class FloorGrid75{
public:
	FloorGrid75(){};
	~FloorGrid75(){};

	//Path will be erased and filled with a proper path should a path be found. 
	bool resolve_click(float x, float y, const Display& d, glm::ivec2 start, std::vector<glm::vec2>& path);
	void setWalkable(int x, int y);
	void setWalkable(glm::ivec2 p) { setWalkable(p.x, p.y); }
	void setUnwalkable(glm::ivec2 p) { setUnwalkable(p.x, p.y); }
	void setUnwalkable(int x, int y);
	void toggleWalkable(int x, int y);
	void toggleWalkable(glm::ivec2 p) { toggleWalkable(p.x, p.y); }

private:

	Node75 grid[19][19];
	float adjusted_y;
	glm::ivec2 _getIndexFromMousPos(int x, int y, const Display& d);
	bool _find_path_indices(glm::ivec2 start, glm::ivec2 end, std::vector<glm::vec2>& path);
	void _change_path_indices_to_screen_coordinates(std::vector<glm::vec2>& path, const Display& d);
	void _change_single_index_to_screen_coordinates(glm::vec2& c, const Display& d);
};


