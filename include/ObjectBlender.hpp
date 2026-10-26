#ifndef OBJECTBLENDER_HPP
#define OBJECTBLENDER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>
#include <bits/stdc++.h>
#include "structure.hpp"
#include "fonction_math.hpp"
#include "global.hpp"

struct vertex
{
	vec3 position;
	vec3 normal;
	vec2 texcoord;
	int idMaterial;
};

struct key{
	std::string index;
	int nbIndex;
};

struct lightning
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 emission;

	float shininess;
	float opacity;
	
	std::vector<std::string> diffuseTexture;
};

class ObjectBlender
{
private:
	std::string name;
	std::vector<vertex> vertexs;
	std::vector<face> faces;
	std::vector<vec3> v;
	std::vector<vec3> n;
	std::vector<vec2> t;
	std::vector<dface> dfaces;
	std::map<int, lightning> color;
	std::map<std::string, int> keys;
	lightning light;

public:
	ObjectBlender(std::string fileObj, std::string fileMtl, bool uv);
	ObjectBlender(const ObjectBlender &o);
	ObjectBlender &operator=(const ObjectBlender &o);
	~ObjectBlender();

	int		parserModelUV(std::string fileObj, std::string fileMtl);
	int		parserModel(std::string fileObj, std::string fileMtl);
	const	std::vector<vec3> &getV() const;
	const	std::vector<face> &getF() const;
	const	std::vector<dface> &getdF() const;
	const	std::vector<vertex> &getVertexs() const;
	const	std::string &getName() const;
	const	lightning &getlightning() const;
	const	std::map<std::string, int> &getKey() const;
	const	std::map<int, lightning> &getMaterials() const;
	void	calculeNormal();
	int		parseLight(std::string text);
	void	generateTexCoords();
	void	mouse_callback(GLFWwindow *window, double xposIn, double yposIn);

	void	tri(bool uv);
};

#endif