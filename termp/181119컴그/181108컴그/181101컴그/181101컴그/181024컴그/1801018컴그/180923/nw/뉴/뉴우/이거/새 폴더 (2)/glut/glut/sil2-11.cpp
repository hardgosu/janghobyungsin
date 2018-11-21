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

Polygon0 *testClass[5];

void display(void);
void reshape(int x, int y);
void TimerFunc(int);
void Start();
void Mouse(int button, int state, int x, int y);
void MouseWheel(int button, int state, int x, int y);
void MouseDrag(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);


//declare like this to create object.and use pointer
//GLint cubeList[10];

GLdouble xTranslate, yTranslate, zTranslate;

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







//
//
//only for temporary
bool animationFlag = true;


void idleFunc(void)
{
	if (zRotated > 360.0) {
		zRotated -= 360.0*floor(zRotated / 360.0);   // Don't allow overflow
	}

	if (yRotated > 360.0) {
		yRotated -= 360.0*floor(yRotated / 360.0);   // Don't allow overflow
	}

	if (xRotated > 360.0) {
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
	glutInitWindowSize(800, 600);
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


	glMatrixMode(GL_MODELVIEW);
	// clear the drawing buffer.
	glClear(GL_COLOR_BUFFER_BIT);
	// clear the identity matrix.
	masterMatrix->glLoadMasterMatrix();



	masterMatrix->glSetMasterMatrix(sample, rotateMatrix, scaleMatrix);


	testClass[0]->DrawXYLine(400, false, true);

	//testClass->DrawCube(20, false, true);


	testClass[1]->DrawSpring(50, false, true, animationFlag);
	testClass[2]->SetPosition(GLVector3(0, 200, 0));
	testClass[2]->DrawSineGraph(50, false, true, animationFlag);

	testClass[3]->SetPosition(GLVector3(0, -200, 0));
	testClass[3]->DrawRectEscalator(50, false, true, animationFlag);

	testClass[4]->SetPosition(GLVector3(0, -100, 0));
	testClass[4]->DrawRibbon(25, false, true, animationFlag);

	//testClass->DrawCube(30);



	glutSwapBuffers();

}

void reshape(int x, int y)
{

	if (y == 0 || x == 0) return;

	masterMatrix->glLoadMasterMatrix();



	glOrtho(-x / 2, x / 2, -y / 2, y / 2, -400, 400);

	//gluPerspective(39.0, (GLdouble)x / (GLdouble)y, 0.6, 40.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	//glMatrixMode(GL_TEXTURE);
	//glMatrixMode(GL_PROJECTION);

	glViewport(0, 0, x, y);  //Use the whole window for rendering

}

void TimerFunc(int value) {
	printf("d");
	glutPostRedisplay();

	glutTimerFunc(1000 / 60, TimerFunc, 1);
}


void Start() {

	testClass[0] = new Polygon0();

	for (int i = 1; i < 5; ++i)
	{
		testClass[i] = new Polygon0(masterMatrix);

	}


	srand((unsigned)time(NULL));
	glMatrixMode(GL_PROJECTION);

}

void Mouse(int button, int state, int x, int y) {

}

void MouseWheel(int button, int state, int x, int y) {

}

void MouseDrag(int x, int y) {

}

void Keyboard(unsigned char key, int x, int y) {
	if (key == 'x')
	{
		sample[12] += 5;

	}
	else if (key == 'X')
	{
		sample[12] -= 5;
	}

	else if (key == 'y')
	{
		sample[13] += 5;

	}
	else if (key == 'Y')
	{
		sample[13] -= 5;

	}

	else if (key == 's')
	{
		scaleMatrix[0] += 0.01;

	}
	else if (key == 'S')
	{
		scaleMatrix[0] -= 0.01;

	}
	else if (key == 'r')
	{

		sample[12] += 50;
	}
	else if (key == 'R')
	{
		sample[12] -= 50;

	}
	else if (key == 't' || key == 'T')
	{
		animationFlag = !animationFlag;

	}
	else if (key == 'q' || key == 'Q')
	{
		exit(1);

	}
	else if (key == 'a' || key == 'A')
	{
		animationFlag = true;
	}


}
void KeyboardUp(unsigned char key, int x, int y) {
	if (key == 'x' || key == 'X')
	{


	}
	else if (key == 'y' || key == 'Y')
	{


	}
	else if (key == 's' || key == 'S')
	{


	}
	else if (key == 'r' || key == 'R')
	{


	}
	else if (key == 't' || key == 'T')
	{


	}
	else if (key == 'q' || key == 'Q')
	{


	}

}