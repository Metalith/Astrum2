#ifndef RENDER_SYS_HPP
#define RENDER_SYS_HPP

#include "system.hpp"
#include <glfw3.h>
#include "components/transform.hpp"

class RenderSystem: public System {
	public:
		RenderSystem();
		void update();
		void addEntity(int e);
	private:
		GLFWwindow* window;
		Transform* tPlayer;
};

#endif
