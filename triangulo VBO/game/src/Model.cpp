#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
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

#include <glm/glm.hpp>

#include "../include/Model.hpp"

bool load3DOBJok(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
){
	printf("Loading OBJ file %s...\n", path);
    std::vector<int> vertexIndices;
    std::vector<int> uvIndices;
    std::vector<int> normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file!\n");
        return false;
    }


    while( 1 ){
        char lineHeader[128];
        // read the first word of the line

        int res = fscanf(file, "%s", lineHeader);
        printf("%d", res);
        if (res == EOF) {
            break; // EOF = End Of File. Quit the loop.
        } else {
            // parse lineHeader
            if ( strcmp( lineHeader, "v" ) == 0 ){
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
                temp_vertices.push_back(vertex);
            } else if ( strcmp( lineHeader, "vt" ) == 0 ){
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y );
                temp_uvs.push_back(uv);
            } else if ( strcmp( lineHeader, "vn" ) == 0 ){
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
                temp_normals.push_back(normal);
            } else if ( strcmp( lineHeader, "f" ) == 0 ){
                std::string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
                    &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                    &vertexIndex[2], &uvIndex[2], &normalIndex[2]
                );
                if (matches != 9){
                    printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                    return false;
                }
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices    .push_back(uvIndex[0]);
                uvIndices    .push_back(uvIndex[1]);
                uvIndices    .push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
        }
    }

    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
        // printf("%d\n", vertexIndex);
        unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];

        out_vertices.push_back(vertex);
		out_uvs     .push_back(uv);
		out_normals .push_back(normal);
    }
    fclose(file);
	return true;
}