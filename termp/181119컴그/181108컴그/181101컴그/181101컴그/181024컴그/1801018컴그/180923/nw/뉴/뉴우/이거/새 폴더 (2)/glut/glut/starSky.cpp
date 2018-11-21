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



MasterMatrix* masterMatrix = new MasterMatrix(false);

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



bool LiangBarsky(double edgeLeft, double edgeRight, double edgeBottom, double edgeTop,   // Define the x/y clipping values for the border.
	double x0src, double y0src, double x1src, double y1src,                 // Define the start and end points of the line.
	double &x0clip, double &y0clip, double &x1clip, double &y1clip);       // The output values, so declare these outside.





double aaa[4];


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



int worldMousePositionX = 0;
int worldMousePositionY = 0;

bool downUp = false;

int CheckCollisions();

//
//
//only for temporary
const int triangleNum = 18;
Polygon0* triangles[triangleNum];
const int rectangleNum = 2;
Polygon0* rectangles[rectangleNum];

Polygon0* rectangles2[rectangleNum];
bool rectangles2Activate[rectangleNum] = { true,true };

const int sliceTriangleNum = 10;
Polygon0* sliceTriangles[sliceTriangleNum];
Polygon0* sliceTriangles2[sliceTriangleNum];
bool noSTCollision[sliceTriangleNum];


const int fallingTriangleNum = 50;
Polygon0* fallingTriangles[fallingTriangleNum];


const int greedNum = 2;
Greed* greed[greedNum];


int poolingNum = 0;


struct SelfAnimation
{

	int keyFrame;
	int currentFrame;
	bool loop;
	bool activate;

	//Polygon0* target
	int targetIndex;
	int xDir;
	int yDir;
	int distance;
	bool canPick;

};
//슬슬 변수명 짓기가 귀찮아
SelfAnimation leftRightMoveParameter[sliceTriangleNum];



void LeftRightMove(SelfAnimation*);
void ParameterInitialize(int);







DraggingLine* draggingLine;


bool leftRotate = false;
bool rightRotate = false;

bool bothRotate = false;

bool temp[4];
//int poolingNum = 0;

GLAnimator* asd = new GLAnimator();
GLAnimator* asd2 = new GLAnimator();



bool starCollisionChecked[triangleNum * 5];


struct PhysicsStruct
{

	double acceleration = 0;
	double gravitationalAcceleration = 9.8;
	double speed = 50;
	GLVector2 velocity = GLVector2(0, 0);
	int dir = 1;
	int timeOfFrame = 0;

	double theta = 0;

};



void ParabolicMotion(PhysicsStruct* physicStruct);
void ParabolicMotionInitialize(PhysicsStruct* physicStruct);


PhysicsStruct physicsStruct[4];



int starPoolingNum = 0;
Star* star[triangleNum * 5];
GLVector4 tempColor = GLVector4(1, 1, 1, 1);


struct LinearMoveStruct
{
	GLVector2 point1 = GLVector2(0, 0);
	GLVector2 point2 = GLVector2(0, 0);
	double t = 0;

};
LinearMoveStruct linearMoveStruct[triangleNum * 5];




