#include "../include/header.hpp"
#include <GL/gl.h>

vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

Camera		cam(vec3(0.7f, 1.5f, 8.7f));

float		deltaTime = 0.0f;	// Time between current frame and last frame
float		lastFrame = 0.0f;

bool		autoRot = false;
bool		wareFrame = false;
bool 		firstMouse = true;

float 		factor = 1.0;
bool 		onTexture = false;
bool		exist_texture = true;
bool		texWorld = true;
vec3 		cursorColor = {1.f, 0.f, 0.f};
Light HighLight =
	{vec3 (1.2f, 1.0f, 2.0f),
	vec3 (1.0f, 1.0f, 1.0f),
	vec3 (1.0f, 1.0f, 1.0f),
	vec3 (1.0f, 1.0f, 1.0f)};

Light LowLight =
	{vec3 (1.2f, 1.0f, 2.0f),
	vec3 (0.15f, 0.15f, 0.15f),
	vec3 (0.8f, 0.8f, 0.8f),
	vec3 (0.35f, 0.35f, 0.35f)};

vec4 HightAb = {0.1f, 0.1f, 0.0f, 1.0f};
vec4 LowAb = {0.f, 0.1f, 0.1f, 1.0f};

Model		objet[] = {{"42.obj", "42.mtl", "shaderObjectSansNetT.vs", "shaderObjectSansNetT.fs", false, 0.f, -1.f, 1.f, -74.033f, -104.846f, HighLight, HightAb, NULL},
					{"42N.obj", "42.mtl", "shaderObject42N.vs", "shaderObject42N.fs", true, 0.f, -1.f, 1.f, -74.033f, -104.846f, HighLight, HightAb, NULL},
					{"teapot.obj", "teapot2.mtl", "shaderObjectSansNetT.vs", "shaderObjectSansNetT.fs", false, 0.f, 50.f, 1.f, -55.f, -104.f, HighLight, HightAb, NULL},
					{"teapot2.obj", "teapot2.mtl", "shaderObjectTeapot2.vs", "shaderObjectTeapot2.fs", true, 0.f, 100.f, 1.f, -70.033f, -104.846f, HighLight, HightAb, NULL},
					{"dragon.obj", "dragon.mtl", "shaderObjectDragon.vs", "shaderObjectDragon.fs", true, -1.4f, 0.1f, 0.07f, -74.033f, -104.846f, LowLight, LowAb, NULL},
					{"luffy.obj", "luffy.mtl", "shaderObjectLuffy.vs", "shaderObjectLuffy.fs", true, 0.f, 1.7f, 6.5f, -30.f, -40.f, HighLight, HightAb, NULL}
};

std::string default_texture = "kitten.ppm";
Model		pointer_object = objet[MODEL];
std::map<int, GLuint> texture;

Material	emerald;
Material	jade;
Material	obsidian;
Material	pearl;
Material	ruby;
Material	turquoise;
Material	brass;
Material	bronze;
Material	chrome;
Material	copper;
Material	gold;
Material	silver;
Material	black_plastic;
Material	cyan_plastic;
Material	green_plastic;
Material	red_plastic;
Material	white_plastic;
Material	yellow_plastic;
Material	black_rubber;
Material	cyan_rubber;
Material	green_rubber;
Material	red_rubber;
Material	white_rubber;
Material	yellow_rubber;
Light		light;

float vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};
