#include "Mesh.h"

Mesh::Mesh()
{
    vertices = {};
    triangles = {};
}

Mesh::Mesh(std::vector<Vector3> _vertices, std::vector<int> _triangles)
{
    vertices = _vertices;
    if (_triangles.size() % 3 == 0) {
        triangles = _triangles;
    }
    else {
        triangles = std::vector<int>();
    }
    CreateFaceNormals();
    CreateVertexNormals();
    CreateVertexList();
    
}

Mesh::~Mesh()
{
}

std::vector<Vertex> Mesh::CreateVertexList()
{
    vertexList = {};
    Vertex vert;
    for (auto it = triangles.rbegin(); it != triangles.rend(); ++it)
    {
        int test = *it;
        vert.pos = vertices[test];
        vert.normalVertex = normalsVertex[test];
        vertexList.push_back(vert);
    }
    return vertexList;
}

std::vector<Vector3> Mesh::CreateFaceNormals()
{
    for (int i = 0; i <= triangles.size() - 3; i += 3) {
        Vector3 edge1 = vertices[triangles[i + 1]] - vertices[triangles[i]];
        Vector3 edge2 = vertices[triangles[i + 2]] - vertices[triangles[i]];
        normalsFace.push_back(Vector3::Cross(edge1, edge2).normalize());
    }
    return normalsFace;
}

std::vector<Vector3> Mesh::CreateVertexNormals()
{
    normalsVertex = std::vector<Vector3>((int)vertices.size(), Vector3(0, 0, 0));
    for (int i = 0, j = -1; i < triangles.size(); i++) {
        if (i % 3 == 0) j++;
        normalsVertex[triangles[i]] += normalsFace[j];
    }
    for (auto &v : normalsVertex) {
        v.normalize();
    }
    return normalsVertex;
}
