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



	glEnable(GL_CULL_FACE_MODE);



	glCullFace(GL_BACK);


	// clear the identity matrix.
	masterMatrix->glLoadMasterMatrix();



	masterMatrix->glSetMasterMatrix(sample, rotateMatrix, scaleMatrix);

	testClass->DrawXYZLine(viewportData.width, false, false);

	//testClass->DrawCube(30);




	board->DrawBoard(1000, false, true);
	board->SetPosition(0, -300, 0);

	hexahedron->DrawHexahedron(100, false, true, true);
	hexahedron->DrawHexahedron(100, true, false, false);

	hexahedron2->DrawHexahedron(50, false, true, true);
	hexahedron2->DrawHexahedron(50, true, false, false);

	hexahedron3->DrawHexahedron(25, false, true, true);
	hexahedron3->DrawHexahedron(25, true, false, false);


	sphere->DrawWireSphere(100, false, false);




	runningMachine->DrawRunningMachine(30, false, true);


	gymTree->DrawingGymTree(50, false, false);



	runningPeople->DrawingRunningPeople(50, true, false);
	chulbongPeople->DrawingChulbongPeople(50, false, false);

	benchPressPeople->DrawingBenchPressPeople(50, false, false);

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

	static int dir = 1;

	static int temp = 0;



	if (hexahedron->Position().x > 800)
	{



		hexXDir *= -1;

		hexZDir *= -1;


		hexahedron->Translate(5 * hexXDir, 0, 5 * hexZDir);

		hexahedron2->Translate(5 * hexXDir, 0, 5 * hexZDir);
		hexahedron3->Translate(5 * hexXDir, 0, 5 * hexZDir);

	}
	if (hexahedron->Position().x < -800)
	{

		hexXDir *= -1;

		hexZDir *= -1;

		hexahedron->Translate(5 * hexXDir, 0, 5 * hexZDir);

		hexahedron2->Translate(5 * hexXDir, 0, 5 * hexZDir);
		hexahedron3->Translate(5 * hexXDir, 0, 5 * hexZDir);

	}
	if (hexahedron->Position().z > 800)
	{

		hexXDir *= -1;

		hexZDir *= -1;

		hexahedron->Translate(5 * hexXDir, 0, 5 * hexZDir);

		hexahedron2->Translate(5 * hexXDir, 0, 5 * hexZDir);
		hexahedron3->Translate(5 * hexXDir, 0, 5 * hexZDir);
	}
	if (hexahedron->Position().z < -800)
	{

		hexXDir *= -1;

		hexZDir *= -1;
		hexahedron->Translate(5 * hexXDir, 0, 5 * hexZDir);

		hexahedron2->Translate(5 * hexXDir, 0, 5 * hexZDir);
		hexahedron3->Translate(5 * hexXDir, 0, 5 * hexZDir);
	}






	if (sphere->Position().x > 800)
	{
		sphere->SetPosition(800, sphere->Position().y, sphere->Position().z);
		sphereXDir *= -1;
		sphereZDir *= -1;

	}
	if (sphere->Position().x < -800)
	{
		sphere->SetPosition(-800, sphere->Position().y, sphere->Position().z);
		sphereXDir *= -1;
		sphereZDir *= -1;
	}

	if (sphere->Position().z > 800)
	{
		sphere->SetPosition(sphere->Position().x, sphere->Position().y, 800);

		sphereXDir *= -1;
		sphereZDir *= -1;


	}
	if (sphere->Position().z < -800)
	{
		sphere->SetPosition(sphere->Position().x, sphere->Position().y, -800);
		sphereXDir *= -1;
		sphereZDir *= -1;

	}

	for (int i = 0; i < 4; ++i)
	{
		if (CollisionCheck(collisionData[5], collisionData[i]))
		{
			printf("스피어충돌\n");
			sphereXDir *= -1;
			sphereZDir *= -1;
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		if (CollisionCheck(collisionData[6], collisionData[i]))
		{
			printf("크레인충돌\n");
			hexXDir *= -1;
			hexZDir *= -1;
		}
	}
	if (CollisionCheck(collisionData[5], collisionData[6]))
	{
		printf("둘의충돌\n");

		sphereXDir *= -1;
		sphereZDir *= -1;
		sphere->Translate(7 * sphereXDir, 0, 7 * sphereZDir);

		hexXDir *= -1;
		hexZDir *= -1;
		hexahedron->Translate(5 * hexXDir, 0, 5 * hexZDir);

		hexahedron2->Translate(5 * hexXDir, 0, 5 * hexZDir);
		hexahedron3->Translate(5 * hexXDir, 0, 5 * hexZDir);

	}

	hexahedron->Translate(5 * hexXDir, 0, 5 * hexZDir);

	hexahedron2->Translate(5 * hexXDir, 0, 5 * hexZDir);
	hexahedron3->Translate(5 * hexXDir, 0, 5 * hexZDir);


	sphere->Translate(7 * sphereXDir, 0, 7 * sphereZDir);


	sphere->RotateNoGimbalLock(-3 * sphereZDir, 0, -3 * sphereXDir);

	collisionData[5].bottomZ = sphere->Position().z - 50;
	collisionData[5].topZ = sphere->Position().z + 50;
	collisionData[5].leftX = sphere->Position().x - 50;
	collisionData[5].rightX = sphere->Position().x + 50;

	collisionData[6].bottomZ = hexahedron->Position().z - 50;
	collisionData[6].topZ = hexahedron->Position().z + 50;
	collisionData[6].leftX = hexahedron->Position().x - 50;
	collisionData[6].rightX = hexahedron->Position().x + 50;


	ApplyRotate();



	glutPostRedisplay();

	glutTimerFunc(1000 / 60, TimerFunc, 1);
}


