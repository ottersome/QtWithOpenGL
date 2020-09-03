#include "Cuboid.h"



Cuboid::Cuboid(float length, float height, float width):
	length(length),height(height),width(width)
{
	//MUST TODO:set interleaved spaced
	//Nothing yet to do here
	printSelf();
	buildVertices();
	std::cout << "Cuboid Initialization Finished\n" << std::endl;
	interleavedStride = sizeof(float)*8;
	std::cout << "Interleaved Stride of cube is : " << interleavedStride << std::endl;
}


Cuboid::~Cuboid()
{
}

void Cuboid::printSelf() {
	std::cout << "===== Cuboid =====\n"
		<< "   Index Count: " << getIndexCount() << "\n"
		<< "  Vertex Count: " << getVertexCount() << "\n"
		<< "  Normal Count: " << getNormalCount() << "\n"
		<< "TexCoord Count: " << getTexCoordCount() << std::endl;
}

void Cuboid::buildVertices() {

	//From bottom to top clockwise(starting furthermost left)
	//Bottom Side
	addVertex(-1.0f,-1.0f,-1.0f);
	addVertex(1.0f,-1.0f,-1.0f);
	addVertex(1.0f,-1.0f,1.0f);
	addVertex(-1.0f,-1.0f,1.0f);
	//Top Side
	addVertex(-1.0f,1.0f,-1.0f);
	addVertex(1.0f,1.0f,-1.0f);
	addVertex(1.0f,1.0f,1.0f);
	addVertex(-1.0f,1.0f,1.0f);

	//Tex Coords(THIS IS JUST A PLACEHODLER)
	//Bottom Side
	addTexCoord(-1.0f,-1.0f);
	addTexCoord(1.0f,-1.0f);
	addTexCoord(1.0f,-1.0f);
	addTexCoord(-1.0f,-1.0f);
	//Top Side
	addTexCoord(-1.0f,1.0f);
	addTexCoord(1.0f,1.0f);
	addTexCoord(1.0f,1.0f);
	addTexCoord(-1.0f,1.0f);

	//Normals Coords(THIS IS JUST A PLACEHODLER)
	//Bottom Side
	addNormal(-1.0f,-1.0f,-1.0f);
	addNormal(1.0f,-1.0f,-1.0f);
	addNormal(1.0f,-1.0f,1.0f);
	addNormal(-1.0f,-1.0f,1.0f);
	//Top Side
	addNormal(-1.0f,1.0f,-1.0f);
	addNormal(1.0f,1.0f,-1.0f);
	addNormal(1.0f,1.0f,1.0f);
	addNormal(-1.0f,1.0f,1.0f);

	//Now onto setting the indices
	//Remember Front Faces are those that are declared CCWise
	//Might want to connect the end of each face so we can use this with lines too
	//Front
	addIndices(3,2,6);
	addIndices(3,6,7);

	//Left
	addIndices(3,7,4);
	addIndices(3,4,0);

	//Bottom
	addIndices(0,1,3);
	addIndices(3,1,2);

	//Right
	addIndices(2,1,5);
	addIndices(3,5,6);

	//Top
	addIndices(6,5,4);
	addIndices(4,7,6);

	//Back
	addIndices(0,4,5);
	addIndices(5,1,0);

	buildInterleavedVertices();
 } 
