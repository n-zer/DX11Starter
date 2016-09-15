#include "Material.h"

Material::Material(SimpleVertexShader * vs, SimplePixelShader * ps) {
	vertexShader = vs;
	pixelShader = ps;
}

Material::~Material() {

}

SimpleVertexShader * Material::GetVertexShader() {
	return vertexShader;
}

SimplePixelShader * Material::GetPixelShader() {
	return pixelShader;
}