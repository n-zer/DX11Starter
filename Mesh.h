#pragma once
#include <d3d11.h>
#include "Vertex.h"
class Mesh
{
public:
	Mesh();
	Mesh(Vertex* verts,unsigned int vertCount, unsigned int* inds, unsigned int indCount, ID3D11Device* dev);
	~Mesh();
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	unsigned int GetIndexCount();

private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	unsigned int indexCount;
};