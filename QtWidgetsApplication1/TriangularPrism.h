#pragma once
#include "Basic3DGeom.h"
class TriangularPrism :
	public Basic3DGeom
{
public:
	TriangularPrism(float length = 2.0f, float radius=1.0f);//Radius of circle that encloses it
	~TriangularPrism();

	void printSelf() override;
	void buildVertices() override;
private:
	float length;
	float radius;
};

