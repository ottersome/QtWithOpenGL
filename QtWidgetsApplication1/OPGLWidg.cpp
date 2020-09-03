#include "OPGLWidg.h"
#include <math.h>



OPGLWidg::OPGLWidg(QWidget* parent, Qt::WindowFlags f) : QOpenGLWidget(parent, f)
{
	//This works but it dont seem right 
	//Without these three lines the rendering will be updated
	//only a couple of times or so 
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(10);
}


OPGLWidg::~OPGLWidg()
{

}


void OPGLWidg::initializeGL() {
	//Modern OpenGL

	initializeOpenGLFunctions();

	//Set Clear Color
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	//Create and Compile the Shaders
	m_program = new QOpenGLShaderProgram();
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
		R"(#version 430 core
		layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
		layout (location = 1) in vec3 normal;
		layout (location = 2) in vec2 textcoord;
		uniform mat4 Projection;
		uniform mat4 ModelView;
		uniform mat3 normMatrix;
		uniform vec4 lightPos;
		out vec3 newNormal;
		out vec3 lightDirVec;
			void main()
			{
			    vec4 vecMV = ModelView *vec4(aPos,1.0); 
			    newNormal = normMatrix *normal; 
			    lightDirVec = (ModelView *lightPos).xyz - vecMV.xyz; 
			    gl_Position = Projection*ModelView*vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
			})"
                                    );
 
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
		R"(#version 430 core
		in vec3 newNormal;
		in vec3 lightDirVec;
		out vec4 FragColor;
		void main()
		{
				vec4 ambientLight = vec4(0.8f*vec3(0.2f,0.2f,0.2f),1);
				vec3 L = normalize(lightDirVec);
				vec3 N = normalize(newNormal);
				float angle = max(dot(L,N),0);
				vec4 diffuseLight = vec4(1.0f*angle*vec3(0.8f,0.8f,0.8f),1.0f);
				FragColor = vec4(0.8f,0.1f,0.2f,1.0f)*(diffuseLight+ambientLight);
		})"
                                    );
    m_program->link();
    m_program->bind(); // bind Shader (Do not release until VAO is created:s)

	//Generate Our Buffers
	glGenBuffers(1, &vboId);
	glGenBuffers(1, &iboId);

	glFrontFace(GL_CCW);

	drawCuboid(); 
}
void OPGLWidg::resizeGL(int w, int h) {


}
void OPGLWidg::changeCamPos() {
	camPos[0] = sin(curAng) * 5;
	camPos[1] = 3;
	camPos[2] = cos(curAng) * 5;
	curAng += fmod((360 / 30)*0.001, 3.14f);
}
void OPGLWidg::paintGL() {
	changeCamPos();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camPos[0],camPos[1],camPos[2],
		0,0,0,
		0,1,0
		);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLfloat)512 / (GLfloat)512, 1, 500);

	
    const qreal retinaScale = devicePixelRatio();
	glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    m_program->bind();

	// Clear
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	//bind VBOs
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);

	GLfloat pmtx[16];
	GLfloat mmtx[16];
	glGetFloatv(GL_PROJECTION_MATRIX,pmtx);
	glGetFloatv(GL_MODELVIEW_MATRIX,mmtx);


	GLint pmatLoc		= glGetUniformLocation(m_program->programId(), "Projection");
	GLint mmatLoc		= glGetUniformLocation(m_program->programId(), "ModelView");
	GLint nmatLoc		= glGetUniformLocation(m_program->programId(), "normMatrix");
	GLint lightPosLoc	= glGetUniformLocation(m_program->programId(), "lightPos");
	
	//Send Values
	glUniformMatrix4fv(pmatLoc,1,GL_FALSE,pmtx);
	glUniformMatrix4fv(mmatLoc,1,GL_FALSE,mmtx);
	glUniform4f(lightPosLoc,-5.0f,3.0f,5.0f,1.0f);//Light Position
	
	//Calculate Normal Matrix
	glm::mat4 modelView(mmtx[0],mmtx[1],mmtx[2],mmtx[3],mmtx[4],mmtx[5],mmtx[6],mmtx[7],mmtx[8],mmtx[9],mmtx[10],mmtx[11],mmtx[12],mmtx[13],mmtx[14],mmtx[15]);
	glm::mat3 normMatrix = glm::transpose(glm::inverse(glm::mat3(modelView)));
	//std::cout << "This is the normmatrix :\n";
	//std::cout << glm::to_string(normMatrix)<<std::endl;
	glUniformMatrix3fv(nmatLoc,1,GL_FALSE,&normMatrix[0][0]);//TODO check that that adddress is correct

	// activate attrib arrays
	glPointSize(5.0f);//No need for this unless we are drawing points
	// draw a sphere with VBO
	glDrawElements(GL_TRIANGLES,
		dispGeom->getIndexCount(),          // # of indices
		GL_UNSIGNED_INT,                 // data type
		(void*)0);                       // offset to indices


	// unbind VBOs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
    m_program->release();
}

