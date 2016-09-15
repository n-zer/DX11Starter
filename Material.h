#pragma once
#include "SimpleShader.h"


class Material {
public:
	Material(SimpleVertexShader * vs, SimplePixelShader * ps);
	~Material();
	SimpleVertexShader * GetVertexShader();
	SimplePixelShader * GetPixelShader();
private:
	SimpleVertexShader * vertexShader;
	SimplePixelShader * pixelShader;
};
