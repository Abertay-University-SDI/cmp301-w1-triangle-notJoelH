#include "ColourTriangle.h"

// TriangleMesh.cpp
// Simple triangle mesh for example purposes. With texture cooridnates and normals.


// Initialise buffers and load texture.
ColourTriangle::ColourTriangle(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	initBuffers(device);
}


// Release resources.
ColourTriangle::~ColourTriangle()
{
	// Run parent deconstructor
	BaseMesh::~BaseMesh();
}

// Build shape and fill buffers.
void ColourTriangle::initBuffers(ID3D11Device* device)
{
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	//Set vertices to 4 to create quad
	//Set indices to 6 to create 2 triangles
	vertexCount = 4;
	indexCount = 6;

	VertexType_Colour* vertices = new VertexType_Colour[vertexCount];
	unsigned long* indices = new unsigned long[indexCount];

	// Load the vertex array with data.
	vertices[0].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);  // Top Left
	vertices[0].colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	vertices[1].position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // Top Right
	vertices[1].colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // bottom right.
	vertices[2].colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	vertices[3].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // bottom left.
	vertices[3].colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	//Draw 2 triangles counter clockwise

	// Load the index array with data.
	indices[0] = 3;  // Bottom Left.
	indices[1] = 1;	 // Top Right
	indices[2] = 0;  // Top Left

	indices[3] = 3;  // Bottom Left.
	indices[4] = 2;  // Bottom right.
	indices[5] = 1;  // Top right.

	D3D11_BUFFER_DESC vertexBufferDesc = { sizeof(VertexType_Colour) * vertexCount, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
	vertexData = { vertices, 0 , 0 };
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

	D3D11_BUFFER_DESC indexBufferDesc = { sizeof(unsigned long) * indexCount, D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER, 0, 0, 0 };
	indexData = { indices, 0, 0 };
	device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;
}

void ColourTriangle::sendData(ID3D11DeviceContext* deviceContext, D3D_PRIMITIVE_TOPOLOGY top)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType_Colour);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(top);
}


