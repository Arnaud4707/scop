#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat2.hpp"
#include "Mat3.hpp"
#include "Mat4.hpp"
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct face
{
	int x;
	int y;
	int z;
};

struct dface
{
	face	position;
	face	normal;
	face	texture;
	int	idMaterial;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
	std::string diffuseTexture;
};

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Model
{
	std::string obj;
	std::string mtl;
	std::string vertexShader;
	std::string fragmentShader;
	bool		uv;
	float		rotation_X;
	float		rotation_Y;
	float		scale;
	float		position_X;
	float		position_Y;
	Light		light;
	vec4		ambient;
	GLFWwindow * window;
};

enum objet{
	R42,
	R42N,
	TEA,
	TEA2,
	DRAGON,
	LUFFY
};

#endif