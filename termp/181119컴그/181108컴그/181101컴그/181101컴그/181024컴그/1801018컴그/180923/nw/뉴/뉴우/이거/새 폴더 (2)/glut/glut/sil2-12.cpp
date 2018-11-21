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


//declare like this to create object.and use pointer
//GLint cubeList[10];
MasterMatrix* masterMatrix = new MasterMatrix();


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

bool flags[5];
Polygon0 *testClass[5];
Polygon0 *xYLine = new Polygon0();
Polygon0* cube = new Polygon0(masterMatrix);
Polygon0* triangle = new Polygon0(masterMatrix);
DrawingLine* drawingLine = new DrawingLine(masterMatrix);
SpringLine* springLine = new SpringLine(masterMatrix);

double scale = 0.1;
int scaleAniStack = 0;
bool pluss = true;

int angle = 270;

bool flag2 = false;

const static int springNum = 6;

bool drawingLineAnimation = false;
int animationStep = 0;

GLdouble tempDistance[20];


GLVector3 distance0;

int zigzagAnimationStep = 0;

int springAnimationStep = 0;

GLVector3 aaaaasd[22];

bool triangleOrRect = true;

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


	//testClass->DrawCube(30);
	xYLine->DrawXYLine(400, false, false);
	if (flags[0])
	{
		if (triangleOrRect)
		{
			triangle->DrawWireTriangle(25, false, false);
		}
		else
		{
			triangle->DrawCube(25, false, true);

		}


		if (flag2)
		{
			triangle->SetPosition(GLVector3(0 + 92 * sin((PI6 * angle) / 180.0), 0 + 92 * cos((PI6 * angle) / 180.0), 0));
			triangle->Rotate(GLVector4(-angle, 0, 0, 1), 2);
		}

		else
		{
			triangle->Rotate(GLVector4(0, 0, 0, 0), 2);
			triangle->SetPosition(GLVector3(0 + 100 * sin((PI6 * angle) / 180.0), 0 + 100 * cos((PI6 * angle) / 180.0), 0));

		}




		testClass[0]->DrawCircle(100, false, true);


		angle = angle++ % 360;

	}

	if (flags[1])
	{

		if (triangleOrRect)
		{
			triangle->DrawWireTriangle(10, false, false);
		}
		else
		{
			triangle->DrawCube(10, false, true);

		}
		triangle->SetPosition(GLVector3(-180 + angle, 100 * sin(10 * ((angle * PI6) / 180.0)), 0));


		testClass[1]->DrawSineGraph(100, false, true, false);

		angle = angle++ % 360;
	}
	if (flags[2])
	{

		if (triangleOrRect)
		{
			triangle->DrawWireTriangle(10, false, false);
		}
		else
		{
			triangle->DrawCube(10, false, true);

		}


		springLine->ObjectiveRendering();



		if (angle < 180) {
			triangle->SetPosition(GLVector3(
				springLine->vector3List.GetDataOfIndex(springAnimationStep).x + 1 * springLine->size * cos((angle* PI6) / 180.0),
				springLine->vector3List.GetDataOfIndex(springAnimationStep).y + 1 * springLine->size * sin((angle* PI6) / 180.0),
				springLine->vector3List.GetDataOfIndex(springAnimationStep).z)
			);
		}
		else if (angle < 360)
		{

			triangle->SetPosition(GLVector3(
				springLine->vector3List.GetDataOfIndex(springAnimationStep).x + (1 * springLine->size * 0.8) + 1 * springLine->size * 1.8 * cos((angle * PI6) / 180.0),
				springLine->vector3List.GetDataOfIndex(springAnimationStep).y + 1 * springLine->size * 1.8 *  sin((angle* PI6) / 180.0),
				springLine->vector3List.GetDataOfIndex(springAnimationStep).z)
			);

		}


		if (angle >= 360)
		{

			angle = 0;

			springAnimationStep++;
			if (springAnimationStep >= springLine->cycle - 1)
			{
				springAnimationStep = 0;
			}
		}


		angle++;



		//testClass[2]->DrawSpring(50, false, true, false);

	}

	if (flags[3])
	{

		if (triangleOrRect)
		{
			triangle->DrawWireTriangle(10, false, false);
		}
		else
		{
			triangle->DrawCube(10, false, true);

		}

		testClass[3]->DrawZigzag(50, false, true);


		triangle->Translate(GLVector3(
			(aaaaasd[zigzagAnimationStep + 1].x - aaaaasd[zigzagAnimationStep].x) / masterMatrix->DistanceBetween3DPosition(aaaaasd[zigzagAnimationStep + 1], aaaaasd[zigzagAnimationStep]),
			(aaaaasd[zigzagAnimationStep + 1].y - aaaaasd[zigzagAnimationStep].y) / masterMatrix->DistanceBetween3DPosition(aaaaasd[zigzagAnimationStep + 1], aaaaasd[zigzagAnimationStep]),
			(aaaaasd[zigzagAnimationStep + 1].z - aaaaasd[zigzagAnimationStep].z) / masterMatrix->DistanceBetween3DPosition(aaaaasd[zigzagAnimationStep + 1], aaaaasd[zigzagAnimationStep])
		));


		distance0.x += (aaaaasd[zigzagAnimationStep + 1].x - aaaaasd[zigzagAnimationStep].x) / masterMatrix->DistanceBetween3DPosition(aaaaasd[zigzagAnimationStep + 1], aaaaasd[zigzagAnimationStep]);
		distance0.y += (aaaaasd[zigzagAnimationStep + 1].y - aaaaasd[zigzagAnimationStep].y) / masterMatrix->DistanceBetween3DPosition(aaaaasd[zigzagAnimationStep + 1], aaaaasd[zigzagAnimationStep]);



		if (
			fabs(distance0.x) >= fabs((aaaaasd[zigzagAnimationStep + 1].x - aaaaasd[zigzagAnimationStep].x))
			&& fabs(distance0.y) >= fabs((aaaaasd[zigzagAnimationStep + 1].y - aaaaasd[zigzagAnimationStep].y))
			&& fabs(distance0.z) >= fabs((aaaaasd[zigzagAnimationStep + 1].z - aaaaasd[zigzagAnimationStep].z))
			)
		{
			zigzagAnimationStep++;

			distance0 = GLVector3(0, 0, 0);

			if (zigzagAnimationStep >= 12)
			{
				triangle->SetPosition(aaaaasd[0]);
				zigzagAnimationStep = 0;
			}
		}



	}
	if (flags[4])
	{
		drawingLine->ObjectiveRendering();

		if (drawingLineAnimation)
		{
			if (triangleOrRect)
			{
				triangle->DrawWireTriangle(10, false, false);
			}
			else
			{
				triangle->DrawCube(10, false, true);

			}
			if (animationStep == 1)
			{
				triangle->Translate(GLVector3(
					(drawingLine->vector3List.GetDataOfIndex(1).x - drawingLine->vector3List.GetDataOfIndex(0).x) / tempDistance[0],
					(drawingLine->vector3List.GetDataOfIndex(1).y - drawingLine->vector3List.GetDataOfIndex(0).y) / tempDistance[0],
					(drawingLine->vector3List.GetDataOfIndex(1).z - drawingLine->vector3List.GetDataOfIndex(0).z) / tempDistance[0]
				)
				);

				distance0.x += (drawingLine->vector3List.GetDataOfIndex(1).x - drawingLine->vector3List.GetDataOfIndex(0).x) / tempDistance[0];
				distance0.y += (drawingLine->vector3List.GetDataOfIndex(1).y - drawingLine->vector3List.GetDataOfIndex(0).y) / tempDistance[0];
				distance0.z += (drawingLine->vector3List.GetDataOfIndex(1).z - drawingLine->vector3List.GetDataOfIndex(0).z) / tempDistance[0];
				printf("%f\n", distance0.x);

				if (fabs(distance0.x) >= fabs((drawingLine->vector3List.GetDataOfIndex(1).x - drawingLine->vector3List.GetDataOfIndex(0).x))
					&& fabs(distance0.y) >= fabs((drawingLine->vector3List.GetDataOfIndex(1).y - drawingLine->vector3List.GetDataOfIndex(0).y))
					&& fabs(distance0.z) >= fabs((drawingLine->vector3List.GetDataOfIndex(1).z - drawingLine->vector3List.GetDataOfIndex(0).z))
					)
				{


					animationStep = 2;

					distance0 = GLVector3(0, 0, 0);

					triangle->SetPosition(drawingLine->vector3List.GetDataOfIndex(1));


				}


			}
			else if (animationStep == 2)
			{
				triangle->Translate(GLVector3(
					(drawingLine->vector3List.GetDataOfIndex(2).x - drawingLine->vector3List.GetDataOfIndex(1).x) / tempDistance[1],
					(drawingLine->vector3List.GetDataOfIndex(2).y - drawingLine->vector3List.GetDataOfIndex(1).y) / tempDistance[1],
					(drawingLine->vector3List.GetDataOfIndex(2).z - drawingLine->vector3List.GetDataOfIndex(1).z) / tempDistance[1]
				)
				);

				distance0.x += (drawingLine->vector3List.GetDataOfIndex(2).x - drawingLine->vector3List.GetDataOfIndex(1).x) / tempDistance[1];
				distance0.y += (drawingLine->vector3List.GetDataOfIndex(2).y - drawingLine->vector3List.GetDataOfIndex(1).y) / tempDistance[1];
				distance0.z += (drawingLine->vector3List.GetDataOfIndex(2).z - drawingLine->vector3List.GetDataOfIndex(1).z) / tempDistance[1];
				printf("%f\n", distance0.x);

				if (fabs(distance0.x) >= fabs((drawingLine->vector3List.GetDataOfIndex(2).x - drawingLine->vector3List.GetDataOfIndex(1).x))
					&& fabs(distance0.y) >= fabs((drawingLine->vector3List.GetDataOfIndex(2).y - drawingLine->vector3List.GetDataOfIndex(1).y))
					&& fabs(distance0.z) >= fabs((drawingLine->vector3List.GetDataOfIndex(2).z - drawingLine->vector3List.GetDataOfIndex(1).z))
					)
				{


					animationStep = 3;

					distance0 = GLVector3(0, 0, 0);


					triangle->SetPosition(drawingLine->vector3List.GetDataOfIndex(2));

				}

			}
			else if (animationStep == 3)
			{
				triangle->Translate(GLVector3(
					(drawingLine->vector3List.GetDataOfIndex(3).x - drawingLine->vector3List.GetDataOfIndex(2).x) / tempDistance[2],
					(drawingLine->vector3List.GetDataOfIndex(3).y - drawingLine->vector3List.GetDataOfIndex(2).y) / tempDistance[2],
					(drawingLine->vector3List.GetDataOfIndex(3).z - drawingLine->vector3List.GetDataOfIndex(2).z) / tempDistance[2]
				)
				);

				distance0.x += (drawingLine->vector3List.GetDataOfIndex(3).x - drawingLine->vector3List.GetDataOfIndex(2).x) / tempDistance[2];
				distance0.y += (drawingLine->vector3List.GetDataOfIndex(3).y - drawingLine->vector3List.GetDataOfIndex(2).y) / tempDistance[2];
				distance0.z += (drawingLine->vector3List.GetDataOfIndex(3).z - drawingLine->vector3List.GetDataOfIndex(2).z) / tempDistance[2];
				printf("%f\n", distance0.x);

				if (fabs(distance0.x) >= fabs((drawingLine->vector3List.GetDataOfIndex(3).x - drawingLine->vector3List.GetDataOfIndex(2).x))
					&& fabs(distance0.y) >= fabs((drawingLine->vector3List.GetDataOfIndex(3).y - drawingLine->vector3List.GetDataOfIndex(2).y))
					&& fabs(distance0.z) >= fabs((drawingLine->vector3List.GetDataOfIndex(3).z - drawingLine->vector3List.GetDataOfIndex(2).z))
					)
				{


					animationStep = 4;

					distance0 = GLVector3(0, 0, 0);


					triangle->SetPosition(drawingLine->vector3List.GetDataOfIndex(3));

				}

			}
			else if (animationStep == 4)
			{
				triangle->Translate(GLVector3(
					(drawingLine->vector3List.GetDataOfIndex(4).x - drawingLine->vector3List.GetDataOfIndex(3).x) / tempDistance[3],
					(drawingLine->vector3List.GetDataOfIndex(4).y - drawingLine->vector3List.GetDataOfIndex(3).y) / tempDistance[3],
					(drawingLine->vector3List.GetDataOfIndex(4).z - drawingLine->vector3List.GetDataOfIndex(3).z) / tempDistance[3]
				)
				);

				distance0.x += (drawingLine->vector3List.GetDataOfIndex(4).x - drawingLine->vector3List.GetDataOfIndex(3).x) / tempDistance[3];
				distance0.y += (drawingLine->vector3List.GetDataOfIndex(4).y - drawingLine->vector3List.GetDataOfIndex(3).y) / tempDistance[3];
				distance0.z += (drawingLine->vector3List.GetDataOfIndex(4).z - drawingLine->vector3List.GetDataOfIndex(3).z) / tempDistance[3];
				printf("%f\n", distance0.x);

				if (fabs(distance0.x) >= fabs((drawingLine->vector3List.GetDataOfIndex(4).x - drawingLine->vector3List.GetDataOfIndex(3).x))
					&& fabs(distance0.y) >= fabs((drawingLine->vector3List.GetDataOfIndex(4).y - drawingLine->vector3List.GetDataOfIndex(3).y))
					&& fabs(distance0.z) >= fabs((drawingLine->vector3List.GetDataOfIndex(4).z - drawingLine->vector3List.GetDataOfIndex(3).z))
					)
				{


					animationStep = 1;

					distance0 = GLVector3(0, 0, 0);


					triangle->SetPosition(drawingLine->vector3List.GetDataOfIndex(0));

				}

			}

		}
	}



	triangle->Scale(GLVector3(1.0, 1.3, 1));

	triangle->Scale(GLVector3(1.0 + scale * scaleAniStack, 1.0 + scale * scaleAniStack, 1.0 + scale * scaleAniStack));




	if (pluss)
	{
		scaleAniStack++;
	}
	else
	{
		scaleAniStack--;

	}

	if (scaleAniStack >= 6)
	{
		pluss = false;

	}

	else if (scaleAniStack <= 0)
	{
		pluss = true;

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
	printf("d");

	if (zRotated > 360.0) {
		zRotated -= 360.0*floor(zRotated / 360.0);   // Don't allow overflow
	}

	if (yRotated > 360.0) {
		yRotated -= 360.0*floor(yRotated / 360.0);   // Don't allow overflow
	}

	if (xRotated > 360.0) {
		xRotated -= 360.0*floor(xRotated / 360.0);   // Don't allow overflow
	}

	rotateMatrix[0] = yRotated;
	rotateMatrix[1] = 0;
	rotateMatrix[2] = 1;
	rotateMatrix[3] = 0;


	glutPostRedisplay();

	glutTimerFunc(1000 / 60, TimerFunc, 1);
}