void LinearMove(Polygon0* target, LinearMoveStruct *linearMoveStruct);







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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_ALPHA);
	//glAlphaFunc()

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

	for (int i = 0; i < triangleNum; ++i)
	{
		triangles[i]->DrawTriangle(20, false, true);
		triangles[i]->Translate(1, 0, 0);

		if (triangles[i]->Position().x > 440)
		{
			triangles[i]->SetPosition(-460, 380, 0);
			triangles[i]->Rotate(rand() % 360, 0, 0, 1, 2);
			triangles[i]->objectActivate = true;
		}

		triangles[i]->Rotate2(1, 0, 0, 1, 2);
	}

	for (int i = 0; i < rectangleNum; ++i)
	{

		rectangles[i]->DrawHexahedron(20, false, true, false);

		rectangles[i]->Translate(0, 1, 0);
		rectangles[i]->Rotate2(1, 1, 1, 1, 0);



	}

	for (int i = 0; i < rectangleNum; ++i)
	{
		if (rectangles2Activate[i])
		{
			rectangles2[i]->DrawRectangle(20, false, true);
		}


		rectangles2[i]->Translate(0, 5, 0);


		if (rectangles2[i]->Position().y > 420)
		{

			rectangles2[i]->SetPosition(0, -1200, 0);
			rectangles2[i]->Rotate(45 * (rand() % 2), 0, 0, 1, 2);
			rectangles2Activate[i] = true;
		}

	}

	for (int i = 0; i < sliceTriangleNum; ++i)
	{

		sliceTriangles[i]->DrawTriangle(25, false, false);



	}


	draggingLine->DrawDraggingLine(false, false);


	for (int i = 0; i < greedNum; ++i)
	{
		greed[i]->DrawGreed();


	}




	for (int i = 0; i < triangleNum * 5; ++i)
	{

		if (star[i]->objectActivate)
		{
			star[i]->Rotate2(2, 0, 0, 1, 2);
			star[i]->DrawingStar(5, false, false);

		}

	}

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



	//asd->AlphaBlendingAnimation(rectangles2[0]);
	//asd2->AlphaBlendingAnimation(triangles[4]);



	ApplyRotate();
	if (draggingLine->onMyMouse)
	{
		for (int i = 0; i < rectangleNum; ++i)
		{
			if (LiangBarsky(rectangles2[i]->Position().x - rectangles2[i]->size, rectangles2[i]->Position().x + rectangles2[i]->size, rectangles2[i]->Position().y - rectangles2[i]->size,
				rectangles2[i]->Position().y + rectangles2[i]->size, draggingLine->startPoint.x, draggingLine->startPoint.y, draggingLine->endPoint.x, draggingLine->endPoint.y, aaa[0], aaa[1], aaa[2], aaa[3]))
			{
				printf("우리 정글 도대체 뭐함\n");





			}
		}
	}

	for (int i = 0; i < sliceTriangleNum; ++i)
	{
		/*
		if (leftRightMoveParameter[i].activate)
		{
			LeftRightMove(&leftRightMoveParameter[i]);

		}

		*/
		ParabolicMotion(&physicsStruct[i]);
		sliceTriangles[i]->Translate(physicsStruct[i].velocity.x * 0.5, physicsStruct[i].velocity.y* 0.5, 0);



		if (sliceTriangles[i]->Position().y < -800)
		{
			sliceTriangles[i]->SetPosition(0, -1000, 0);
		}

	}

	for (int i = 0; i < greedNum; ++i)
	{
		for (int j = 0; j < sliceTriangleNum; ++j)
		{
			if (LiangBarsky(greed[i]->Position().x, greed[i]->Position().x + greed[i]->greedData.width, greed[i]->Position().y, greed[i]->Position().y + greed[i]->greedData.height
				, sliceTriangles[j]->Position().x - sliceTriangles[i]->size, sliceTriangles[j]->Position().y - sliceTriangles[i]->size, sliceTriangles[j]->Position().x + sliceTriangles[i]->size, sliceTriangles[j]->Position().y + sliceTriangles[i]->size
				, aaa[0], aaa[1], aaa[2], aaa[3])
				)
			{


				printf("그리드와 충돌\n");

				if (!noSTCollision[j])
				{

					greed[i]->FillTriangle();

					noSTCollision[j] = true;

				}
			}
		}
	}

	for (int i = 0; i < sliceTriangleNum; ++i)
	{
		for (int j = 0; j < triangleNum; ++j)
		{
			if (LiangBarsky(sliceTriangles[i]->Position().x, sliceTriangles[i]->Position().x + sliceTriangles[i]->size, sliceTriangles[i]->Position().y, sliceTriangles[i]->Position().y + sliceTriangles[i]->size
				, triangles[j]->Position().x - triangles[i]->size, triangles[j]->Position().y - triangles[i]->size, triangles[j]->Position().x + triangles[i]->size, triangles[j]->Position().y + triangles[i]->size
				, aaa[0], aaa[1], aaa[2], aaa[3])
				)
			{
				if (triangles[j]->objectActivate)
				{

					printf("상단부 삼각형과 충돌 %d\n", j);

					if (!noSTCollision[i])
					{

						triangles[j]->objectActivate = false;
						sliceTriangles[i]->objectActivate = false;

						noSTCollision[i] = true;

						linearMoveStruct[starPoolingNum].point1.x = triangles[j]->Position().x;
						linearMoveStruct[starPoolingNum].point1.y = triangles[j]->Position().y;
						linearMoveStruct[starPoolingNum].t = 0;


						starCollisionChecked[starPoolingNum] = false;
						

						star[poolingNum]->Scale(1, 1, 1);
						star[starPoolingNum]->color4D = GLVector4((rand() % 11) / 10.0, (rand() % 11) / 10.0, (rand() % 11) / 10.0, 1);
						star[starPoolingNum]->SetPosition(triangles[j]->Position());
						star[starPoolingNum++]->objectActivate = true;

						if (starPoolingNum >= triangleNum * 5)
						{
							starPoolingNum = 0;
						}

					}

				}
			}
		}
	}


	for (int i = 0; i < triangleNum * 5; ++i)
	{
		if (star[i]->objectActivate)
		{
			LinearMove(star[i], &linearMoveStruct[i]);
			//printf("%f %f\n", star[i]->Position().x, star[i]->Position().y);

			if (starCollisionChecked[i] == false)
			{
				for (int j = i + 1; j < triangleNum * 5; ++j)
				{
					if (starCollisionChecked[j] == false)
					{

						if (LiangBarsky(star[i]->Position().x - (25 * star[i]->currentScaleMatrix[0]), star[i]->Position().x + (25 * star[i]->currentScaleMatrix[0]), star[i]->Position().y - (25 * star[i]->currentScaleMatrix[1]), star[i]->Position().y + (25 * star[i]->currentScaleMatrix[1]),
							star[j]->Position().x - (25 * star[j]->currentScaleMatrix[0]), star[j]->Position().y - (25 * star[j]->currentScaleMatrix[1]), star[j]->Position().x + (25 * star[j]->currentScaleMatrix[0]), star[j]->Position().y + (25 * star[j]->currentScaleMatrix[1])
							, aaa[0], aaa[1], aaa[2], aaa[3])
							)
						{

							star[i]->Scale(1.5, 1.5, 1);
							star[j]->Scale(1.5, 1.5, 1);
							tempColor = GLVector4(star[i]->color4D.x, star[i]->color4D.y, star[i]->color4D.z, star[i]->color4D.w);
							
							star[i]->color4D.x += star[j]->color4D.x;
							star[i]->color4D.y += star[j]->color4D.y;
							star[i]->color4D.z *= star[j]->color4D.z;

							star[j]->color4D.x += tempColor.x;
							star[j]->color4D.y += tempColor.y;
							star[j]->color4D.z += tempColor.z;





							starCollisionChecked[i] = true;
							starCollisionChecked[j] = true;
						}
					}
				}


			}

		}
	}



	glutPostRedisplay();

	glutTimerFunc(1000 / 60, TimerFunc, 1);
}


