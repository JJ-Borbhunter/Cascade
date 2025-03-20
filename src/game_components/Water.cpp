#include "Water.hpp"
#include "texture_load.hpp"

GLuint Water::WaterTexture = -1;

Water::Water(std::array<float, 8> positions, bool flow):
	stream{
		(WaterTexture == -1) ? (WaterTexture = texture_load::OGL_texture("Resources/texture/water.png")) : WaterTexture,
		100,
		100,
		{0, 1, 2, 1},
		{
			{0.0, 1.0,  0.0, 0.0,  1.0/3.0, 0.0,  1.0, 1.0/3.0},
			{0.0, 1.0,  0.0, 0.0,  2.0/3.0, 0.0,  1.0, 2.0/3.0},
			{0.0, 1.0,  0.0, 0.0,  3.0/3.0, 0.0,  1.0, 3.0/3.0}
		},
		10 //slowness
	}
{
	_flowing = flow;
	stream.overwritePositions(positions);
}