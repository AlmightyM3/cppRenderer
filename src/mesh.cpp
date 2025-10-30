#include "mesh.h"

#include <fstream>
#include <sstream>
#include <iostream>

Mesh::Mesh(std::vector<vertex> initialVertices, std::vector<uint32_t> initialIndices) {
	Mesh::vertices = initialVertices;
	Mesh::indices = initialIndices;

	Mesh::uploadData();
}

Mesh::Mesh(std::string filePath) {
	Mesh::loadOBJ(filePath);
	Mesh::uploadData();
}

Mesh::~Mesh() {

}

void Mesh::uploadData() {
	unsigned int VBO;
	glCreateBuffers(1, &VBO);
	glNamedBufferStorage(VBO, sizeof(vertex) * Mesh::vertices.size(), Mesh::vertices.data(), GL_DYNAMIC_STORAGE_BIT);

	unsigned int IBO;
	glCreateBuffers(1, &IBO);
	glNamedBufferStorage(IBO, sizeof(uint32_t) * Mesh::indices.size(), Mesh::indices.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateVertexArrays(1, &VAO);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(vertex));
	glVertexArrayElementBuffer(VAO, IBO);

	glEnableVertexArrayAttrib(VAO, 0);
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, offsetof(vertex, pos));
	glVertexArrayAttribBinding(VAO, 0, 0);

	glEnableVertexArrayAttrib(VAO, 1);
	glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, offsetof(vertex, normal));
	glVertexArrayAttribBinding(VAO, 1, 0);

	glEnableVertexArrayAttrib(VAO, 2);
	glVertexArrayAttribFormat(VAO, 2, 2, GL_FLOAT, GL_FALSE, offsetof(vertex, texCoord));
	glVertexArrayAttribBinding(VAO, 2, 0);
	Mesh::VAO = VAO;
}

void Mesh::render() {
	glBindVertexArray(Mesh::VAO);
	glDrawElements(GL_TRIANGLES, (unsigned int)Mesh::indices.size(), GL_UNSIGNED_INT, NULL);
}


void Mesh::loadOBJ(std::string filePath) {
	std::ifstream objFile(filePath);
	if (!objFile.is_open()) {
		std::cerr << "Failed to open file: " << filePath << "\n";
		exit(-1);
	}

	std::string line;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcords;
	std::vector<std::string> faces;

	while (std::getline(objFile, line)) {
		//std::cout << line << std::endl; 
		std::stringstream lineData(line);

		std::string lineStart;
		lineData >> lineStart;

		if (lineStart == "v") { // vertex position
			glm::vec3 vertPos;
			lineData >> vertPos.x;
			lineData >> vertPos.y;
			lineData >> vertPos.z;
			positions.push_back(vertPos);
		} 
		else if (lineStart == "vt") { // vertex texture
			glm::vec2 vertTex;
			lineData >> vertTex.x;
			lineData >> vertTex.y;
			texcords.push_back(vertTex);
		} 
		else if (lineStart == "vn") { // vertex normal
			glm::vec3 vertNorm;
			lineData >> vertNorm.x;
			lineData >> vertNorm.y;
			lineData >> vertNorm.z;
			normals.push_back(vertNorm);
		} 
		else if (lineStart == "f") { // face info
			std::vector<std::string> face;
			std::string vert;
			while (lineData >> vert) {
				face.push_back(vert);
			}
			if (face.size() == 3) { // If the face is a tri, we can just add it.
				faces.push_back(face[0]);
				faces.push_back(face[1]);
				faces.push_back(face[2]);
			}
			else if (face.size() > 3){ // Otherwise we need to triangulate the face.
				for (int i = 0; i < face.size() - 1; i++) {
					faces.push_back(face[0]);
					faces.push_back(face[i]);
					faces.push_back(face[i + 1]);
				}
			}
		}
	}

	objFile.close();

	Mesh::vertices = std::vector<vertex>();
	Mesh::indices = std::vector<uint32_t>();

	for (int i = 0; i < faces.size(); i++) {
		// TODO: Use indexes to get rid of duplicate vertices.
		Mesh::indices.push_back(i);

		std::stringstream face(faces[i]);
		std::string faceSegment;
		std::vector<int> faceIndices;

		while (std::getline(face, faceSegment, '/'))
		{
			if (faceSegment == "") {
				faceIndices.push_back(-1);
				continue;
			}
			faceIndices.push_back(std::stoi(faceSegment) - 1);
		}
		
		vertex newVertex;
		int faceSize = faceIndices.size();

		switch (faceSize) {
		case 3:
			if (faceIndices[2] != -1)
				newVertex.normal = normals[faceIndices[2]];
		case 2:
			if (faceIndices[1] != -1)
				newVertex.texCoord = texcords[faceIndices[1]];
		case 1:
			if (faceIndices[0] != -1)
				newVertex.pos = positions[faceIndices[0]];
		}
		Mesh::vertices.push_back(newVertex);
	}
}