
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
Polygon0 *testClass[4];

void display(void);
void reshape(int x, int y);
void TimerFunc(int);
void Start();
void Mouse(int button, int state, int x, int y);
void MouseWheel(int button, int state, int x, int y);
void MouseDrag(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);


MasterMatrix* masterMatrix = new MasterMatrix();

//declare like this to create object.and use pointer
//GLint cubeList[10];





//temp
void MakeSphere();

GLdouble rotateArr[16]
= { 1, 0, 0, 0,
   0, 1, 0, 0,
   0, 0, 1, 0,
   0, 0, 0, 1 };

double moveX = 5;
double moveZ = 5;



GLdouble sample[16]

{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
};

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
	glLoadIdentity();

	MakeSphere();



	glutSwapBuffers();

}

void reshape(int x, int y)
{

	if (y == 0 || x == 0) return;

	glLoadIdentity();



	glOrtho(-x / 2, x / 2, -y / 2, y / 2, -400, 400);

	//gluPerspective(39.0, (GLdouble)x / (GLdouble)y, 0.6, 40.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	//glMatrixMode(GL_TEXTURE);
	//glMatrixMode(GL_PROJECTION);

	glViewport(0, 0, x, y);  //Use the whole window for rendering

}

void TimerFunc(int value)
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
	xRotated++;
	printf("d");
	glutPostRedisplay();

	glutTimerFunc(1000 / 60, TimerFunc, 1);
}


void Start()
{


	srand((unsigned)time(NULL));

}

void MakeSphere()
{
	glLineWidth(1.0);

	glTranslated(moveX, 15, moveZ);

	glPushMatrix();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	glMultMatrixd(rotateArr);

	glutWireSphere(15, 10, 10);
	glPopMatrix();
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
	switch (key)
	{

	case 'l':
		glPushMatrix();
		{
			glRotated(1, 0, 0, 1);
			glMultMatrixd(rotateArr);
			glGetDoublev(GL_MODELVIEW_MATRIX, rotateArr);
		}
		glPopMatrix();
		if (moveX >= -150)
			moveX--;
		break;
	case 'L':
		glPushMatrix();
		{
			glRotated(-1, 0, 0, 1);
			glMultMatrixd(rotateArr);
			glGetDoublev(GL_MODELVIEW_MATRIX, rotateArr);
		}
		glPopMatrix();
		if (moveX <= 150)
			moveX++;
		break;
	}

}
void KeyboardUp(unsigned char key, int x, int y)
{


}