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
void Menu(int);

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
Polygon0 *bigSphere;
Polygon0 *bigPath[3];
Polygon0 *smallPath[3];
Polygon0 *middleSattellite[3];
Polygon0 *smallSattellite[3];

bool leftRotate = false;
bool rightRotate = false;

bool bothRotate = false;

bool temp[4];
int poolingNum = 0;
bool projection = false;
bool wireOption = true;

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
	int SubMenu1, SubMenu2, SubMenu3; int MainMenu;


	glutInit(&argc, argv);



	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("glutBase");
	//initLighting();

	xRotated = yRotated = zRotated = 0.0;
	SubMenu1 = glutCreateMenu(Menu);
	glutAddMenuEntry("Solid", 1);
	glutAddMenuEntry("Wire", 2);



	glutAttachMenu(GLUT_RIGHT_BUTTON);
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


	bigSphere->DrawSphere(100, false, false,wireOption);
	bigPath[0]->DrawCircle(250, false, false);
	bigPath[0]->Rotate(90, 1, 0, 0, 0);


	bigPath[1]->DrawCircle(250, false, false);
	bigPath[1]->Rotate(90, 0, 1, 0, 1);
	bigPath[1]->axisRotate = true;
	bigPath[1]->AxisRotate(45, 0, 0, 1, 2);

	bigPath[2]->DrawCircle(250, false, false);
	bigPath[2]->Rotate(90, 0, 1, 0, 1);
	bigPath[2]->axisRotate = true;
	bigPath[2]->AxisRotate(135, 0, 0, 1, 2);


	middleSattellite[0]->DrawSphere(30, false, false, wireOption);
	middleSattellite[0]->SetPosition(-250, 0, 0);
	middleSattellite[0]->axisRotate = true;
	middleSattellite[0]->AxisRotate2(1, 0, 1, 0, 1);




	middleSattellite[1]->DrawSphere(30, false, false, wireOption);
	middleSattellite[1]->SetPosition(-250, 0, 0);
	middleSattellite[1]->axisRotate = true;
	middleSattellite[1]->AxisRotate(45, 0, 0, 1, 2);
	middleSattellite[1]->AxisRotate2(2, -1, 1, 0, 1);





	middleSattellite[2]->DrawSphere(30, false, false, wireOption);
	middleSattellite[2]->SetPosition(-250, 0, 0);
	middleSattellite[2]->axisRotate = true;
	middleSattellite[2]->AxisRotate(315, 0, 0, 1, 2);
	middleSattellite[2]->AxisRotate2(2, 1, 1, 0, 1);


	smallPath[0]->DrawCircle(75, false, true);
	smallPath[0]->SetPosition(-250, 0, 0);
	smallPath[0]->Rotate(90, 1, 0, 0, 0);
	smallPath[0]->axisRotate = true;
	smallPath[0]->AxisRotate2(1, 0, 1, 0, 1);



	smallPath[1]->DrawCircle(75, false, true);
	smallPath[1]->SetPosition(-250, 0, 0);
	smallPath[1]->Rotate(90, 1, 0, 0, 0);
	smallPath[1]->axisRotate = true;
	smallPath[1]->AxisRotate(45, 0, 0, 1, 2);
	smallPath[1]->AxisRotate2(2, -1, 1, 0, 1);


	smallPath[2]->DrawCircle(75, false, true);
	smallPath[2]->SetPosition(-250, 0, 0);
	smallPath[2]->Rotate(90, 1, 0, 0, 0);
	smallPath[2]->axisRotate = true;
	smallPath[2]->AxisRotate(315, 0, 0, 1, 2);
	smallPath[2]->AxisRotate2(2, 1, 1, 0, 1);


	smallSattellite[0]->DrawSphere(15, false, false, wireOption);
	smallSattellite[0]->SetPosition(-250 - 75, 0, 0);
	smallSattellite[0]->axisRotate = true;


	//smallSattellite[0]->SetAxisTranslate(-250 + 250 * sin((smallPath[0]->axisYRotateMatrix[0]) * PI6 / 180.0), 0 , 0 + 250 * cos((smallPath[0]->axisYRotateMatrix[0]) * PI6 / 180.0));

	smallSattellite[0]->AxisRotate2(1, 0, 1, 0, 1);




	smallSattellite[1]->DrawSphere(15, false, false, wireOption);
	smallSattellite[1]->SetPosition(-250 - 75, 0, 0);
	smallSattellite[1]->axisRotate = true;
	smallSattellite[1]->AxisRotate(45, 0, 0, 1, 2);
	smallSattellite[1]->AxisRotate2(2, -1, 1, 0, 1);





	smallSattellite[2]->DrawSphere(15, false, false, wireOption);
	smallSattellite[2]->SetPosition(-250 - 75, 0, 0);
	smallSattellite[2]->axisRotate = true;
	smallSattellite[2]->AxisRotate(315, 0, 0, 1, 2);
	smallSattellite[2]->AxisRotate2(2, 1, 1, 0, 1);





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
	printf("d");



	static double temp = 0;




	ApplyRotate();



	glutPostRedisplay();

	glutTimerFunc(1000 / 60, TimerFunc, 1);
}


void Start()
{


	srand((unsigned)time(NULL));

	for (int i = 0; i < 3; ++i)
	{
		bigPath[i] = new Polygon0(masterMatrix);
		smallPath[i] = new Polygon0(masterMatrix);
		smallSattellite[i] = new Polygon0(masterMatrix);
		middleSattellite[i] = new Polygon0(masterMatrix);

	}

	bigSphere = new Polygon0(masterMatrix);


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
	if (key == 'w' || key == 'W')
	{

		masterMatrix->thisCamera.eyeY += 2.0;


	}

	if (key == 'a' || key == 'A')
	{


		masterMatrix->thisCamera.eyeX -= 2.0;

	}

	if (key == 's' || key == 'S')
	{

		masterMatrix->thisCamera.eyeY -= 2.0;



	}
	if (key == 'd' || key == 'D')
	{

		masterMatrix->thisCamera.eyeX += 2.0;



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

	if (key == 'i' || key == 'I')
	{

		zRotated = 0;
		xRotated = 0;
		yRotated = 0;
		masterMatrix->thisCamera.eyeX = 0;
		masterMatrix->thisCamera.eyeY = 0;
		masterMatrix->thisCamera.eyeZ = 400;
	}

	if (key == '-')
	{

		masterMatrix->thisCamera.eyeZ -= 2.0;

	}

	else if (key == '+')
	{

		masterMatrix->thisCamera.eyeZ += 2.0;

	}

	if (key == 'o')
	{
		projection = !projection;
		printf("asd%d\n", projection);
		masterMatrix = new MasterMatrix(projection);

		zRotated = 0;
		xRotated = 0;
		yRotated = 0;
		masterMatrix->thisCamera.eyeX = 0;
		masterMatrix->thisCamera.eyeY = 0;
		masterMatrix->thisCamera.eyeZ = 400;


		bigSphere->masterMatrixs = masterMatrix;
		for (int i = 0; i < 3; ++i)
		{
			bigPath[i]->masterMatrixs = masterMatrix;
			smallPath[i]->masterMatrixs = masterMatrix;
			smallSattellite[i]->masterMatrixs = masterMatrix;
			middleSattellite[i]->masterMatrixs = masterMatrix;

		}

	}

}
void KeyboardUp(unsigned char key, int x, int y)
{


}


void Menu(int button)
{
	switch (button)
	{
		case 1: 
			wireOption = false;
			break;
		case 2:  
			wireOption = true;
			break;
		case 11:  break;
	}
	glutPostRedisplay();
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