#pragma once
#include "Basic3DGeom.h"
class Cylinder :
	public Basic3DGeom
{
public:
	Cylinder(float height = 2.0f, unsigned int sides=6.0, float radius = 1.0f);
	~Cylinder();

	void printSelf() override;
	void buildVertices() override;
private:
	std::vector<float> getUnitCircleVertices();
	void generateIndices();
private:
	float height;
	unsigned int sides;
	float radius;

    int baseCenterIndex;
    int topCenterIndex; // include center vertex
};

