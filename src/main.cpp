// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <unistd.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include "engine.hpp"
#include "systems/render.hpp"
#include "common/shader.hpp"

bool		CreateWindow(GLFWwindow* window);
std::string	UpdateVersion();

typedef enum { SHADED, WIREFRAME, POINTS } displayModes;
displayModes mode = SHADED;
bool showBounds = false;

int main() {
	if (!CreateWindow(window)) return -1;
	srand(time(NULL));
	//setSDF();
	Engine e = Engine();
	e.addSystem(new RenderSystem());
	window = glfwGetCurrentContext();
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0 ) e.update();
	//std::cout << "THE END" << std::endl;

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

bool CreateWindow(GLFWwindow* window) {
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768,("Engine Ver 0.0." + UpdateVersion()).c_str(), NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwSwapInterval(0);
	// Initialize AntTweakBar
	// RenderSystem::initTw();
	// // Create a tweak abar
	//
	// // Set GLFW event callbacks. I removed glfwSetWindowSizeCallback for conciseness
	// glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW); // - Directly redirect GLFW mouse button events to AntTweakBar
	// glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW);          // - Directly redirect GLFW mouse position events to AntTweakBar
	// glfwSetScrollCallback(window, (GLFWscrollfun)TwEventMouseWheelGLFW);    // - Directly redirect GLFW mouse wheel events to AntTweakBar
	// glfwSetKeyCallback(window, ControlSystem::key_callback);                         // - Directly redirect GLFW key events to AntTweakBar
	// glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW);                      // - Directly redirect GLFW char events to AntTweakBar

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the vertex of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024/2, 768/2);

	return true;
}


std::string UpdateVersion() {
	int v;
	char cwd[1024];
	readlink("/proc/self/exe", cwd, 1024);
	std::string scwd = std::string(cwd);
	std::string path = scwd.substr(0, scwd.rfind("/")) + "/../VERSION";
	std::fstream myfile(path, std::ios::in | std::ios::out);
	myfile >> v;
	myfile.clear();
	myfile.seekp(0,std::ios::beg);
	myfile << ++v;
	myfile.close();
	return std::to_string(v);
}