void Start()
{


	srand((unsigned)time(NULL));



	for (int i = 0; i < triangleNum; ++i)
	{

		triangles[i] = new Polygon0(masterMatrix);

		triangles[i]->SetPosition(-440 + i * 50, 380, 0);
		triangles[i]->Rotate(rand() % 360, 0, 0, 1, 2);
		//triangles[i]->alpha = 0.5;
	}


	for (int i = 0; i < rectangleNum; ++i)
	{

		rectangles[i] = new Polygon0(masterMatrix);

		rectangles[i]->SetPosition(0, -400 + i * 40, 0);

		rectangles[i]->Rotate(45 * rand() % 2, 0, 0, 1, 2);


	}
	draggingLine = new DraggingLine(masterMatrix);

	for (int i = 0; i < rectangleNum; ++i)
	{
		rectangles2[i] = new Polygon0(masterMatrix);

		rectangles2[i]->SetPosition(0, 0 - i * 800, 0);

		rectangles2[i]->Rotate(45 * (rand() % 2), 0, 0, 1, 2);

	}



	for (int i = 0; i < sliceTriangleNum; ++i)
	{

		sliceTriangles[i] = new Polygon0(masterMatrix);
		sliceTriangles[i]->SetPosition(0, -1600, 0);

		ParameterInitialize(i);

	}


	for (int i = 0; i < greedNum; ++i)
	{
		greed[i] = new Greed(masterMatrix);

		greed[i]->SetPosition(-400 + (i * 500), -400, 0);

	}



	for (int i = 0; i < triangleNum * 5; ++i)
	{
		star[i] = new Star(masterMatrix);
		star[i]->objectActivate = false;
		star[i]->SetPosition(0, -1200, 0);

		linearMoveStruct[i].point2 = GLVector2((rand() % 500) - 200, (rand() % 500) - 200);

		starCollisionChecked[i] = false;

	}




}