void Start()
{


	srand((unsigned)time(NULL));


	masterMatrix->thisCamera.eyeY += 1000.0;
	masterMatrix->thisCamera.eyeZ += 1000.0;


	sphere->rotationAccumulate = true;
	sphere->SetPosition(-200, -100, -300);
	control = hexahedron;
	control->SetPosition(0, -280, 300);
	hexahedron->rotationAccumulate = true;
	hexahedron2->SetPosition(0, -180, 300);
	hexahedron2->Scale(1, 3, 1);
	hexahedron2->rotationAccumulate = true;
	hexahedron3->SetPosition(0, -30, 300);
	hexahedron3->Scale(1, 3, 1);
	hexahedron3->rotationAccumulate = true;







	runningMachine->SetPosition(-600, -150, 600);

	runningPeople->SetPosition(-600, -100, 700);


	chulbongPeople->SetPosition(900, 0, -700);
	benchPressPeople->SetPosition(-800, -200, -700);

	gymTree->SetPosition(800, -200, 800);


	//runningMachine
	collisionData[0].bottomZ = runningMachine->Position().z - 200;
	collisionData[0].topZ = runningMachine->Position().z + 300;
	collisionData[0].leftX = runningMachine->Position().x - 500;
	collisionData[0].rightX = runningMachine->Position().x + 500;




	//chulbongpeople
	collisionData[1].bottomZ = chulbongPeople->Position().z - 50;
	collisionData[1].topZ = chulbongPeople->Position().z + 50;
	collisionData[1].leftX = chulbongPeople->Position().x - 50;
	collisionData[1].rightX = chulbongPeople->Position().x + 50;





	//benchPressPeople
	collisionData[2].bottomZ = benchPressPeople->Position().z - 250;
	collisionData[2].topZ = benchPressPeople->Position().z + 250;
	collisionData[2].leftX = benchPressPeople->Position().x - 250;
	collisionData[2].rightX = benchPressPeople->Position().x + 250;


	//gymTree
	collisionData[3].bottomZ = gymTree->Position().z - 100;
	collisionData[3].topZ = gymTree->Position().z + 100;
	collisionData[3].leftX = gymTree->Position().x - 100;
	collisionData[3].rightX = gymTree->Position().x + 100;



	sphereZDir = 0;
	hexZDir = 0;




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
		controls[controlPointer++] = false;
		controlPointer = controlPointer % 2;
		controls[controlPointer] = true;


	}
	if (key == 'd')
	{

		if (controls[0])
		{
			sphereXDir = 1;
			sphereZDir = 0;
		}
		else if (controls[1])
		{
			hexXDir = 1;
			hexZDir = 0;
		}
	}
	if (key == 'a')
	{
		if (controls[0])
		{
			sphereXDir = -1;
			sphereZDir = 0;
		}
		else if (controls[1])
		{
			hexXDir = -1;
			hexZDir = 0;
		}
	}
	if (key == 'w')
	{
		if (controls[0])
		{
			sphereXDir = 0;
			sphereZDir = -1;
		}
		else if (controls[1])
		{
			hexXDir = 0;
			hexZDir = -1;
		}
	}
	if (key == 's')
	{
		if (controls[0])
		{
			sphereXDir = 0;
			sphereZDir = 1;
		}
		else if (controls[1])
		{
			hexXDir = 0;
			hexZDir = 1;
		}
	}
	if (key == 'S')
	{



	}

	if (key == 'b')
	{

		hexahedron->RotateNoGimbalLock(0, 5, 0);
		hexahedron2->RotateNoGimbalLock(0, 5, 0);
		hexahedron3->RotateNoGimbalLock(0, 5, 0);


	}
	if (key == 'B')
	{
		hexahedron->RotateNoGimbalLock(0, -5, 0);
		hexahedron2->RotateNoGimbalLock(0, -5, 0);
		hexahedron3->RotateNoGimbalLock(0, -5, 0);

	}

	if (key == 'k')
	{
		if (hexahedron3->currentXRotateMatrix[0] < 90)
		{
			hexahedron3->Rotate2(5, 1, 0, 0, 0);
		}
	}
	if (key == 'K')
	{
		if (hexahedron3->currentXRotateMatrix[0] > -90)
		{
			hexahedron3->Rotate2(-5, 1, 0, 0, 0);
		}

	}

	if (key == 'm')
	{
		hexahedron2->RotateNoGimbalLock(0, 5, 0);
		hexahedron3->RotateNoGimbalLock(0, 5, 0);









	}
	if (key == 'M')
	{




		hexahedron2->RotateNoGimbalLock(0, -5, 0);
		hexahedron3->RotateNoGimbalLock(0, -5, 0);


	}

	if (key == 'l')
	{

		if (hexahedron3->currentZRotateMatrix[0] < 90)
		{
			hexahedron3->Rotate2(5, 0, 0, 1, 2);
		}

	}
	if (key == 'L')
	{
		if (hexahedron3->currentZRotateMatrix[0] > -90)
		{
			hexahedron3->Rotate2(-5, 0, 0, 1, 2);
		}


	}
	if (key == 'N')
	{
		if (hexahedron2->currentXRotateMatrix[0] < 90)
		{
			hexahedron2->Rotate2(5, 1, 0, 0, 0);

			hexahedron3->SetFreeRotateXAxis(GLVector3(0, -150, 0), GLVector3(20, -150, 0));
			hexahedron3->SetFreeRotateYAxis(GLVector3(0, -150, 0), GLVector3(0, 20 - 150, 0));
			hexahedron3->SetFreeRotateZAxis(GLVector3(0, -150, 0), GLVector3(0, 0 - 150, 20));
			hexahedron3->freeAxisRotate = true;
			hexahedron3->FreeAxisRotate2(5, 0, 0);
		}





	}
	if (key == 'n')
	{
		if (hexahedron2->currentXRotateMatrix[0] > -90)
		{
			hexahedron2->Rotate2(-5, 1, 0, 0, 0);

			hexahedron3->SetFreeRotateXAxis(GLVector3(0, -150, 0), GLVector3(20, -150, 0));
			hexahedron3->SetFreeRotateYAxis(GLVector3(0, -150, 0), GLVector3(0, 20 - 150, 0));
			hexahedron3->SetFreeRotateZAxis(GLVector3(0, -150, 0), GLVector3(0, 0 - 150, 20));
			hexahedron3->freeAxisRotate = true;
			hexahedron3->FreeAxisRotate2(-5, 0, 0);

		}
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