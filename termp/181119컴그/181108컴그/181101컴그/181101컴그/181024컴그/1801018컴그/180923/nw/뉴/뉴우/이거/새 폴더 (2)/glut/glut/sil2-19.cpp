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
Polygon0 *sphere = new Polygon0(masterMatrix);



Polygon0 *control;


bool leftRotate = false;
bool rightRotate = false;

bool bothRotate = false;

bool temp[4];
int poolingNum = 0;

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

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("glutBase");
	//initLighting();

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



	glEnable(GL_CULL_FACE_MODE);



	glCullFace(GL_BACK);


	// clear the identity matrix.
	masterMatrix->glLoadMasterMatrix();



	masterMatrix->glSetMasterMatrix(sample, rotateMatrix, scaleMatrix);

	testClass->DrawXYZLine(viewportData.width, false, false);

	//testClass->DrawCube(30);



	board->DrawBoard(500, false, true);
	board->SetPosition(0, -300, 0);


	sphere->DrawWireSphere(100, true, false);



	glutSwapBuffers();



	//disable culling
	glDisable(GL_CULL_FACE);




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



	static double temp = 0;




	ApplyRotate();



	glutPostRedisplay();

	glutTimerFunc(1000 / 60, TimerFunc, 1);
}


void Start()
{


	srand((unsigned)time(NULL));
	control = sphere;
	sphere->SetPosition(0, -280, 100);
	control->freeAxisRotate = true;
	control->SetFreeRotateXAxis(GLVector3(0, -280, 100), GLVector3(-7, -280, 100));
	control->SetFreeRotateYAxis(GLVector3(0, -280, 100), GLVector3(0, -280 - 7, 100));
	control->SetFreeRotateZAxis(GLVector3(0, -280, 100), GLVector3(0, -280, 100 - 7));
	//control->Rotate2(90, 1, 1, 0, 0);
	control->rotationAccumulate = true;

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
		sphere->SetPosition(0, -280, 100);
		control->freeAxisRotate = true;
		control->SetFreeRotateXAxis(control->Position(), GLVector3(control->Position().x - 7, control->Position().y, control->Position().z));
		control->SetFreeRotateYAxis(control->Position(), GLVector3(control->Position().x, control->Position().y - 7, control->Position().z));
		control->SetFreeRotateZAxis(control->Position(), GLVector3(control->Position().x, control->Position().y, control->Position().z - 7));

	}
	if (key == 'd')
	{



	}
	if (key == 'a')
	{


	}
	if (key == 'w')
	{



	}
	if (key == 's')
	{


	}

	if (key == 'm')
	{
		control->RotateNoGimbalLock(0, 5, 0);

	}
	if (key == 'M')
	{
		control->RotateNoGimbalLock(0, -5, 0);
	}

	if (key == 'l')
	{

		control->Translate(5, 0, 0);
		control->RotateNoGimbalLock(0, 0, -5);



	}
	if (key == 'L')
	{
		control->Translate(-5, 0, 0);
		control->RotateNoGimbalLock(0, 0, 5);

	}
	if (key == 'N')
	{

		control->Translate(0, 0, 5);
		control->RotateNoGimbalLock(5, 0, 0);


	}
	if (key == 'n')
	{
		control->Translate(0, 0, -5);
		control->RotateNoGimbalLock(-5, 0, 0);

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

	}

	if (key == 'q' || key == 'Q' || key == '¤²')
	{

		masterMatrix->thisCamera.eyeZ -= 2.0;

	}

	else if (key == 'e' || key == 'E' || key == '¤§')
	{

		masterMatrix->thisCamera.eyeZ += 2.0;

	}
	if (key == 'c' || key == 'C' || key == '¤º')
	{

		poolingNum = ++poolingNum % 4;


		for (int i = 0; i < 4; ++i)
		{
			temp[i] = false;
		}

		temp[poolingNum] = true;

		leftRotate = false;
		rightRotate = false;
		bothRotate = false;

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