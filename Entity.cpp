#include "Entity.h"

Entity::Entity(Mesh* m, Material* mat) {
	mesh = m;
	material = mat;
	position = XMFLOAT3(0, 0, 0);
	rotation = XMFLOAT4X4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
	scale = XMFLOAT3(1, 1, 1);
	wmDirty = true;
}
Entity::~Entity() {
	delete mesh;
	delete material;
}
void Entity::PositionDelta(XMFLOAT3 delta) {
	position.x += delta.x;
	position.y += delta.y;
	position.z += delta.z;
	wmDirty = true;
}
void Entity::SetPosition(XMFLOAT3 pos) {
	position = pos;
	wmDirty = true;
}
void Entity::SetRotation(XMFLOAT4X4 rot) {
	rotation = rot;
	wmDirty = true;
}
void Entity::SetScale(XMFLOAT3 sc) {
	scale = sc;
	wmDirty = true;
}

XMMATRIX Entity::GetWorldMatrix() {
	if (wmDirty) {
		XMMATRIX mat = XMMATRIX(scale.x, 0, 0, 0, 0, scale.y, 0, 0, 0, 0, scale.z, 0, 0, 0, 0, 1);
		mat = XMLoadFloat4x4(&rotation)*mat;
		mat = XMMATRIX(1, 0, 0, position.x, 0, 1, 0, position.y, 0, 0, 1, position.z, 0, 0, 0, 1)*mat;
		XMStoreFloat4x4(&worldMatrix, mat);
		wmDirty = false;
		return mat;
	}
	else
		return XMLoadFloat4x4(&worldMatrix);
}

Mesh* Entity::GetMesh() {
	return mesh;
}

void Entity::PrepareMaterial(XMFLOAT4X4 view, XMFLOAT4X4 projection, DirectionalLight dLight) {
	SimpleVertexShader * vertexShader = material->GetVertexShader();
	SimplePixelShader * pixelShader = material->GetPixelShader();
	// Send data to shader variables
	//  - Do this ONCE PER OBJECT you're drawing
	//  - This is actually a complex process of copying data to a local buffer
	//    and then copying that entire buffer to the GPU.  
	//  - The "SimpleShader" class handles all of that for you.
	DirectX::XMFLOAT4X4 wm;
	XMStoreFloat4x4(&wm, GetWorldMatrix());
	vertexShader->SetMatrix4x4("world", wm);
	vertexShader->SetMatrix4x4("view", view);
	vertexShader->SetMatrix4x4("projection", projection);

	// Once you've set all of the data you care to change for
	// the next draw call, you need to actually send it to the GPU
	//  - If you skip this, the "SetMatrix" calls above won't make it to the GPU!
	vertexShader->CopyAllBufferData();

	// Set the vertex and pixel shaders to use for the next Draw() command
	//  - These don't technically need to be set every frame...YET
	//  - Once you start applying different shaders to different objects,
	//    you'll need to swap the current shaders before each draw
	vertexShader->SetShader();
	pixelShader->SetShader();

	pixelShader->SetData("light", &dLight, sizeof(DirectionalLight));
}