void Start() {


	srand((unsigned)time(NULL));
	glMatrixMode(GL_PROJECTION);


	for (int i = 0; i < 5; ++i)
	{

		testClass[i] = new Polygon0(masterMatrix);
	}


}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("x : %d,y : %d\n", x - 400, 300 - y);
		if (flags[4])
		{

			drawingLine->AddPoints(GLVector3(x - 400, 300 - y, 0));
			drawingLine->Confirm();

			triangle->SetPosition(drawingLine->vector3List.GetDataOfIndex(0));

			if (drawingLine->NumberOfPoint() == drawingLine->lineLimit)
			{
				drawingLineAnimation = true;
				animationStep = 1;

				tempDistance[0] = masterMatrix->DistanceBetween3DPosition(drawingLine->vector3List.GetDataOfIndex(0), drawingLine->vector3List.GetDataOfIndex(1));
				tempDistance[1] = masterMatrix->DistanceBetween3DPosition(drawingLine->vector3List.GetDataOfIndex(1), drawingLine->vector3List.GetDataOfIndex(2));
				tempDistance[2] = masterMatrix->DistanceBetween3DPosition(drawingLine->vector3List.GetDataOfIndex(2), drawingLine->vector3List.GetDataOfIndex(3));
				tempDistance[3] = masterMatrix->DistanceBetween3DPosition(drawingLine->vector3List.GetDataOfIndex(3), drawingLine->vector3List.GetDataOfIndex(4));
				distance0 = GLVector3(0, 0, 0);
			}
		}


	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{




	}

}

