#include "Mesh.h"

Mesh::Mesh()
{
    vertices = {};
    triangles = {};
}

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<int> _triangles)
{
    vertices = _vertices;
    triangles = _triangles;
    CreateVertexList();
}

Mesh::~Mesh()
{
}

std::vector<Vertex> Mesh::CreateVertexList()
{
    vertexList = {};
    for (auto it = triangles.rbegin(); it != triangles.rend(); ++it)
    {
        vertexList.push_back(vertices[*it]);
    }
    return vertexList;
}
