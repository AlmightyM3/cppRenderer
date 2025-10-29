#include "mesh.h"

Mesh::Mesh(std::vector<vertex> initialVertices, std::vector<uint32_t> initialIndices) {
	Mesh::vertices = initialVertices;
	Mesh::indices = initialIndices;

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