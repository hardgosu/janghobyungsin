//실습20 :파묻혀도 됨

#include "stdafx.h"
#include "ProjectLibrary.h"

using namespace TestNameSpace;

GLfloat xRotated, yRotated, zRotated;
GLdouble radius = 2;
GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 }; //Black Color
GLfloat qaGreen[] = { 0.0, 1.0, 0.0, 1.0 }; //Green Color
GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 }; //White Color
GLfloat qaRed[] = { 1.0, 0.0, 0.0, 1.0 }; //White Color

										  // Set lighting intensity and color
GLfloat qaAmbientLight[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat qaDiffuseLight[] = { 1, 1, 1, 1.0 };
GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat emitLight[] = { 0.9, 0.9, 0.9, 0.01 };
GLfloat Noemit[] = { 0.0, 0.0, 0.0, 1.0 };
// Light source position
GLfloat qaLightPosition[] = { 0, 0, 0, 1 };



MasterMatrix* masterMatrix = new MasterMatrix();

void display(void);
void reshape(int x, int y);
void TimerFunc(int);
void Start();
void Mouse(int button, int state, int x, int y);
void MouseWheel(int button, int state, int x, int y);
void MouseDrag(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
bool LiangBarsky(double edgeLeft, double edgeRight, double edgeBottom, double edgeTop,   // Define the x/y clipping values for the border.
	double x0src, double y0src, double x1src, double y1src,                 // Define the start and end points of the line.
	double &x0clip, double &y0clip, double &x1clip, double &y1clip);         // The output values, so declare these outside.



void ApplyRotate();





//declare like this to create object.and use pointer
//GLint cubeList[10];

GLdouble sample[16]

{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
};
GLdouble rotateMatrix[12]
{
	0,0,0,0,
	0,0,0,0,
	0,0,0,0

};
GLdouble scaleMatrix[3]
{
	1,1,1

};




OrthoData viewportData;





//
//
//only for temporary
Polygon0 *testClass = new Polygon0(masterMatrix);
Polygon0 *board = new Polygon0(masterMatrix);
Polygon0 *hexahedron = new Polygon0(masterMatrix);
Polygon0 *hexahedron2 = new Polygon0(masterMatrix);
Polygon0 *hexahedron3 = new Polygon0(masterMatrix);

Polygon0 *sphere = new Polygon0(masterMatrix);
Polygon0 *standingHexahedron = new Polygon0(masterMatrix);
Polygon0 *standingSphere = new Polygon0(masterMatrix);
RunningMachine *runningMachine = new RunningMachine(masterMatrix);
RunningPeople *runningPeople = new RunningPeople(masterMatrix);
ChulbongPeople *chulbongPeople = new ChulbongPeople(masterMatrix);
BenchPressPeople *benchPressPeople = new BenchPressPeople(masterMatrix);
GymTree *gymTree = new GymTree(masterMatrix);

OpenCube *openCube = new OpenCube(masterMatrix);

Bezier *bezier = new Bezier(masterMatrix);


struct CollisionData
{
	double leftX;
	double topZ;
	double rightX;
	double bottomZ;

	GLVector3 position;

};
CollisionData collisionData[7];


Polygon0 *control;
Polygon0 *control2;



bool leftRotate = false;
bool rightRotate = false;

bool bothRotate = false;

bool temp[4];
int poolingNum = 0;

int sphereXDir = 1;
int sphereYDir = 1;
int sphereZDir = 1;
int sphereXVelocity = 0;
int sphereYVelocity = 0;

int hexXDir = 1;
int hexZDir = 1;
int hexXVelocity = 0;
int hexYVelocity = 0;



bool controls[2];
int controlPointer = 0;

bool CollisionCheck(CollisionData collisionData1, CollisionData collisionData2);

void idleFunc(void)
{
	if (zRotated > 360.0)
	{
		zRotated -= 360.0*floor(zRotated / 360.0);   // Don't allow overflow
	}

	if (yRotated > 360.0)
	{
		yRotated -= 360.0*floor(yRotated / 360.0);   // Don't allow overflow
	}

	if (xRotated > 360.0)
	{
		xRotated -= 360.0*floor(xRotated / 360.0);   // Don't allow overflow
	}
	//zRotated += 0.01;
	//yRotated += 0.01;
	display();

}
void initLighting()
{

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Set lighting intensity and color
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	//glDisable(GL_LIGHTING);
	//glDisable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);


}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("glutBase");
	initLighting();

	xRotated = yRotated = zRotated = 0.0;

	//glutIdleFunc(idleFunc);
	glutTimerFunc(100, TimerFunc, 1);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMouseFunc(Mouse);
	glutMouseWheelFunc(MouseWheel);
	glutMotionFunc(MouseDrag);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	Start();
	glutMainLoop();
	return 0;
}

void display(void)
{
	static double temps = 0;

	glMatrixMode(GL_MODELVIEW);
	// clear the drawing buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	//glEnable(GL_CULL_FACE_MODE);



	//glCullFace(GL_BACK);


	// clear the identity matrix.
	masterMatrix->glLoadMasterMatrix();



	masterMatrix->glSetMasterMatrix(sample, rotateMatrix, scaleMatrix);

	testClass->DrawXYZLine(viewportData.width, false, false);

	bezier->SetBasicParameter(20, false, false);
	bezier->DrawCurveLine();


	//openCube->DrawingOpenCube(200, false, false);

	

	




	glutSwapBuffers();



	//disable culling
	//glDisable(GL_CULL_FACE);




}

void reshape(int x, int y)
{

	if (y == 0 || x == 0) return;

	glViewport(0, 0, x, y);  //Use the whole window for rendering

	masterMatrix->glLoadMasterMatrix();

	viewportData.screenLTX = -x / 2;
	viewportData.screenRBX = x / 2;
	viewportData.screenRBY = -y / 2;
	viewportData.screenLTY = y / 2;
	viewportData.zNear = -800;
	viewportData.zFar = 800;
	viewportData.width = x;
	viewportData.height = y;
	viewportData.zSize = fabs(viewportData.zNear - viewportData.zFar);



	//glLoadIdentity();
	//glMatrixMode(GL_TEXTURE);
	//glMatrixMode(GL_PROJECTION);
	//gluLookAt(0, 0, 400, 0, 0, 0, 0, 1, 0);


}

void TimerFunc(int value)
{
	//printf("teapot : (%f,%f,%f)\n", teapot->Position().x, teapot->Position().y, teapot->Position().z);

	static int dir = 1;

	static int temp = 0;











	ApplyRotate();



	glutPostRedisplay();

	glutTimerFunc(1000 / 60, TimerFunc, 1);
}


void Start()
{


	srand((unsigned)time(NULL));


	masterMatrix->thisCamera.eyeY += 1000.0;
	masterMatrix->thisCamera.eyeZ += 1000.0;







}

void Mouse(int button, int state, int x, int y)
{

}

void MouseWheel(int button, int state, int x, int y)
{


}

void MouseDrag(int x, int y)
{

}

void Keyboard(unsigned char key, int x, int y)
{

	if (key == 'i')
	{

		glEnable(GL_DEPTH_TEST);

	}
	if (key == 'I')
	{

		glDisable(GL_DEPTH_TEST);

	}
	if (key == 'd')
	{

		glEnable(GL_CULL_FACE);
	}
	if (key == 'a')
	{
		glDisable(GL_CULL_FACE);
	}
	if (key == 'w')
	{

	}
	if (key == 'W')
	{

	}

	if (key == 's')
	{


	}
	if (key == 'S')
	{


	}

	if (key == 'b')
	{

		glShadeModel(GL_SMOOTH); // 또는 glShadeModel (GL_FLAT)


	}
	if (key == 'B')
	{
		glShadeModel(GL_FLAT); // 또는 glShadeModel (GL_FLAT)

	}

	if (key == 'k')
	{

	}
	if (key == 'K')
	{

	}

	if (key == 'm')
	{






	}
	if (key == 'M')
	{





	}

	if (key == 'l')
	{


	}
	if (key == 'L')
	{


	}
	if (key == 'N')
	{






	}
	if (key == 'n')
	{

	}


	if (key == 'r' || key == 'R')
	{

		rightRotate = !rightRotate;


	}

	if (key == 'o' || key == 'O')
	{

		bothRotate = !bothRotate;



	}
	else if (key == 'O')
	{

		yRotated -= 2.0;

	}
	if (key == 'y')
	{

		yRotated += 2.0;


	}
	else if (key == 'Y')
	{

		yRotated -= 2.0;

	}

	if (key == 'z')
	{


		zRotated += 2.0;

	}
	else if (key == 'Z')
	{

		zRotated -= 2.0;

	}
	if (key == 'x')
	{


		xRotated += 2.0;

	}
	else if (key == 'X')
	{

		xRotated -= 2.0;

	}

	if (key == ']')
	{

		zRotated = 0;
		xRotated = 0;
		yRotated = 0;
		masterMatrix->thisCamera.eyeX = 0.0;
		masterMatrix->thisCamera.eyeY = 0.0;
		masterMatrix->thisCamera.eyeZ = 300.0;
	}

	if (key == 'q' || key == 'Q' || key == 'ㅂ')
	{

		masterMatrix->thisCamera.eyeY -= 5.0;
		masterMatrix->thisCamera.eyeZ -= 5.0;

	}

	else if (key == 'e' || key == 'E' || key == 'ㄷ')
	{

		masterMatrix->thisCamera.eyeY += 5.0;
		masterMatrix->thisCamera.eyeZ += 5.0;

	}
	if (key == 'c' || key == 'C' || key == 'ㅊ')
	{
		/*
		poolingNum = ++poolingNum % 4;


		for (int i = 0; i < 4; ++i)
		{
			temp[i] = false;
		}

		temp[poolingNum] = true;

		leftRotate = false;
		rightRotate = false;
		bothRotate = false;
		*/
	}

}
void KeyboardUp(unsigned char key, int x, int y)
{


}

void ApplyRotate()
{
	if (zRotated > 360.0)
	{
		zRotated -= 360.0*floor(zRotated / 360.0);   // Don't allow overflow
	}

	if (yRotated > 360.0)
	{
		yRotated -= 360.0*floor(yRotated / 360.0);   // Don't allow overflow
	}

	if (xRotated > 360.0)
	{
		xRotated -= 360.0*floor(xRotated / 360.0);   // Don't allow overflow
	}


	rotateMatrix[4] = yRotated;
	rotateMatrix[5] = 0;
	rotateMatrix[6] = 1;
	rotateMatrix[7] = 0;

	rotateMatrix[0] = xRotated;
	rotateMatrix[1] = 1;
	rotateMatrix[2] = 0;
	rotateMatrix[3] = 0;

	rotateMatrix[8] = zRotated;
	rotateMatrix[9] = 0;
	rotateMatrix[10] = 0;
	rotateMatrix[11] = 1;

}


bool CollisionCheck(CollisionData collisionData1, CollisionData collisionData2)
{

	if (collisionData1.leftX > collisionData2.rightX)
		return false;

	if (collisionData1.rightX < collisionData2.leftX)

		return false;

	if (collisionData1.topZ < collisionData2.bottomZ)
		return false;

	if (collisionData1.bottomZ > collisionData2.topZ)
		return false;

	return true;


}


bool LiangBarsky(double edgeLeft, double edgeRight, double edgeBottom, double edgeTop,   // Define the x/y clipping values for the border.
	double x0src, double y0src, double x1src, double y1src,                 // Define the start and end points of the line.
	double &x0clip, double &y0clip, double &x1clip, double &y1clip)         // The output values, so declare these outside.
{

	double t0 = 0.0;    double t1 = 1.0;
	double xdelta = x1src - x0src;
	double ydelta = y1src - y0src;
	double p, q, r;

	for (int edge = 0; edge < 4; edge++)
	{   // Traverse through left, right, bottom, top edges.
		if (edge == 0) { p = -xdelta;    q = -(edgeLeft - x0src); }
		if (edge == 1) { p = xdelta;     q = (edgeRight - x0src); }
		if (edge == 2) { p = -ydelta;    q = -(edgeBottom - y0src); }
		if (edge == 3) { p = ydelta;     q = (edgeTop - y0src); }
		r = q / p;
		if (p == 0 && q < 0) return false;   // Don't draw line at all. (parallel line outside)

		if (p < 0)
		{
			if (r > t1) return false;         // Don't draw line at all.
			else if (r > t0) t0 = r;            // Line is clipped!
		}
		else if (p > 0)
		{
			if (r < t0) return false;      // Don't draw line at all.
			else if (r < t1) t1 = r;         // Line is clipped!
		}
	}

	x0clip = x0src + t0 * xdelta;
	y0clip = y0src + t0 * ydelta;
	x1clip = x0src + t1 * xdelta;
	y1clip = y0src + t1 * ydelta;

	return true;        // (clipped) line is drawn
}
