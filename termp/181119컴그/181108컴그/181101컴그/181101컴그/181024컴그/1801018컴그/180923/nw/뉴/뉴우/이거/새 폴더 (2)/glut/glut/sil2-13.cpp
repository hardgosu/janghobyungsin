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

GLVector3 nextPosition;
GLdouble distance;


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



//
//
//only for temporary


GLVector3 asd[3];
GLVector3 asd2[3];
GLdouble distance1[3];
GLdouble distance2[3];

GLdouble sizeOfObject;

int stack1 = 0;
int stack2 = 0;


GLdouble localScaleMatrix1[3]
{
	1,1,1

};
GLdouble localScaleMatrix2[3]
{
	1,1,1

};

GLdouble localRotateMatrix1[4]
{
	0,0,0,0

};
GLdouble localRotateMatrix2[4]
{
	0,0,0,0

};

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

	for (int i = 0; i < 2; ++i)
	{
		testClass[i]->Create3DObject(8, sizeOfObject, false, true);

	}
	testClass[0]->Scale(GLVector3(localScaleMatrix1[0], localScaleMatrix1[1], localScaleMatrix1[2]));
	testClass[1]->Scale(GLVector3(localScaleMatrix2[0], localScaleMatrix2[1], localScaleMatrix2[2]));



	testClass[2]->Create3DObject(10, 25, false, true);
	testClass[3]->Create3DObject(10, 25, false, true);

	testClass[2]->Rotate2(GLVector4(2, 0, 1, 0), 1);

	testClass[3]->Rotate2(GLVector4(1, 0, 1, 0), 1);


	if (stack1 == 0)
	{
		testClass[2]->Translate(GLVector3((asd[1].x - asd[0].x) / distance1[0], (asd[1].y - asd[0].y) / distance1[0], (asd[1].z - asd[0].z) / distance1[0]));
	}

	else if (stack1 == 1)
	{
		testClass[2]->Translate(GLVector3((asd[2].x - asd[1].x) / distance1[1], (asd[2].y - asd[1].y) / distance1[1], (asd[2].z - asd[1].z) / distance1[1]));

	}
	else if (stack1 == 2)
	{

		testClass[2]->Translate(GLVector3((asd[0].x - asd[1].x) / distance1[2], (asd[0].y - asd[2].y) / distance1[2], (asd[0].z - asd[2].z) / distance1[2]));
	}

	if (stack2 == 0)

	{
		testClass[3]->Translate(GLVector3((asd2[1].x - asd2[0].x) / distance2[0], (asd2[1].y - asd2[0].y) / distance2[0], (asd2[1].z - asd2[0].z) / distance2[0]));
	}

	else if (stack2 == 1)
	{
		testClass[3]->Translate(GLVector3((asd2[2].x - asd2[1].x) / distance2[1], (asd2[2].y - asd2[1].y) / distance2[1], (asd2[2].z - asd2[1].z) / distance2[1]));

	}
	else if (stack2 == 2)
	{

		testClass[3]->Translate(GLVector3((asd2[0].x - asd2[1].x) / distance2[2], (asd2[0].y - asd2[2].y) / distance2[2], (asd2[0].z - asd2[2].z) / distance2[2]));
	}
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





	/*
	asd[0] = GLVector3(testClass[0]->Position().x - 1 * 50 * 1, testClass[0]->Position().y, testClass[0]->Position().z);
	asd[1] = GLVector3(testClass[0]->Position().x, testClass[0]->Position().y + 1 * 50 * 3, testClass[0]->Position().z);
	asd[2] = GLVector3(testClass[0]->Position().x + 1 * 50 * 1, testClass[0]->Position().y, testClass[0]->Position().z);


	asd2[0] = GLVector3(testClass[1]->Position().x - 1 * 50 * 1, testClass[1]->Position().y, testClass[1]->Position().z);
	asd2[1] = GLVector3(testClass[1]->Position().x, testClass[1]->Position().y + 1 * 50 * 3, testClass[1]->Position().z);
	asd2[2] = GLVector3(testClass[1]->Position().x + 1 * 50 * 1, testClass[1]->Position().y, testClass[1]->Position().z);
	*/

	asd[0] = GLVector3(testClass[0]->Position().x - 1 * sizeOfObject * localScaleMatrix1[0], testClass[0]->Position().y, testClass[0]->Position().z);
	asd[1] = GLVector3(testClass[0]->Position().x, testClass[0]->Position().y + 1 * sizeOfObject * localScaleMatrix1[1], testClass[0]->Position().z);
	asd[2] = GLVector3(testClass[0]->Position().x + 1 * sizeOfObject * localScaleMatrix1[0], testClass[0]->Position().y, testClass[0]->Position().z);

	asd2[0] = GLVector3(testClass[1]->Position().x, testClass[1]->Position().y, testClass[1]->Position().z + 1 * sizeOfObject * localScaleMatrix2[0]);
	asd2[1] = GLVector3(testClass[1]->Position().x, testClass[1]->Position().y + 1 * sizeOfObject * localScaleMatrix2[1], testClass[1]->Position().z);
	asd2[2] = GLVector3(testClass[1]->Position().x, testClass[1]->Position().y, testClass[1]->Position().z - 1 * sizeOfObject * localScaleMatrix2[0]);

	if (stack1 == 0 && testClass[2]->Position().x >= asd[1].x)
	{

		testClass[2]->SetPosition(GLVector3(asd[1].x, asd[1].y, asd[1].z));
		stack1 = 1;
	}

	else if (stack1 == 1 && testClass[2]->Position().x >= asd[2].x)
	{

		testClass[2]->SetPosition(GLVector3(asd[2].x, asd[2].y, asd[2].z));
		stack1 = 2;
	}
	else if (stack1 == 2 && testClass[2]->Position().x <= asd[0].x)
	{
		testClass[2]->SetPosition(GLVector3(asd[0].x, asd[0].y, asd[0].z));
		stack1 = 0;

	}


	if (stack2 == 0 && testClass[3]->Position().z <= asd2[1].z)
	{

		testClass[3]->SetPosition(GLVector3(asd2[1].x, asd2[1].y, asd2[1].z));
		stack2 = 1;
	}
	else if (stack2 == 1 && testClass[3]->Position().z <= asd2[2].z)
	{

		testClass[3]->SetPosition(GLVector3(asd2[2].x, asd2[2].y, asd2[2].z));
		stack2 = 2;
	}
	else if (stack2 == 2 && testClass[3]->Position().z >= asd2[0].z)
	{
		testClass[3]->SetPosition(GLVector3(asd2[0].x, asd2[0].y, asd2[0].z));
		stack2 = 0;

	}

	




	//printf("%f",masterMatrix->currentYRotateMatrix[0]);
	glutPostRedisplay();

	glutTimerFunc(1000 / 60, TimerFunc, 1);
}


