#include "FloorGrid75.hpp"
#include "Display.hpp"
#include "Camera.hpp"
#include "GridUtilities.hpp"
#include <cmath>
#include <iostream>
#include <queue>
#include <fstream>

// #define GENERATE_CLICK_RECORD
// #define GENERATE_EXACT_SCREEN_COORDS
#undef GENERATE_CLICK_RECORD
#undef GENERATE_EXACT_SCREEN_COORDS

glm::ivec2 FloorGrid75::_getIndexFromMousPos(int x, int y, const Display& d) {

	const float grid_size = 75.0f * d.get_height()/900.0f;
	y = -y + d.get_height() / 2.0f;
	x = x - d.get_width() / 2.0f;
	float a = x * 0.5773502691896258f - y;
	float b = x * 0.5773502691896258f + y;
	a /= grid_size;
	b /= grid_size;
	return glm::ivec2(floor(a) + 10, floor(b) + 10);
	//+10 is for the oddities of 0,0 being like offscreen and not in the center
}




bool FloorGrid75::resolve_click(float x, float y, const Display& d, glm::ivec2 start, std::vector<glm::vec2>& path){
	glm::ivec2 coords = _getIndexFromMousPos(x, y, d);
#ifdef GENERATE_CLICK_RECORD
	std::ofstream f("last record.txt", std::ios::app);
	f << "\tfloor.setWalkable(" << coords.x << ", " << coords.y << ");\n";
	f.close();
#endif
#ifdef GENERATE_EXACT_SCREEN_COORDS
    static int n = 1;
    std::cout << x - 720 << ", " << -y + 450;
    if (n % 4 == 0) { 
        std::cout << std::endl; 
    } else {
        std::cout << ", ";
    }
    n++;
#endif

    if (coords.x == 19) {
        coords.x = 18;
    }
    if (coords.y == 19) {
        coords.y = 18;
    }

	if ( coords.x < 0 || coords.y < 0 || coords.x >= 19 || coords.y >= 19) {
		return false;
	}
    if(coords == start){
        return false;
    }
	if (grid[coords.x][coords.y].isActive()) {
		bool isPath = _find_path_indices(start, coords, path);
		if (isPath) {
			_change_path_indices_to_screen_coordinates(path, d);
		}
		return isPath;
	}
	return false;
}


void FloorGrid75::setWalkable(int x, int y) { 
    if ( x >= 0 || y >= 0 || x < 19 || y < 19) {
        grid[x][y].setActive(); 
    }
}
void FloorGrid75::setUnwalkable(int x, int y) { 
    if ( x >= 0 || y >= 0 || x < 19 || y < 19) {
        grid[x][y].setInactive(); 
    }
}

void FloorGrid75::toggleWalkable(int x, int y) {
    if ( x >= 0 || y >= 0 || x < 19 || y < 19) {
        if(grid[x][y].isActive()){
            grid[x][y].setInactive();
        } else {
            grid[x][y].setActive();
        }
    }
}


bool FloorGrid75::_find_path_indices(glm::ivec2 start, glm::ivec2 end, std::vector<glm::vec2>& path) {
    bool visited[19][19] = {false};
    std::queue<glm::ivec2> q;
    glm::ivec2 parent[19][19];  // Store parent nodes for path reconstruction

    visited[start.x][start.y] = true;
    q.push(start);
    parent[start.x][start.y] = {-1, -1};  // Mark as root

    // Cardinal (Up, Down, Left, Right) movements
    glm::ivec2 directions[4] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}
    };

    while (!q.empty()) {
        glm::ivec2 current = q.front();
        q.pop();

        if (current == end) {
            // Construct path by backtracking
            glm::ivec2 at = end;
            path.clear();
            while (at != start) {
                path.push_back(glm::vec2(at.x, at.y));
                at = parent[at.x][at.y];
            }
            std::reverse(path.begin(), path.end());
            return true;
        }

        // Explore adjacent nodes
        for (const auto& dir : directions) {
            glm::ivec2 next = current + dir;
            if (next.x >= 0 && next.x < 19 && next.y >= 0 && next.y < 19) {  // Bounds check
                if (grid[next.x][next.y].isActive() && !visited[next.x][next.y]) {
                    q.push(next);
                    visited[next.x][next.y] = true;
                    parent[next.x][next.y] = current;
                }
            }
        }

        // Explore special connections
        for (const auto& special : grid[current.x][current.y].special) {
            if (special.x >= 0 && special.x < 19 && special.y >= 0 && special.y < 19) {  // Bounds check
                if (!visited[special.x][special.y]) {
                    q.push(special);
                    visited[special.x][special.y] = true;
                    parent[special.x][special.y] = current;
                }
            }
        }
    }

    return false;  // No path found
}


void FloorGrid75::_change_path_indices_to_screen_coordinates(std::vector<glm::vec2>& path, const Display& d){
	for (int i = 0; i < path.size(); ++i) {
		change_single_index_to_screen_coordinates(path[i]);
	}
}


void FloorGrid75::_change_single_index_to_screen_coordinates(glm::vec2& c, const Display& d){
	const float grid_size = 75.0f * d.get_height()/900.0f;

	float a = (c.x + -10) * grid_size;
	float b = (c.y + -10) * grid_size;
	c.y = -0.5f * a + 0.5f * b;
	c.x = 0.8660254038 * a + 0.8660254038f * b;
	c.x += (grid_size) * 0.8660254038;
}
