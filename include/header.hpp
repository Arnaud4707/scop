#ifndef HEADER_HPP
#define HEADER_HPP

#include "structure.hpp"
#define WIDTH 800
#define HEIGHT 600

#include "shader.hpp"
#include "ObjectBlender.hpp"

struct ImagePPM {
    int width = 0;
    int height = 0;
    std::vector<uint8_t> pixels;
};

ImagePPM        loadPPM(const std::string& filename);
void 			framebuffer_size_callback(GLFWwindow *window, int width, int height);
void 			processInput(GLFWwindow *window, float *delta, Shader *ourShader, Camera *camera);
void 			vertexf(GLFWwindow *window, ObjectBlender *obj, unsigned int *VBO, unsigned int *VAO, unsigned int *lightVAO, int size);
void 			vertexdf(GLFWwindow *window, ObjectBlender *obj, unsigned int *VBO, unsigned int *VAO, unsigned int *lightVAO, int size);
void 			transform4(Shader *ourShader);
void 			scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void 			camera(Shader *ourShader);
void 			objectAndLight(Shader *ourShader, mat4 *model, mat4 *view, mat4 *projection, int width, int height, vec3 pos);
void 			materialAndLight(Shader *ourShader, mat4 *model, mat4 *view, mat4 *projection, int width, int height, Material mat, vec3 pos);
void 			initMaterials(void);
unsigned int 	loadTexture(char const *path);
void 			vertexSansNT(GLFWwindow *window, ObjectBlender *obj, unsigned int *VBO, unsigned int *VAO, unsigned int *lightVAO, int size);
void 			print_vertex(ObjectBlender *obj);
vec3 			centerObj(ObjectBlender *obj);

#endif