void Mouse(int button, int state, int x, int y)
{

	worldMousePositionX = x - (800 / 2);
	worldMousePositionY = (800 / 2) - y;

	static int randomTemp = 0;
	static int randomTemp2 = 0;

	if (button == 0)
	{

		if (downUp == false)
		{
			downUp = true;
			draggingLine->Enable();
			printf("%d down\n", downUp);
		}

		else if (downUp == true)
		{
			downUp = false;
			printf("ㄴㅁㄴㅇ");
			draggingLine->Disable();
			printf("%d up\n", downUp);

			for (int i = 0; i < rectangleNum; ++i)
			{
				if (rectangles2Activate[i])
				{

					if (LiangBarsky(rectangles2[i]->Position().x - rectangles2[i]->size, rectangles2[i]->Position().x + rectangles2[i]->size, rectangles2[i]->Position().y - rectangles2[i]->size,
						rectangles2[i]->Position().y + rectangles2[i]->size, draggingLine->startPoint.x, draggingLine->startPoint.y, draggingLine->endPoint.x, draggingLine->endPoint.y, aaa[0], aaa[1], aaa[2], aaa[3]))
					{
						printf("짤라\n");

						noSTCollision[2 * i] = false;
						noSTCollision[2 * i + 1] = false;

						if (draggingLine->startPoint.x >= rectangles2[i]->Position().x - rectangles2[i]->size &&
							draggingLine->startPoint.x <= rectangles2[i]->Position().x + rectangles2[i]->size)
						{

							printf("수직가르기\n");

							if (i == 0)
							{

								ParameterInitialize(0);
								leftRightMoveParameter[0].activate = true;
								sliceTriangles[0]->objectActivate = true;
								ParabolicMotionInitialize(&physicsStruct[0]);
								physicsStruct[0].dir = -1;


								ParameterInitialize(1);
								leftRightMoveParameter[1].activate = true;
								sliceTriangles[1]->objectActivate = true;
								ParabolicMotionInitialize(&physicsStruct[1]);



								sliceTriangles[0]->SetPosition(rectangles2[i]->Position().x, rectangles2[i]->Position().y, 0);
								if (((int)rectangles2[i]->currentZRotateMatrix[0] % 90 == 45))
								{
									sliceTriangles[0]->Rotate(90, 0, 0, 1, 2);

									leftRightMoveParameter[0].xDir = -1;
								}

								else
								{
									sliceTriangles[0]->Rotate(135, 0, 0, 1, 2);
									leftRightMoveParameter[0].xDir = -1;
								}



								sliceTriangles[1]->SetPosition(rectangles2[i]->Position().x, rectangles2[i]->Position().y, 0);
								if (((int)rectangles2[i]->currentZRotateMatrix[0] % 90 == 45))
								{

									sliceTriangles[1]->Rotate(270, 0, 0, 1, 2);

									leftRightMoveParameter[1].xDir = 1;
								}

								else
								{
									sliceTriangles[1]->Rotate(-45, 0, 0, 1, 2);
									leftRightMoveParameter[1].xDir = 1;
								}


								rectangles2Activate[i] = false;

							}

							else if (i == 1)

							{

								ParameterInitialize(2);
								leftRightMoveParameter[2].activate = true;
								sliceTriangles[2]->objectActivate = true;

								ParabolicMotionInitialize(&physicsStruct[2]);
								physicsStruct[2].dir = -1;



								ParameterInitialize(3);
								leftRightMoveParameter[3].activate = true;
								sliceTriangles[3]->objectActivate = true;

								ParabolicMotionInitialize(&physicsStruct[3]);


								sliceTriangles[2]->SetPosition(rectangles2[i]->Position().x, rectangles2[i]->Position().y, 0);


								if (((int)rectangles2[i]->currentZRotateMatrix[0] % 90 == 45))
								{
									sliceTriangles[2]->Rotate(90, 0, 0, 1, 2);

									leftRightMoveParameter[2].xDir = -1;
								}

								else
								{
									sliceTriangles[2]->Rotate(135, 0, 0, 1, 2);

									leftRightMoveParameter[2].xDir = -1;
								}





								sliceTriangles[3]->SetPosition(rectangles2[i]->Position().x, rectangles2[i]->Position().y, 0);
								if (((int)rectangles2[i]->currentZRotateMatrix[0] % 90 == 45))
								{
									sliceTriangles[3]->Rotate(270, 0, 0, 1, 2);

									leftRightMoveParameter[3].xDir = 1;
								}

								else
								{
									sliceTriangles[3]->Rotate(-45, 0, 0, 1, 2);
									leftRightMoveParameter[3].xDir = 1;
								}

								rectangles2Activate[i] = false;

							}

						}

						else if (draggingLine->startPoint.y >= rectangles2[i]->Position().y - rectangles2[i]->size &&
							draggingLine->startPoint.y <= rectangles2[i]->Position().y + rectangles2[i]->size)
						{
							printf("수평가르기\n");

							if (i == 0)
							{

								ParameterInitialize(0);
								leftRightMoveParameter[0].activate = true;
								sliceTriangles[0]->objectActivate = true;


								ParabolicMotionInitialize(&physicsStruct[0]);
								physicsStruct[0].dir = -1;



								ParameterInitialize(1);
								leftRightMoveParameter[1].activate = true;
								sliceTriangles[1]->objectActivate = true;


								ParabolicMotionInitialize(&physicsStruct[1]);



								sliceTriangles[0]->SetPosition(rectangles2[i]->Position().x, rectangles2[i]->Position().y, 0);
								if (((int)rectangles2[i]->currentZRotateMatrix[0] % 90 == 45))
								{
									sliceTriangles[0]->Rotate(180, 0, 0, 1, 2);
									leftRightMoveParameter[0].xDir = 1;
								}

								else
								{
									sliceTriangles[0]->Rotate(225, 0, 0, 1, 2);
									leftRightMoveParameter[0].xDir = 1;
								}

								sliceTriangles[1]->SetPosition(rectangles2[i]->Position().x, rectangles2[i]->Position().y, 0);
								if (((int)rectangles2[i]->currentZRotateMatrix[0] % 90 == 45))
								{

									sliceTriangles[1]->Rotate(0, 0, 0, 1, 2);
									leftRightMoveParameter[1].xDir = -1;
								}

								else
								{
									sliceTriangles[1]->Rotate(45, 0, 0, 1, 2);
									leftRightMoveParameter[1].xDir = -1;
								}


								rectangles2Activate[i] = false;

							}

							else if (i == 1)

							{

								ParameterInitialize(2);
								leftRightMoveParameter[2].activate = true;
								sliceTriangles[2]->objectActivate = true;

								ParabolicMotionInitialize(&physicsStruct[2]);
								physicsStruct[2].dir = -1;



								ParameterInitialize(3);
								leftRightMoveParameter[3].activate = true;
								sliceTriangles[3]->objectActivate = true;
								ParabolicMotionInitialize(&physicsStruct[3]);



								sliceTriangles[2]->SetPosition(rectangles2[i]->Position().x, rectangles2[i]->Position().y, 0);
								if (((int)rectangles2[i]->currentZRotateMatrix[0] % 90 == 45))
								{
									sliceTriangles[2]->Rotate(180, 0, 0, 1, 2);
									leftRightMoveParameter[2].xDir = 1;
								}

								else
								{
									sliceTriangles[2]->Rotate(225, 0, 0, 1, 2);
									leftRightMoveParameter[2].xDir = 1;
								}

								sliceTriangles[3]->SetPosition(rectangles2[i]->Position().x, rectangles2[i]->Position().y, 0);
								if (((int)rectangles2[i]->currentZRotateMatrix[0] % 90 == 45))
								{
									sliceTriangles[3]->Rotate(0, 0, 0, 1, 2);
									leftRightMoveParameter[3].xDir = -1;
								}

								else
								{
									sliceTriangles[3]->Rotate(45, 0, 0, 1, 2);
									leftRightMoveParameter[3].xDir = -1;
								}



								rectangles2Activate[i] = false;

							}

						}

						else
						{
							printf("랜덤\n");
							randomTemp2 = rand() % 2;
							randomTemp = -90 * (randomTemp2);

							if (i == 0)
							{

								ParameterInitialize(0);
								leftRightMoveParameter[0].activate = true;
								sliceTriangles[0]->objectActivate = true;

								ParabolicMotionInitialize(&physicsStruct[0]);
								physicsStruct[0].dir = -1;



								ParameterInitialize(1);
								leftRightMoveParameter[1].activate = true;
								sliceTriangles[1]->objectActivate = true;

								ParabolicMotionInitialize(&physicsStruct[1]);




								sliceTriangles[0]->SetPosition(rectangles2[i]->Position().x, rectangles2[i]->Position().y, 0);
								if (((int)rectangles2[i]->currentZRotateMatrix[0] % 90 == 45))
								{
									sliceTriangles[0]->Rotate(180 + randomTemp, 0, 0, 1, 2);
									if (randomTemp2 == 0)
									{
										leftRightMoveParameter[0].xDir = 1;
									}
									else
									{

										leftRightMoveParameter[0].xDir = -1;
									}
								}

								else
								{
									sliceTriangles[0]->Rotate(225 + randomTemp, 0, 0, 1, 2);
									if (randomTemp2 == 0)
									{
										leftRightMoveParameter[0].xDir = 1;
									}
									else
									{

										leftRightMoveParameter[0].xDir = -1;
									}
								}

								sliceTriangles[1]->SetPosition(rectangles2[i]->Position().x, rectangles2[i]->Position().y, 0);
								if (((int)rectangles2[i]->currentZRotateMatrix[0] % 90 == 45))
								{

									sliceTriangles[1]->Rotate(0 + randomTemp, 0, 0, 1, 2);
									if (randomTemp2 == 0)
									{
										leftRightMoveParameter[1].xDir = -1;
									}
									else
									{

										leftRightMoveParameter[1].xDir = 1;
									}
								}

								else
								{
									sliceTriangles[1]->Rotate(45 + randomTemp, 0, 0, 1, 2);
									if (randomTemp2 == 0)
									{
										leftRightMoveParameter[1].xDir = -1;
									}
									else
									{

										leftRightMoveParameter[1].xDir = 1;
									}
								}


								rectangles2Activate[i] = false;

							}

							else if (i == 1)

							{

								ParameterInitialize(2);
								leftRightMoveParameter[2].activate = true;
								sliceTriangles[2]->objectActivate = true;

								ParabolicMotionInitialize(&physicsStruct[2]);
								physicsStruct[2].dir = -1;


								ParameterInitialize(3);
								leftRightMoveParameter[3].activate = true;
								sliceTriangles[3]->objectActivate = true;

								ParabolicMotionInitialize(&physicsStruct[3]);



								sliceTriangles[2]->SetPosition(rectangles2[i]->Position().x, rectangles2[i]->Position().y, 0);
								if (((int)rectangles2[i]->currentZRotateMatrix[0] % 90 == 45))
								{
									sliceTriangles[2]->Rotate(180 + randomTemp, 0, 0, 1, 2);
									if (randomTemp2 == 0)
									{
										leftRightMoveParameter[2].xDir = 1;
									}
									else
									{

										leftRightMoveParameter[2].xDir = -1;
									}

								}

								else
								{
									sliceTriangles[2]->Rotate(225 + randomTemp, 0, 0, 1, 2);
									if (randomTemp2 == 0)
									{
										leftRightMoveParameter[2].xDir = 1;
									}
									else
									{

										leftRightMoveParameter[2].xDir = -1;
									}
								}

								sliceTriangles[3]->SetPosition(rectangles2[i]->Position().x, rectangles2[i]->Position().y, 0);
								if (((int)rectangles2[i]->currentZRotateMatrix[0] % 90 == 45))
								{
									sliceTriangles[3]->Rotate(0 + randomTemp, 0, 0, 1, 2);
									if (randomTemp2 == 0)
									{
										leftRightMoveParameter[3].xDir = -1;
									}
									else
									{

										leftRightMoveParameter[3].xDir = 1;
									}
								}

								else
								{
									sliceTriangles[3]->Rotate(45 + randomTemp, 0, 0, 1, 2);
									if (randomTemp2 == 0)
									{
										leftRightMoveParameter[3].xDir = -1;
									}
									else
									{

										leftRightMoveParameter[3].xDir = 1;
									}
								}



								rectangles2Activate[i] = false;

							}




						}

					}
				}

			}
		}


		if (downUp == true)
		{

			draggingLine->SetPosition(GLVector3(x - (800 / 2), (800 / 2) - y, 0), GLVector3(x - (800 / 2), (800 / 2) - y, 0));




		}




	}


	//draggingLine->SetPosition(GLVector3(x, y, 0), GLVector3(x, y, 0));
	//draggingLine->Enable();


}

