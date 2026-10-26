#include "structure.hpp"
#include <GL/gl.h>
#include <vector>
#include <map>

#define SPEED_SWITCH_COLOR_TEXTURE 0.1

#ifndef MODEL
# define MODEL DRAGON
#endif

extern	float	vertices[216];
extern	bool	autoRot;
extern	bool	wareFrame;
extern	float	factor;
extern	bool	onTexture;
extern	bool	texWorld;
extern	float	deltaTime;	// Time between current frame and last frame
extern	float	lastFrame;
extern	Model	objet[6];

extern std::map<int, GLuint> texture; // 0 texure 1 mask
extern std::string  default_texture;
extern Model        pointer_object;
extern vec3         cursorColor;

extern Material emerald;
extern Material jade;
extern Material obsidian;
extern Material pearl;
extern Material ruby;
extern Material turquoise;
extern Material brass;
extern Material bronze;
extern Material chrome;
extern Material copper;
extern Material gold;
extern Material silver;
extern Material black_plastic;
extern Material cyan_plastic;
extern Material green_plastic;
extern Material red_plastic;
extern Material white_plastic;
extern Material yellow_plastic;
extern Material black_rubber;
extern Material cyan_rubber;
extern Material green_rubber;
extern Material red_rubber;
extern Material white_rubber;
extern Material yellow_rubber;
