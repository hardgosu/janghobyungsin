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




void display(void);
void reshape(int x, int y);
void TimerFunc(int);
void Start();
void Mouse(int button, int state, int x, int y);
void MouseWheel(int button, int state, int x, int y);
void MouseDrag(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);



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

GLdouble greenColor[4]{
	0.2,1,0,1

};

GLdouble masterMatrix[16]
{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1

};

GLdouble sample[][16]
{
	{1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	-300,0,0,1
	},

	{1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	-200,0,0,1

	},

	{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	-50,0,0,1

	},

	{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	50,0,0,1

	}

	,

	{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	200,0,0,1

	},

	{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	300,0,0,1

	},


	{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	-120,0,0,1

	}
	,
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		120,0,0,1

	}



};



GLdouble* pMatrix[6];

GLint number = 0;


tm timeStruct;

time_t now, before;


GLint aniStack;
bool cubeColon[2]{ false,false };


//declare like this to create object.and use pointer
//GLint cubeList[10];
RectangularClock* rectangularClock;
Polygon0 *testClass = new Polygon0();
TwinCube *twinCube;
MasterMatrix *masterMatrixs = new MasterMatrix();
static GLint degree = 0;
static GLdouble* result;


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
	glutTimerFunc(1000, TimerFunc, 1000);
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

	glColor3d(0.2, 1, 0);

	masterMatrixs->glLoadMasterMatrix();





	//객체그리기
	masterMatrixs->glSetMasterMatrix(masterMatrix, rotateMatrix, scaleMatrix);




	rectangularClock->RectangularClockNum(masterMatrixs, timeStruct.tm_hour / 10, 15, pMatrix[0], true, greenColor);
	rectangularClock->RectangularClockNum(masterMatrixs, timeStruct.tm_hour % 10, 15, pMatrix[1], true, greenColor);

	rectangularClock->RectangularClockNum(masterMatrixs, timeStruct.tm_min / 10, 15, pMatrix[2], true, greenColor);
	rectangularClock->RectangularClockNum(masterMatrixs, timeStruct.tm_min % 10, 15, pMatrix[3], true, greenColor);

	rectangularClock->RectangularClockNum(masterMatrixs, timeStruct.tm_sec / 10, 15, pMatrix[4], true, greenColor);
	rectangularClock->RectangularClockNum(masterMatrixs, timeStruct.tm_sec % 10, 15, pMatrix[5], true, greenColor);





	if (cubeColon[0])
		twinCube->DrawTwinCube(masterMatrixs, 10.0, 40.0, false, sample[6]);
	if (cubeColon[1])
		twinCube->DrawTwinCube(masterMatrixs, 10.0, 40.0, false, sample[7]);



	glutSwapBuffers();

}

void reshape(int x, int y)
{

	if (y == 0 || x == 0) return;

	glMatrixMode(GL_PROJECTION);
	masterMatrixs->glLoadMasterMatrix();

	//gluPerspective(39.0, (GLdouble)x / (GLdouble)y, 0.6, 40.0);




	glOrtho(-x / 2, x / 2, -y / 2, y / 2, -400, 400);


	//glMatrixMode(GL_TEXTURE);
	//glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);  //Use the whole window for rendering

}

void TimerFunc(int value) {




	now = before = time(0); //초 단위 시간을 구함
	localtime_s(&timeStruct, &now); //지역 시각을 구함

	if (aniStack >= 60) {

		aniStack = 0;
	}

	if (aniStack % 60 == 0) {


		for (int i = 0; i < 2; ++i) {

			cubeColon[i] = !cubeColon[i];
		}

	}


	//0,2,8,10


	if (zRotated > 360.0) {
		zRotated -= 360.0*floor(zRotated / 360.0);   // Don't allow overflow
	}

	if (yRotated > 360.0) {
		yRotated -= 360.0*floor(yRotated / 360.0);   // Don't allow overflow
	}

	if (xRotated > 360.0) {
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
	aniStack++;

	//printf("d");
	number = (++number) % 10;
	glutPostRedisplay();

	glutTimerFunc(value / 60, TimerFunc, value);
}


void Start()
{
	//printf("%f,%f\n", cos(180 *(PI6 / 180.0)), cos(0 *(PI6 / 180.0)));
	rectangularClock = new RectangularClock();
	yRotated = 30.0;

	xRotated = 30.0;


	//time.hour = 

	for (int i = 0; i < 6; ++i) {

		pMatrix[i] = sample[i];

	}

	aniStack = 0;

	twinCube = new TwinCube();




}

void Mouse(int button, int state, int x, int y) {

}

void MouseWheel(int button, int state, int x, int y) {

}

void MouseDrag(int x, int y) {

}

void Keyboard(unsigned char key, int x, int y) {

	if (key == 'a' || key == 'A' || key == 'ㅁ') {


		yRotated += 2.0;

	}
	else if (key == 'd' || key == 'D' || key == 'ㅇ') {

		yRotated -= 2.0;

	}

	if (key == 'w' || key == 'W' || key == 'ㅈ') {


		xRotated += 2.0;

	}
	else if (key == 's' || key == 'S' || key == 'ㄴ') {

		xRotated -= 2.0;

	}

	printf("%d\n", degree);
}
void KeyboardUp(unsigned char key, int x, int y) {


}