void MouseWheel(int button, int state, int x, int y) {

}

void MouseDrag(int x, int y) {

}

void Keyboard(unsigned char key, int x, int y) {



	if (key == '0')
	{
		for (int i = 0; i < 5; ++i)
		{

			flags[i] = false;

		}

		if (!flags[0])
		{
			triangle->SetPosition(GLVector3(-100, 0, 0));
			triangle->Scale(GLVector3(1, 1, 1));
			triangle->Rotate(GLVector4(0, 0, 0, 0), 0);
			triangle->Rotate(GLVector4(0, 0, 0, 0), 1);
			triangle->Rotate(GLVector4(0, 0, 0, 0), 2);

			cube->SetPosition(GLVector3(-100, 0, 0));
			cube->Scale(GLVector3(1, 1, 1));
			cube->Rotate(GLVector4(0, 0, 0, 0), 0);
			cube->Rotate(GLVector4(0, 0, 0, 0), 1);
			cube->Rotate(GLVector4(0, 0, 0, 0), 2);

			angle = 270;
			flags[0] = true;
		}


		animationStep = 0;
		springAnimationStep = 0;
		zigzagAnimationStep = 0;
		yRotated = 0;

	}


	else if (key == '1')
	{
		for (int i = 0; i < 5; ++i)
		{
			flags[i] = false;
		}
		if (!flags[1])
		{
			triangle->SetPosition(GLVector3(-200, 0, 0));
			triangle->Scale(GLVector3(1, 1, 1));
			triangle->Rotate(GLVector4(0, 0, 0, 0), 0);
			triangle->Rotate(GLVector4(0, 0, 0, 0), 1);
			triangle->Rotate(GLVector4(0, 0, 0, 0), 2);

			cube->SetPosition(GLVector3(-200, 0, 0));
			cube->Scale(GLVector3(1, 1, 1));
			cube->Rotate(GLVector4(0, 0, 0, 0), 0);
			cube->Rotate(GLVector4(0, 0, 0, 0), 1);
			cube->Rotate(GLVector4(0, 0, 0, 0), 2);


			flags[1] = true;
		}
		animationStep = 0;
		springAnimationStep = 0;
		zigzagAnimationStep = 0;
		yRotated = 0;

	}
	else if (key == '2')
	{
		for (int i = 0; i < 5; ++i)
		{
			flags[i] = false;
		}
		if (!flags[2])
		{
			triangle->SetPosition(GLVector3(springLine->vector3List.GetDataOfIndex(0).x + springLine->size, springLine->vector3List.GetDataOfIndex(0).y, springLine->vector3List.GetDataOfIndex(0).z));
			triangle->Scale(GLVector3(1, 1, 1));
			triangle->Rotate(GLVector4(0, 0, 0, 0), 0);
			triangle->Rotate(GLVector4(0, 0, 0, 0), 1);
			triangle->Rotate(GLVector4(0, 0, 0, 0), 2);


			cube->SetPosition(GLVector3(springLine->vector3List.GetDataOfIndex(0).x + springLine->size, springLine->vector3List.GetDataOfIndex(0).y, springLine->vector3List.GetDataOfIndex(0).z));
			cube->Scale(GLVector3(1, 1, 1));
			cube->Rotate(GLVector4(0, 0, 0, 0), 0);
			cube->Rotate(GLVector4(0, 0, 0, 0), 1);
			cube->Rotate(GLVector4(0, 0, 0, 0), 2);


			angle = 0;
			flags[2] = true;
		}


		animationStep = 0;
		springAnimationStep = 0;
		zigzagAnimationStep = 0;
		yRotated = 0;

	}
	else if (key == '3')
	{
		for (int i = 0; i < 5; ++i)
		{
			flags[i] = false;
		}
		if (!flags[3])
		{
			triangle->SetPosition(GLVector3(0, 0, 0));
			triangle->Scale(GLVector3(1, 1, 1));
			triangle->Rotate(GLVector4(0, 0, 0, 0), 0);
			triangle->Rotate(GLVector4(0, 0, 0, 0), 1);
			triangle->Rotate(GLVector4(0, 0, 0, 0), 2);




			cube->SetPosition(GLVector3(0, 0, 0));
			cube->Scale(GLVector3(1, 1, 1));
			cube->Rotate(GLVector4(0, 0, 0, 0), 0);
			cube->Rotate(GLVector4(0, 0, 0, 0), 1);
			cube->Rotate(GLVector4(0, 0, 0, 0), 2);

			angle = 0;
			flags[3] = true;
		}


		for (int i = 0; i < 4; ++i)
		{

			aaaaasd[3 * i] = GLVector3(50 * 3 * i * 0.5, 0, 0);
			aaaaasd[3 * i + 1] = GLVector3(50 * (3 * i + 1) * 0.5, 3 * 50, 0);
			aaaaasd[3 * i + 2] = GLVector3(50 * (3 * i + 2) * 0.5, -3 * 50, 0);
			aaaaasd[3 * i + 3] = GLVector3(50 * (3 * i + 3) * 0.5, 0, 0);
		}
		distance0 = GLVector3(0, 0, 0);
		animationStep = 0;
		springAnimationStep = 0;
		zigzagAnimationStep = 0;
		yRotated = 0;

	}
	else if (key == '4')
	{
		for (int i = 0; i < 5; ++i)
		{
			flags[i] = false;
		}
		flags[4] = true;

		drawingLine->Initialize();
		drawingLineAnimation = false;



		triangle->SetPosition(GLVector3(0, 0, 0));
		triangle->Scale(GLVector3(1, 1, 1));
		triangle->Rotate(GLVector4(0, 0, 0, 0), 0);
		triangle->Rotate(GLVector4(0, 0, 0, 0), 1);
		triangle->Rotate(GLVector4(0, 0, 0, 0), 2);




		cube->SetPosition(GLVector3(0, 0, 0));
		cube->Scale(GLVector3(1, 1, 1));
		cube->Rotate(GLVector4(0, 0, 0, 0), 0);
		cube->Rotate(GLVector4(0, 0, 0, 0), 1);
		cube->Rotate(GLVector4(0, 0, 0, 0), 2);


		animationStep = 0;
		springAnimationStep = 0;
		zigzagAnimationStep = 0;
		yRotated = 0;


	}
	else if (key == 'y')
	{
		yRotated += 3;
	}
	else if (key == 'Y')
	{
		yRotated -= 3;
	}
	else if (key == 't' || key == 'T')
	{
		flag2 = !flag2;
	}
	else if (key == 'r' || key == 'R')
	{
		triangleOrRect = !triangleOrRect;
	}
}
void KeyboardUp(unsigned char key, int x, int y) {


}