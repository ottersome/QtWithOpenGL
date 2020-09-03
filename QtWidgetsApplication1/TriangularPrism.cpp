#include "TriangularPrism.h"



TriangularPrism::TriangularPrism(float length, float radius)
	: length(length),radius(radius)
{
	
	printSelf();
	buildVertices();
	std::cout << "Cuboid Initialization Finished\n" << std::endl;
	interleavedStride = sizeof(float)*8;
	std::cout << "Interleaved Stride of cube is : " << interleavedStride << std::endl;
}



void TriangularPrism::printSelf() {
	std::cout << "===== Triangular Prism =====\n"
		<< "   Length: " << this->length << "\n"
		<< "   Radius: " << this->radius << "\n"
		<< "   Index Count: " << getIndexCount() << "\n"
		<< "  Vertex Count: " << getVertexCount() << "\n"
		<< "  Normal Count: " << getNormalCount() << "\n"
		<< "TexCoord Count: " << getTexCoordCount() << std::endl;
}

void TriangularPrism::buildVertices() {
	//Ill Hardcode the points in unit circle
	//Bottom
	addVertex(-0.866f,-1,0.5f);
	addVertex(0.866f,-1,0.5f);
	addVertex(0.0,-1,-1.0f);

	//Top
	addVertex(-0.866f,1,0.5f);
	addVertex(0.866f,1,0.5f);
	addVertex(0.0,1,-1.0f);

	//Add Normals
	addNormal(-0.866f,-1,0.5f);
	addNormal(0.866f,-1,0.5f);
	addNormal(0.0,-1,-1.0f);

	//Top
	addNormal(-0.866f,1,0.5f);
	addNormal(0.866f,1,0.5f);
	addNormal(0.0,1,-1.0f);

	//Add Texture Coordinates(NOTWORKING, JUst place holder)
	addTexCoord(-0.866f,-1);
	addTexCoord(0.866f,-1);
	addTexCoord(0.0,-1);

	//Top
	addTexCoord(-0.866f,1);
	addTexCoord(0.866f,1);
	addTexCoord(0.0,1);

	//Now add the indices
	addIndices(0,2,1);

	addIndices(1,2,5);
	addIndices(1,5,4);

	addIndices(4,5,3);

	addIndices(3,5,2);
	addIndices(3,2,0);

	addIndices(0,1,4);
	addIndices(0,4,3);

	buildInterleavedVertices();

}


TriangularPrism::~TriangularPrism()
{
}
