#include "Entity.h"

Entity::Entity(Mesh* m){
	mesh = m;
	position = XMFLOAT3(0, 0, 0);
	rotation = XMFLOAT4X4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
	scale = XMFLOAT3(1, 1, 1);
	wmDirty = true;
}
Entity::~Entity() {
	delete mesh;
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