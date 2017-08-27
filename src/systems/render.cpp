#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include "render.hpp"
#include "../common/shader.hpp"

GLuint programID;
GLuint vertexbuffer;
GLuint elementbuffer;

GLuint ProjID;
GLuint ModelID;
GLuint ViewID;

glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
RenderSystem::RenderSystem() {
  this->window = glfwGetCurrentContext();

  // Dark blue background
  glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
  

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS); 
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  // Create and compile our GLSL program from the shaders
  programID = LoadShaders( "../res/Voxel.vert", "../res/Voxel.frag" );

	// Get a handle for our "MVP" uniform
	ProjID = glGetUniformLocation(programID, "projection");
	ViewID = glGetUniformLocation(programID, "view");
	ModelID = glGetUniformLocation(programID, "model");
  
  // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
  Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
  // Camera matrix
  View       = glm::lookAt(
                glm::vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
                glm::vec3(0,0,0), // and looks at the origin
                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                );
  // Model matrix : an identity matrix (model will be at the origin)
  Model      = glm::mat4(1.0f);
  // Our ModelViewProjection : multiplication of our 3 matrices
  
  static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
  };
  std::vector<unsigned short> indices;
  indices.push_back(0);
  indices.push_back(1);
  indices.push_back(2);
  indices.push_back(2);
  indices.push_back(3);
  indices.push_back(1);
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

}

void RenderSystem::update() {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Use our shader
  glUseProgram(programID);

  // Model matrix : an identity matrix (model will be at the origin)
  glm::mat4 Model      = glm::mat4(1.0f);

  glUniformMatrix4fv(ProjID, 1, GL_FALSE, &Projection[0][0]);
  glUniformMatrix4fv(ViewID, 1, GL_FALSE, &View[0][0]);
  glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);

  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
  );

  // Draw the triangle !
  glDrawElements(GL_TRIANGLES,
    6,    // count
    GL_UNSIGNED_SHORT,   // type
    (void*)0           // element array buffer offset
  );


  glDisableVertexAttribArray(0);

  // Swap buffers
  glfwSwapBuffers(window);
  glfwPollEvents();
}
