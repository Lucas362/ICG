#ifndef OBJLOADER_H
#define OBJLOADER_H
#ifndef GLM_FORCE_PURE
#	define GLM_FORCE_PURE
#endif//GLM_FORCE_PURE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_SWIZZLE
#include <glm/ext/vector_relational.hpp>
#include <glm/vector_relational.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <ctime>
#include <vector>

// Read an .obj file and load the vertices, uvs and normals
// return true if the obj was loaded with success
bool load3DOBJok(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs, 
	std::vector<glm::vec3> & out_normals
);

#endif