#ifndef TERRAIN_SYS_HPP
#define TERRAIN_SYS_HPP

#include "system.hpp"
#include "components/mesh.hpp"
#include <glfw3.h>

class TerrainSystem: public System {
	public:
		TerrainSystem();
		void update();

	private:
		void GenerateCube(int x, int y, int z, Mesh * mesh);
};

#endif