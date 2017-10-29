#include "systems/terrain.hpp"
#include "systems/system.hpp"
#include "engine.hpp"

#include "components/mesh.hpp"

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
#include <vector>

Mesh mesh = Mesh();

const int CHUNK_SIZE = 16;
TerrainSystem::TerrainSystem() {
    std::cout << "New System :: Terrain!" << std::endl;

    
    /*
    For each cube in chunk
    Generate each face with offset
    foreach face in vorder
        foreach vertexindex in face
            vertex[i] + offset[n]
            normallist += normal(n)
            indices += iOrder + i
    */
    
    int chunk = engine->createEntity();
	engine->addComponent(chunk, &mesh);
    
    int i, j, k;
    for (i = 0; i < CHUNK_SIZE; i++) {
        for (j = 0; j < CHUNK_SIZE; j++) {
            for (k = 0; k < CHUNK_SIZE; k++) {
               GenerateCube(i, j, k, &mesh);
            }   
        }   
    }
}

void TerrainSystem::update() {

}

static const std::vector<GLfloat> g_vertex_buffer_data = {
    //FRONT FACE
    -0.3f, -0.3f, -0.3f,
    -0.3f,  0.3f, -0.3f,
     0.3f, -0.3f, -0.3f,
     0.3f,  0.3f, -0.3f,
    
     //BACK FACE
     0.3f, -0.3f, 0.3f,
     0.3f,  0.3f, 0.3f,
    -0.3f, -0.3f, 0.3f,
    -0.3f,  0.3f, 0.3f,

     //LEFT FACE
    -0.3f,  0.3f,  0.3f,
    -0.3f,  0.3f, -0.3f,
    -0.3f, -0.3f,  0.3f,
    -0.3f, -0.3f, -0.3f,
    
    //RIGHT FACE
    0.3f, -0.3f,  0.3f,
    0.3f, -0.3f, -0.3f,
    0.3f,  0.3f,  0.3f,
    0.3f,  0.3f, -0.3f,
    
    //TOP FACE
     0.3f,  0.3f,  0.3f,
     0.3f,  0.3f, -0.3f,
    -0.3f,  0.3f,  0.3f,
    -0.3f,  0.3f, -0.3f,

    //BOTTOM FACE
    -0.3f,  -0.3f,  0.3f,
    -0.3f,  -0.3f, -0.3f,
     0.3f,  -0.3f,  0.3f,
     0.3f,  -0.3f, -0.3f,
};

static const std::vector<GLfloat> g_normal_buffer_data = {
    //Front
     0.0f,  0.0f, -1.0f,
     0.0f,  0.0f, -1.0f,
     0.0f,  0.0f, -1.0f,
     0.0f,  0.0f, -1.0f,
    
    //Back
     0.0f,  0.0f,  1.0f,
     0.0f,  0.0f,  1.0f,
     0.0f,  0.0f,  1.0f,
     0.0f,  0.0f,  1.0f,
    
    //Left
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    //     }   
    // }
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,

    //Right
     1.0f,  0.0f,  0.0f,
     1.0f,  0.0f,  0.0f,
     1.0f,  0.0f,  0.0f,
     1.0f,  0.0f,  0.0f,

    //TOP
     0.0f,  1.0f,  0.0f,
     0.0f,  1.0f,  0.0f,
     0.0f,  1.0f,  0.0f,
     0.0f,  1.0f,  0.0f,

    //Bottom
     0.0f, -1.0f,  0.0f,
     0.0f, -1.0f,  0.0f,
     0.0f, -1.0f,  0.0f,
     0.0f, -1.0f,  0.0f,
  };

void TerrainSystem::GenerateCube(int x, int y, int z, Mesh * mesh) {
    for (unsigned int i = 0; i < g_vertex_buffer_data.size(); i++)
    {
        switch (i % 3)
        {
            case 0:
                mesh->vertices.push_back(x + g_vertex_buffer_data[i]);
                break;
            case 1:
                mesh->vertices.push_back(y + g_vertex_buffer_data[i]);
                break;
            case 2:
                mesh->vertices.push_back(z + g_vertex_buffer_data[i]);
                break;
        }
        mesh->normals.push_back(g_normal_buffer_data[i]);
    }

    unsigned int n = mesh->indices.size() / 6;
    for(unsigned int i = 0; i < g_vertex_buffer_data.size() / 3; i++)
    {
        mesh->indices.push_back((n * 4));
        mesh->indices.push_back((n * 4) + 1);
        mesh->indices.push_back((n * 4) + 2);
        mesh->indices.push_back((n * 4) + 1);
        mesh->indices.push_back((n * 4) + 3);
        mesh->indices.push_back((n * 4) + 2);
      n = mesh->indices.size() / 6;
    }
}