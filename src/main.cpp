#include "../include/header.hpp" 
#include <GL/gl.h>
#include <string>

int main(void)
{
	if (!glfwInit()) // Bonne pratique : vérifier le retour de glfwInit
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

	struct GLFWCleanup {
        ~GLFWCleanup() { glfwTerminate(); }
    } cleanup;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	int nmonitor;
	GLFWmonitor** monitor = glfwGetMonitors(&nmonitor);
	const GLFWvidmode* mode = glfwGetVideoMode(monitor[0]);
 
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	pointer_object.window = glfwCreateWindow(mode->width * 0.8, mode->height * 0.8, "LearnOpenGL", NULL, NULL);
	if (pointer_object.window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(pointer_object.window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwDestroyWindow(pointer_object.window);
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, mode->width * 0.8f, mode->height * 0.8f);
	glfwSetFramebufferSizeCallback(pointer_object.window, framebuffer_size_callback);

    glfwSetScrollCallback(pointer_object.window, scroll_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(pointer_object.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader ourShader("shader/" + pointer_object.vertexShader, "shader/" + pointer_object.fragmentShader);
	glfwSetWindowUserPointer(pointer_object.window, &ourShader);
	
	glfwSetCursorPosCallback(pointer_object.window, Shader::mouse_callback_wrapper);
	Shader lightCubeShader("shader/shaderLightCube.vs", "shader/shaderLightCube.fs");
	unsigned int VAO[1];
	unsigned int lightVAO[1];
	unsigned int VBO[2];
	// unsigned int texture2;
	ourShader.setDeltaTime(0.005);
	ourShader.setRotationSpeed(2.0);

	ObjectBlender obj("model/" + pointer_object.obj, "mtl/" + pointer_object.mtl, pointer_object.uv);
	
	// ourShader.setVec3("color", vec3(1.0f));
	if (pointer_object.uv)
	{
		for (auto &m : obj.getKey()){
			int i =0;
			std::string ambient = "material[" + std::to_string(m.second) + "].ambient";
			std::string diffuse = "material[" + std::to_string(m.second) + "].diffuse";
			std::string specular = "material[" + std::to_string(m.second) + "].specular";
			std::string shininess = "material[" + std::to_string(m.second) + "].shininess";
			const std::map<int, lightning>& material = obj.getMaterials();
			for (std::vector<std::string>::const_iterator it = material.at(m.second).diffuseTexture.begin();
				it != material.at(m.second).diffuseTexture.end(); it++)
			{
				std::string tex = "texture/" + *it;
				texture.insert(std::pair<int, GLuint>(i++, loadTexture(tex.c_str())));
				ourShader.use();
				ourShader.setInt("t[" + std::to_string(m.second) + "].diffuse", m.second);
			}
			ourShader.use(); 
			ourShader.setVec3(ambient, material.at(m.second).ambient);
			ourShader.setVec3(diffuse, material.at(m.second).diffuse);
			ourShader.setVec3(specular, material.at(m.second).specular);
			ourShader.setFloat(shininess, material.at(m.second).shininess);
		}
		vertexdf(pointer_object.window, &obj, VBO, VAO, lightVAO, 2);
	}
	else
	{
		std::string tex = "texture/" + default_texture;
		texture.insert(std::pair<int, GLuint>(0,(loadTexture(tex.c_str()))));
		ourShader.use();
		ourShader.setInt("t", 0);
	 	vertexSansNT(pointer_object.window, &obj, VBO, VAO, lightVAO, 2);
	}
	glEnable(GL_DEPTH_TEST);
	// glDisable(GL_CULL_FACE);
	vec3 c = centerObj(&obj);
	mat4 projection;
	mat4 view;
	mat4 model;
	glfwSetCursorPos(pointer_object.window, mode->width * 0.8 / 2.0, mode->height * 0.8 / 2.0);
	model = mat4(1.0f);
	cam.ProcessMouseMovement(pointer_object.position_X, pointer_object.position_Y, true);
	initMaterials();
	while (!glfwWindowShouldClose(pointer_object.window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
    	processInput(pointer_object.window, &deltaTime, &ourShader, &cam);
    	// processInput(window, &deltaTime, &goldShader, &cam);

		glClearColor(pointer_object.ambient.x, pointer_object.ambient.y, pointer_object.ambient.z, pointer_object.ambient.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto &ptex : texture){
			glActiveTexture(GL_TEXTURE0 + ptex.first);
			glBindTexture(GL_TEXTURE_2D, ptex.second);
		}

		objectAndLight(&ourShader, &model, &view, &projection, mode->width, mode->height, vec3(c.x, c.y, c.z));
		// render the cube
		glBindVertexArray(VAO[0]);
		// glDrawElements(GL_TRIANGLES, 3 * obj.getdF().size(), GL_UNSIGNED_INT, 0);
    	glDrawArrays(GL_TRIANGLES, 0, obj.getVertexs().size());

		if (autoRot)
			ourShader.setRotY(ourShader.getRotY() + (ourShader.getRotationSpeed() * ourShader.getDeltaTime()));
        // also draw the lamp object
        lightCubeShader.use();
		lightCubeShader.setVec3("light", pointer_object.light.specular);
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = mat4(1.0f);
        model = translate(model, pointer_object.light.position);
        model = scale(model, vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightVAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

		// draw a cursor point

		// lightCubeShader.use();
		// lightCubeShader.setVec3("light", cursorColor);
        // lightCubeShader.setMat4("projection", projection);
        // lightCubeShader.setMat4("view", view);
        // model = mat4(1.0f);
        // model = translate(model, {0.f, 0.7f, -1.f});
        // model = scale(model, vec3(0.03f)); // a smaller cube
        // lightCubeShader.setMat4("model", model);

        // glBindVertexArray(lightVAO[0]);
        // glDrawArrays(GL_TRIANGLES, 0, 36);

		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glfwSwapBuffers(pointer_object.window);
		glfwPollEvents();
	}
	for (auto const& ptex : texture)
	{
	    glDeleteTextures(1, &ptex.second);
	}
	texture.clear();
    glDeleteVertexArrays(1, VAO);
    glDeleteVertexArrays(1, lightVAO);
    glDeleteBuffers(2, VBO);
	glDeleteProgram(lightCubeShader.ID);
	glDeleteProgram(ourShader.ID);
    // glDeleteProgram(goldShader.ID);
	glfwDestroyWindow(pointer_object.window);
	glfwTerminate();
	return 0;
}