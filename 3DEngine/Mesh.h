#pragma once
#include "Component.h"
#include <vector>
#include "Vector.h"

struct Vertex {
	Vector3 pos;
	Vector3 normalVertex;
	//Vector3 normalFace;
};

class Mesh : public IComponent {
public:
	Mesh();
	Mesh(std::vector<Vector3> _vertices, std::vector<int> _triangles);
	~Mesh();
	std::vector<Vector3> vertices; // should be privated
	std::vector<int> triangles;   // should be privated

	std::vector<Vector3> normalsVertex;// should be privated
	std::vector<Vector3> normalsFace;// should be privated

	std::vector<Vertex> vertexList;// should be privated

public:
	std::vector<Vertex> CreateVertexList();
	std::vector<Vector3> CreateVertexNormals();
	std::vector<Vector3> CreateFaceNormals();
};