#ifndef RENDER_SYS_HPP
#define RENDER_SYS_HPP

#include "system.hpp"
#include <glfw3.h>

class RenderSystem: public System {
	public:
		RenderSystem();
		void update();
	private:
		GLFWwindow* window;
};

#endif