void MouseWheel(int button, int state, int x, int y)
{


}

void MouseDrag(int x, int y)
{

	static int temp = 0;
	worldMousePositionX = x - (800 / 2);
	worldMousePositionY = (800 / 2) - y;
	temp = CheckCollisions();
	printf("%d\n", worldMousePositionX);

	if (temp != -1)
	{

		sliceTriangles[temp]->SetPosition(worldMousePositionX, worldMousePositionY, 0);


	}

	else if (draggingLine->onMyMouse)
	{
		draggingLine->SetPosition(GLVector3(x - (800 / 2), (800 / 2) - y, 0));
	}



}

void Keyboard(unsigned char key, int x, int y)
{

	if (key == 'i')
	{

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
	if (key == 'b')
	{


	}
	if (key == 'B')
	{

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

	}

	if (key == 'o' || key == 'O')
	{


	}
	else if (key == 'O')
	{



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

	if (key == 'q' || key == 'Q' || key == 'ㅂ')
	{

		masterMatrix->thisCamera.eyeZ -= 2.0;

	}

	else if (key == 'e' || key == 'E' || key == 'ㄷ')
	{

		masterMatrix->thisCamera.eyeZ += 2.0;

	}
	if (key == 'c' || key == 'C' || key == 'ㅊ')
	{




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



int CheckCollisions()
{

	for (int i = 0; i < sliceTriangleNum; ++i)
	{
		if (LiangBarsky(sliceTriangles[i]->Position().x - sliceTriangles[i]->size, sliceTriangles[i]->Position().x + sliceTriangles[i]->size,
			sliceTriangles[i]->Position().y - sliceTriangles[i]->size, sliceTriangles[i]->Position().y + sliceTriangles[i]->size
			, worldMousePositionX, worldMousePositionY, worldMousePositionX + 1, worldMousePositionY + 1
			, aaa[0], aaa[1], aaa[2], aaa[3]))
		{

			return i;
		}



	}







	return -1;


}

void ParameterInitialize(int i)
{

	leftRightMoveParameter[i].activate = false;
	leftRightMoveParameter[i].canPick = false;
	leftRightMoveParameter[i].currentFrame = 0;
	leftRightMoveParameter[i].distance = (rand() % 200) + 100;
	leftRightMoveParameter[i].keyFrame = 120;
	leftRightMoveParameter[i].loop = false;
	leftRightMoveParameter[i].targetIndex = i;
	leftRightMoveParameter[i].xDir = 1;
	leftRightMoveParameter[i].yDir = -1;

}
void LeftRightMove(SelfAnimation* parameter)
{



	if (parameter->activate)
	{


		if (parameter->currentFrame >= parameter->keyFrame)
		{
			parameter->activate = false;


			noSTCollision[parameter->targetIndex] = false;

		}


		if (parameter->currentFrame < parameter->keyFrame / 2)
		{
			sliceTriangles[parameter->targetIndex]->Translate(parameter->xDir * (double)parameter->distance / (double)(parameter->keyFrame / 2), 0, 0);

		}
		else if (parameter->currentFrame < parameter->keyFrame)
		{
			sliceTriangles[parameter->targetIndex]->Translate(0, parameter->yDir * (2000 / (double)(parameter->keyFrame / 2)), 0);

		}



		parameter->currentFrame += 1;
	}


}


void ParabolicMotion(PhysicsStruct* physicsStruct)
{

	physicsStruct->velocity.x = physicsStruct->speed * physicsStruct->dir * cos((PI * physicsStruct->theta) / 180.0);
	physicsStruct->velocity.y = physicsStruct->speed * sin((PI * physicsStruct->theta) / 180.0) - physicsStruct->gravitationalAcceleration * (1 / 60.0)  * physicsStruct->timeOfFrame;
	physicsStruct->timeOfFrame += 1;


}


void LinearMove(Polygon0* target, LinearMoveStruct *linearMoveStruct)
{
	if (linearMoveStruct->t <= 1)
	{
		target->SetPosition((1 - linearMoveStruct->t) * linearMoveStruct->point1.x + (linearMoveStruct->t) * linearMoveStruct->point2.x, (1 - linearMoveStruct->t) * linearMoveStruct->point1.y + (linearMoveStruct->t) * linearMoveStruct->point2.y, 0);
		//target->Translate(-2, -2, 0);
		linearMoveStruct->t += 0.01;



	}





}



void ParabolicMotionInitialize(PhysicsStruct* physicsStruct)
{

	physicsStruct->dir = 1;
	physicsStruct->speed = rand() % 10 + 5;
	physicsStruct->gravitationalAcceleration = 9.8;
	physicsStruct->timeOfFrame = 0;
	physicsStruct->velocity = GLVector2(0, 0);
	physicsStruct->theta = (rand() % 50) + 30;

}