void Start() {


	srand((unsigned)time(NULL));
	glMatrixMode(GL_PROJECTION);


	for (int i = 0; i < 4; ++i)
	{
		testClass[i] = new Polygon0();

		testClass[i]->masterMatrixs = masterMatrix;
	}

	sizeOfObject = 50;
	localScaleMatrix1[0] = 1;
	localScaleMatrix1[1] = 3;
	localScaleMatrix1[2] = 1;

	localScaleMatrix2[0] = 1;
	localScaleMatrix2[1] = 3;
	localScaleMatrix2[2] = 1;


	testClass[0]->Rotate(GLVector4(0, 0, 1, 0), 1);
	testClass[1]->Rotate(GLVector4(90, 0, 1, 0), 1);


	asd[0] = GLVector3(testClass[0]->Position().x - 1 * sizeOfObject * localScaleMatrix1[0], testClass[0]->Position().y, testClass[0]->Position().z);
	asd[1] = GLVector3(testClass[0]->Position().x, testClass[0]->Position().y + 1 * sizeOfObject * localScaleMatrix1[1], testClass[0]->Position().z);
	asd[2] = GLVector3(testClass[0]->Position().x + 1 * sizeOfObject * localScaleMatrix1[0], testClass[0]->Position().y, testClass[0]->Position().z);

	asd2[0] = GLVector3(testClass[1]->Position().x, testClass[1]->Position().y, testClass[1]->Position().z + 1 * sizeOfObject * localScaleMatrix2[0]);
	asd2[1] = GLVector3(testClass[1]->Position().x, testClass[1]->Position().y + 1 * sizeOfObject * localScaleMatrix2[1], testClass[1]->Position().z);
	asd2[2] = GLVector3(testClass[1]->Position().x, testClass[1]->Position().y, testClass[1]->Position().z - 1 * sizeOfObject * localScaleMatrix2[0]);

	distance1[0] = masterMatrix->DistanceBetween3DPosition(asd[0], asd[1]);
	distance1[1] = masterMatrix->DistanceBetween3DPosition(asd[1], asd[2]);
	distance1[2] = masterMatrix->DistanceBetween3DPosition(asd[2], asd[0]);

	distance2[0] = masterMatrix->DistanceBetween3DPosition(asd2[0], asd2[1]);
	distance2[1] = masterMatrix->DistanceBetween3DPosition(asd2[1], asd2[2]);
	distance2[2] = masterMatrix->DistanceBetween3DPosition(asd2[2], asd2[0]);


	printf("%f   %f\n", asd2[0].y, asd2[1].y);


	//localScaleMatrix1[0] = 


	testClass[2]->SetPosition(asd[0]);
	testClass[2]->Rotate(GLVector4(0, 0, 1, 0), 1);;

	testClass[3]->Translate(asd2[0]);
	testClass[3]->Rotate(GLVector4(90, 0, 1, 0), 1);



	//testClass[2]->Translate(GLVector3(100, 0, 0));
	//testClass[3]->Rotate(GLVector4(90, 0, 1, 0), 1);


	//printf("%f %f %f\n", asd[0].x, asd[0].y, asd[0].z);
	printf("%f %f %f\n", masterMatrix->DistanceBetween3DPosition(asd[0], asd[1]), masterMatrix->DistanceBetween3DPosition(asd[1], asd[2]), masterMatrix->DistanceBetween3DPosition(asd[2], asd[0]));

	distance1[0] = masterMatrix->DistanceBetween3DPosition(asd[0], asd[1]);
	distance1[1] = masterMatrix->DistanceBetween3DPosition(asd[1], asd[2]);
	distance1[2] = masterMatrix->DistanceBetween3DPosition(asd[2], asd[0]);

	distance2[0] = masterMatrix->DistanceBetween3DPosition(asd2[0], asd2[1]);
	distance2[1] = masterMatrix->DistanceBetween3DPosition(asd2[1], asd2[2]);
	distance2[2] = masterMatrix->DistanceBetween3DPosition(asd2[2], asd2[0]);

}

void Mouse(int button, int state, int x, int y) {

}

void MouseWheel(int button, int state, int x, int y) {

}

void MouseDrag(int x, int y) {

}

void Keyboard(unsigned char key, int x, int y) {


	if (key == 'a' || key == 'A' || key == 'け') {


		yRotated += 2.0;

	}
	else if (key == 'd' || key == 'D' || key == 'し') {

		yRotated -= 2.0;

	}

	if (key == 'w' || key == 'W' || key == 'じ') {


		localScaleMatrix1[0] += 0.003;
		localScaleMatrix1[1] += 0.003;

		localScaleMatrix2[0] += 0.003;
		localScaleMatrix2[1] += 0.003;

	}
	else if (key == 's' || key == 'S' || key == 'い') {

		localScaleMatrix1[0] -= 0.003;
		localScaleMatrix1[1] -= 0.003;

		localScaleMatrix2[0] -= 0.003;
		localScaleMatrix2[1] -= 0.003;

	}

}
void KeyboardUp(unsigned char key, int x, int y) {


}