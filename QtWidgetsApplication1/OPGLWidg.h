#pragma once
#include <qopenglwidget.h>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <gl\GLU.h>
#include <iostream>
#include <memory>

#include "Basic3DGeom.h"
#include "Sphere.h"
#include "Cuboid.h"
#include "Cylinder.h"
#include "TriangularPrism.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <QOpenGLFunctions_4_3_Core>
#include <QTimer>

class OPGLWidg :
	public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
	Q_OBJECT
public:
    explicit OPGLWidg(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	~OPGLWidg();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
	void initializeShaders();

	//Sphere
	std::shared_ptr<Basic3DGeom> dispGeom;

	//References
	GLuint vboId;
	GLuint iboId;

	//BuffersRectangle
	QOpenGLVertexArrayObject m_vao;//our VAO
	QOpenGLBuffer m_vvbo;//Vertcie VBO
	QOpenGLBuffer m_mvbo;//Color VBO

	//Shader Program
	QOpenGLShaderProgram* m_program;

	float camPos[3];
	float curAng = 0;

private:

	void changeCamPos();
	void changeBuffer(std::shared_ptr<Basic3DGeom>);

public slots:

	void drawSphere();
	void drawCuboid();
	void drawTriangle();
	void drawCylinder();

};