//Slots

void OPGLWidg::drawSphere() {
	printf("Drawing Sphere...\n");

	//Create our vertices
	std::shared_ptr<Sphere>  sphere = std::make_shared<Sphere>(1.0f, 36, 18);
	// can change parameters later
	sphere->setRadius(2.0f);
	sphere->setSectorCount(32);
	sphere->setStackCount(32);
	sphere->setSmooth(false);

	dispGeom = sphere;
	changeBuffer(sphere);

}
void OPGLWidg::drawCuboid() {
	printf("Drawing Cuboid...\n");
	//Use Default Settings
	std::shared_ptr<Cuboid> cuboid = std::make_shared<Cuboid>();
	//We could set some options here for cuboid just like we did for sphere
	
	//Set our displayed geometry to cuboid
	dispGeom = cuboid;
	changeBuffer(cuboid);

}
void OPGLWidg::drawTriangle() {
	printf("Drawing Triangle...\n");
	std::shared_ptr<TriangularPrism> trigPrism = std::make_shared<TriangularPrism>();
	dispGeom = trigPrism;
	changeBuffer(trigPrism);
}
void OPGLWidg::drawCylinder() {
	printf("Drawing Cylinder...\n");
	std::shared_ptr<Cylinder> cylinder = std::make_shared<Cylinder>(2,16,1);
	dispGeom = cylinder;
	changeBuffer(cylinder);
}
void OPGLWidg::changeBuffer(std::shared_ptr<Basic3DGeom> bgeom) {

	//Do the VBO creation here.
	glBindBuffer(GL_ARRAY_BUFFER, vboId);           // for vertex data
	glBufferData(GL_ARRAY_BUFFER,                   // target
		bgeom->getInterleavedVertexSize(), // data size, # of bytes
		bgeom->getInterleavedVertices(),   // ptr to vertex data
		GL_STATIC_DRAW);                   // usage
	std::cout << "BGeom vertex amnt : " << bgeom->getInterleavedVertexSize()<<std::endl;
	std::cout << "VBOid initialized to :" << vboId << std::endl;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);   // for index data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
		bgeom->getIndexSize(),             // data size, # of bytes
		bgeom->getIndices(),               // ptr to index data
		GL_STATIC_DRAW);                   // usage
	std::cout << "BGeom index no : " << bgeom->getIndexSize()<<std::endl;

	std::cout << "iboId initialized to :" << iboId << std::endl;
	std::cout << "Initialized just fine\n" << std::endl;
	
	std::cout << "Now doing the attributes" << std::endl;

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	// set attrib arrays with stride and offset
	int stride = bgeom->getInterleavedStride();     // should be 32 bytes
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float)*8, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float)*8, (void*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(float)*8, (void*)(sizeof(float)*6));
}
