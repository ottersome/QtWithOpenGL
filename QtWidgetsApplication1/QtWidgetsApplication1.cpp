#include "QtWidgetsApplication1.h"
#include "OPGLWidg.h"

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QWidget(parent)
{
	OPGLWidg * qopwid = new OPGLWidg(this);

	QHBoxLayout *hlay = new QHBoxLayout;
	QVBoxLayout *vlay = new QVBoxLayout;

	//Creat the Buttons
	QPushButton  * b_sphere		= new QPushButton("Sphere");
	QPushButton  * b_cuboid		= new QPushButton("Cuboid");
	QPushButton  * b_triangle	= new QPushButton("Triangle");
	QPushButton  * b_cylinder	= new QPushButton("Cylinder");
	
	//Connet Buttons Signals to Widget Slots
	connect(b_sphere,SIGNAL(clicked()),qopwid,SLOT(drawSphere()));
	connect(b_cuboid,SIGNAL(clicked()),qopwid,SLOT(drawCuboid()));
	connect(b_triangle,SIGNAL(clicked()),qopwid,SLOT(drawTriangle()));
	connect(b_cylinder,SIGNAL(clicked()),qopwid,SLOT(drawCylinder()));

	//Setup the Layouts
	vlay->addWidget(b_sphere);
	vlay->addWidget(b_cuboid);
	vlay->addWidget(b_triangle);
	vlay->addWidget(b_cylinder);

	//Set Layouts
	hlay->addWidget(qopwid);
	hlay->addLayout(vlay);

	this->setLayout(hlay);
	this->resize(600,300);

    //ui.setupUi(this);
}
