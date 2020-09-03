#pragma once
#include "Basic3DGeom.h"
class Cuboid :
	public Basic3DGeom
{
public:
	Cuboid(float length = 1.0f, float height = 1.0f, float width = 1.0f);
	~Cuboid();

	void printSelf() override;
	void buildVertices() override;

private:
	float length, height, width;

};

