#pragma once
#include "Component.h"
#include <vector>


struct Vertex {
	float x, y, z;
};

class Mesh : public IComponent {
public:
	Mesh();
	Mesh(std::vector<Vertex> _vertices, std::vector<int> triangles);
	~Mesh();
	std::vector<Vertex> vertices;
	std::vector<int> triangles;
	std::vector<Vertex> CreateVertexList();
	std::vector<Vertex> vertexList;
};