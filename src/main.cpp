/*
 * Pyramid.cpp
 *
 *
 *  Created with the purpose of studying Graphic Programming
 *
 *		Author: BrunoEstevamRJ
 *
 */

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using WINDOW_TITLE "Pyramid"








void UCreateMesh(GLMesh& mesh){
	GLfloat verts[] = {
/**           Vertices                Normals      Texture Coordinates      **/
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,	  0.0f, 0.0f,
  		 0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,	  1.0f, 0.0f,
  		 0.0f,  0.5f,  0.0f,	0.0f,  0.0f, -1.0f,	  0.5f, 1.0f,
  
  	    -0.5f, -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,	  0.0f, 0.0f,
   	     0.5f, -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,	  1.0f, 0.0f,
   	     0.0f,  0.5f,  0.0f,	0.0f,  0.0f,  1.0f,	  0.5f, 1.0f,
  		  
   		-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,	  0.0f, 1.0f,
   		-0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,	  0.0f, 0.0f,
    	 0.0f,  0.5f,  0.0f,   -1.0f,  0.0f,  0.0f,	  0.5f, 1.0f,
  
   		 0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,	  0.0f, 1.0f,
   		 0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,	  0.0f, 0.0f,
   		 0.0f,  0.5f,  0.0f,    1.0f,  0.0f,  0.0f,	  0.5f, 1.0f,
  
		 0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,	  1.0f, 1.0f,
 		 0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,	  1.0f, 0.0f,
 		 0.0f,  0.5f,  0.0f,	0.0f, -1.0f,  0.0f,	  0.5f, 1.0f,
 		  
 		-0.5f, -0.5f,  0.5f,	0.0f,  1.0f,  0.0f,	  0.0f, 0.0f,
 		-0.5f, -0.5f, -0.5f,	0.0f,  1.0f,  0.0f,	  0.0f, 1.0f,
 		 0.0f,  0.5f,  0.0f,	0.0f,  1.0f,  0.0f,	  0.5f, 1.0f,

	};

	/*--[ Initialize Vertex Attribute Pointer ]--*/
	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerNormal = 3;
	const GLuint floatsPerUV = 2;
	const GLuint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

	/*--[ Number of Vertices ]--*/
	mesh.nVertices = sizeof(verts) / stride;

	/*--[ VAO & VBO ]--*/
	glGenVertexArrays(1, &mesh.VAO);
	glGenBuffers(1, &mesh, VBO);

	/*--[ Bind VAO ]--*/
	glBindVertexArray(mesh.VAO);

	/*--[ Bind and fill VBO ]--*/
	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);

	/*--[ Vertex Positions ]--*/
	glEnableVertexAttribArray(0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIS_DRAW);

	/*--[ nORMALS ]--*/
	glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));

	/*--[ UVs ]--*/
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*) (sizeof(float) * (floatsPerVertex + floatsPerNormal)));


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}