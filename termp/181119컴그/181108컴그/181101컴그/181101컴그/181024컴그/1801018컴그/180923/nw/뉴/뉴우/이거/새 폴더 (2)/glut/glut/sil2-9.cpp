#include "stdafx.h"



GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLdouble screenLTX = 0;
GLdouble screenRBX = 800;
GLdouble screenRBY = 0;
GLdouble screenLTY = 600;

int widthNum = 33;
int heightNum = 33;

int stack = 0;

bool left_button = false;


int mousePositionX = 0;
int mousePositionY = 0;



const int objectNumLimit = 100;

const int bigRectNumLimit = 1;




static GLVector3List vector3List[objectNumLimit];
static PolygonObject rects[objectNumLimit];
static PolygonObject bigRects[bigRectNumLimit];
static GLVector3List vector3List2[bigRectNumLimit];

static bool timerFlag[objectNumLimit];

static int poolingNum = 0;
static int bigRectPoolingNum = 0;

static PolygonKind polygonKind = PKNone;
static GLdouble wholeSpeed = 1.0;


static bool timerActivate = false;

CheckCollision checkCollision;

//함수부


void glOrtho2(GLdouble, GLdouble, GLdouble, GLdouble);
void DrawGraph(GLdouble leftX, GLdouble leftY, GLdouble width, GLdouble height, int row, int column);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void MouseDrag(int x, int y);
void SetPolygon(GLVectorBasic datumPoint, PolygonKind polygonKind);
void WholeSpeedUp();
void WholeSpeedDown();
void Start();

bool IsTimerWorking();

GLdouble GetRandomLinear();

void LinearAddTimerFunction(int value);



bool PoolingFull();
void PoolingCycle();


int PlusOrMinus();

void PoolingCycle2();

void ResetMoveRect(int i);
//함수부

void main(int argc, char *argv[]) {
	/*
	for (int i = 0; i < 10; ++i) {
	printf("%d ", timerFlag[i]);
	}
	*/
	srand((unsigned)time(NULL));



	glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example2"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정 



	glutReshapeFunc(Reshape);

	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseDrag);

	Start();
	glutMainLoop();
} // 윈도우 출력 함수 



void Start() {



	for (int i = 0; i < objectNumLimit; ++i) {

		if (rects[i].being == false) {

			SetPolygon(GLVectorBasic(rand() % (int)screenRBX, rand() % (int)screenLTY, 0), PKRe);



		}
	}


}




void SetPolygon(GLVectorBasic datumPoint, PolygonKind polygonKind) {

	int size = 100;

	PoolingCycle();

	if (poolingNum < objectNumLimit) {
		size = 20;
		if (polygonKind == PKRe) {

			vector3List[poolingNum].RemoveAll();



			GLVectorBasic glvector3[2] = {
				GLVectorBasic(datumPoint.x, datumPoint.y, datumPoint.z),
				GLVectorBasic(datumPoint.x + size, datumPoint.y - size, datumPoint.z)

			};

			GLVectorBasic glRGB = GLVectorBasic((rand() % 10 / 10.0), (rand() % 10 / 10.0), (rand() % 10 / 10.0));


			for (int i = 0; i < 2; ++i) {
				vector3List[poolingNum].Add(glvector3[i]);
			}



			rects[poolingNum] = PolygonObject(vector3List[poolingNum], true, PKRe);

			rects[poolingNum].rGB[0] = glRGB;
			rects[poolingNum].rGBOriginal[0] = glRGB;


			rects[poolingNum].linearMoveCoefficient = GetRandomLinear();
			rects[poolingNum].xMoveSpeed = ((rand() % 3) + 5) * PlusOrMinus();
			rects[poolingNum].yMoveSpeed = rects[poolingNum].xMoveSpeed * rects[poolingNum].linearMoveCoefficient;


			rects[poolingNum].xMoveSpeedOriginal = rects[poolingNum].xMoveSpeed;
			rects[poolingNum].yMoveSpeedOriginal = rects[poolingNum].yMoveSpeed;



			int pM = PlusOrMinus();

			if (pM == 1) {

				rects[poolingNum].clock = true;
				rects[poolingNum].toRight = true;


			}
			else if (pM == -1) {

				rects[poolingNum].counterClock = true;
				rects[poolingNum].toLeft = true;
			}




			if (true) {//애니메이션 쓸건지에 대한 플레그

				timerFlag[poolingNum] = true;
				if (!IsTimerWorking()) {

					timerActivate = true;
					glutTimerFunc(100, TimerFunction, poolingNum);
				}

			}



			poolingNum++;

		}

		else if (polygonKind == PKTr) {

			vector3List[poolingNum].RemoveAll();



			GLVectorBasic glvector3[3] = {
				GLVectorBasic(datumPoint.x + (size / 2), datumPoint.y, datumPoint.z),
				GLVectorBasic(datumPoint.x + size, datumPoint.y - size, datumPoint.z),
				GLVectorBasic(datumPoint.x, datumPoint.y - (size / 2), datumPoint.z)

			};

			GLVectorBasic glRGB = GLVectorBasic((rand() % 10 / 10.0), (rand() % 10 / 10.0), (rand() % 10 / 10.0));


			for (int i = 0; i < 3; ++i) {
				vector3List[poolingNum].Add(glvector3[i]);
			}



			rects[poolingNum] = PolygonObject(vector3List[poolingNum], true, PKTr);

			rects[poolingNum].rGB[0] = glRGB;
			rects[poolingNum].rGBOriginal[0] = glRGB;


			if (true) {//애니메이션 쓸건지에 대한 플레그

				timerFlag[poolingNum] = true;
				if (!IsTimerWorking()) {
					timerActivate = true;

					glutTimerFunc(100, TimerFunction, poolingNum);
				}

			}


			poolingNum++;

		}
		else if (polygonKind == PKBRe) {


			size = 80;

			vector3List2[bigRectPoolingNum].RemoveAll();



			GLVectorBasic glvector3[2] = {
				GLVectorBasic(datumPoint.x, datumPoint.y, datumPoint.z),
				GLVectorBasic(datumPoint.x + size, datumPoint.y - size, datumPoint.z)

			};




			for (int i = 0; i < 2; ++i) {
				vector3List2[bigRectPoolingNum].Add(glvector3[i]);
			}



			bigRects[bigRectPoolingNum] = PolygonObject(vector3List2[bigRectPoolingNum], true, PKBRe);



			if (false) {//애니메이션 쓸건지에 대한 플레그

				timerFlag[bigRectPoolingNum] = true;
				if (!IsTimerWorking()) {

					timerActivate = true;
					glutTimerFunc(100, TimerFunction, bigRectPoolingNum);
				}

			}



			bigRectPoolingNum++;

		}


	}




}

void RandomMovingTimerFunction(int value) {


	for (int i = 0; i < poolingNum; ++i) {


		if (rects[i].activate) {




		}




	}






	glutPostRedisplay();


	glutTimerFunc(100, RandomMovingTimerFunction, value);

}




void TimerFunction(int value) {


	if (timerActivate == false) {
		return;
	}
	for (int i = 0; i < objectNumLimit; ++i) {


		if (rects[i].activate && timerFlag[i] == true) {



			if (rects[i].polygonNum == PKRe) {
				//확대축소 애니메이션(추후 모듈화 하기)
				if (rects[i].aniStack >= 6) {
					rects[i].aniStack = 0;


				}


				if (rects[i].aniStack < 3) {

					rects[i].aniStack++;

					rects[i].glVector3[0].x -= 5.0;
					rects[i].glVector3[0].y += 5.0;

					rects[i].glVector3[1].x += 5.0;
					rects[i].glVector3[1].y += 5.0;


					rects[i].glVector3[2].x += 5.0;
					rects[i].glVector3[2].y -= 5.0;

					rects[i].glVector3[3].x -= 5.0;
					rects[i].glVector3[3].y -= 5.0;

					rects[i].rGB[0].x += 0.07;
					rects[i].rGB[0].y += 0.07;
					rects[i].rGB[0].z += 0.07;

				}

				else if (rects[i].aniStack >= 3) {
					rects[i].aniStack++;

					rects[i].glVector3[0].x += 5.0;
					rects[i].glVector3[0].y -= 5.0;

					rects[i].glVector3[1].x -= 5.0;
					rects[i].glVector3[1].y -= 5.0;


					rects[i].glVector3[2].x -= 5.0;
					rects[i].glVector3[2].y += 5.0;

					rects[i].glVector3[3].x += 5.0;
					rects[i].glVector3[3].y += 5.0;
					rects[i].rGB[0].x -= 0.07;
					rects[i].rGB[0].y -= 0.07;
					rects[i].rGB[0].z -= 0.07;

				}



				//이동 모듈

				if (!rects[i].selected) {

					if (rects[i].glVector3[0].y >= screenLTY) {



						while (rects[i].glVector3[0].y >= screenLTY) {
							rects[i].glVector3[1].y -= 0.1;
							rects[i].glVector3[0].y -= 0.1;
							rects[i].glVector3[2].y -= 0.1;
							rects[i].glVector3[3].y -= 0.1;
						}



						rects[i].yMoveSpeed *= -1;

					}
					if (rects[i].glVector3[1].y <= screenRBY) {


						while (rects[i].glVector3[1].y <= screenRBY) {

							rects[i].glVector3[1].y += 0.1;
							rects[i].glVector3[0].y += 0.1;

							rects[i].glVector3[3].y += 0.1;
							rects[i].glVector3[2].y += 0.1;
						}

						rects[i].yMoveSpeed *= -1;
					}

					if (rects[i].glVector3[0].x <= screenLTX) {


						while (rects[i].glVector3[0].x <= screenLTX) {

							rects[i].glVector3[1].x += 0.1;
							rects[i].glVector3[0].x += 0.1;

							rects[i].glVector3[3].x += 0.1;
							rects[i].glVector3[2].x += 0.1;

						}

						rects[i].xMoveSpeed *= -1;
					}


					if (rects[i].glVector3[1].x >= screenRBX) {

						while (rects[i].glVector3[1].x >= screenRBX) {

							rects[i].glVector3[1].x -= 0.1;
							rects[i].glVector3[0].x -= 0.1;
							rects[i].glVector3[2].x -= 0.1;
							rects[i].glVector3[3].x -= 0.1;

						}
						rects[i].xMoveSpeed *= -1;

					}




					rects[i].glVector3[0].x += rects[i].xMoveSpeed;
					rects[i].glVector3[0].y += rects[i].yMoveSpeed;

					rects[i].glVector3[1].x += rects[i].xMoveSpeed;
					rects[i].glVector3[1].y += rects[i].yMoveSpeed;

					rects[i].glVector3[2].x += rects[i].xMoveSpeed;
					rects[i].glVector3[2].y += rects[i].yMoveSpeed;

					rects[i].glVector3[3].x += rects[i].xMoveSpeed;
					rects[i].glVector3[3].y += rects[i].yMoveSpeed;


				}

				else if (rects[i].selected) {

					if (rects[i].counterClock) {


						if (rects[i].toLeft && rects[i].glVector3[0].x >= screenLTX) {
							rects[i].glVector3[0].x -= fabs(rects[i].xMoveSpeed);
							rects[i].glVector3[1].x -= fabs(rects[i].xMoveSpeed);
							rects[i].glVector3[2].x -= fabs(rects[i].xMoveSpeed);
							rects[i].glVector3[3].x -= fabs(rects[i].xMoveSpeed);

							if (rects[i].oneCycled && rects[i].glVector3[0].x <= rects[i].startingPosition.x) {
								rects[i].selected = false;
								rects[i].oneCycled = false;
								rects[i].oneCycle = false;


							}

						}

						else if (rects[i].toLeft)
						{

							while (rects[i].glVector3[0].x < screenLTX) {

								rects[i].glVector3[0].x += 0.1;
								rects[i].glVector3[1].x += 0.1;
								rects[i].glVector3[2].x += 0.1;
								rects[i].glVector3[3].x += 0.1;
							}


							rects[i].toLeft = false;

							rects[i].toDown = true;

						}


						if (rects[i].toDown && rects[i].glVector3[1].y >= screenRBY) {

							rects[i].glVector3[0].y -= fabs(rects[i].yMoveSpeed);
							rects[i].glVector3[1].y -= fabs(rects[i].yMoveSpeed);
							rects[i].glVector3[2].y -= fabs(rects[i].yMoveSpeed);
							rects[i].glVector3[3].y -= fabs(rects[i].yMoveSpeed);

						}

						else if (rects[i].toDown) {


							while (rects[i].glVector3[1].y < screenRBY) {

								rects[i].glVector3[0].y += 0.1;
								rects[i].glVector3[1].y += 0.1;
								rects[i].glVector3[2].y += 0.1;
								rects[i].glVector3[3].y += 0.1;
							}


							rects[i].toDown = false;
							rects[i].toRight = true;
						}



						if (rects[i].toRight && rects[i].glVector3[1].x <= screenRBX) {

							rects[i].glVector3[0].x += fabs(rects[i].xMoveSpeed);
							rects[i].glVector3[1].x += fabs(rects[i].xMoveSpeed);
							rects[i].glVector3[2].x += fabs(rects[i].xMoveSpeed);
							rects[i].glVector3[3].x += fabs(rects[i].xMoveSpeed);
						}

						else if (rects[i].toRight) {

							while (rects[i].glVector3[1].x > screenRBX) {

								rects[i].glVector3[0].x -= 0.1;
								rects[i].glVector3[1].x -= 0.1;
								rects[i].glVector3[2].x -= 0.1;
								rects[i].glVector3[3].x -= 0.1;
							}


							rects[i].toRight = false;
							rects[i].toUp = true;
						}

						if (rects[i].toUp && rects[i].glVector3[0].y <= screenLTY) {

							rects[i].glVector3[0].y += fabs(rects[i].yMoveSpeed);
							rects[i].glVector3[1].y += fabs(rects[i].yMoveSpeed);
							rects[i].glVector3[2].y += fabs(rects[i].yMoveSpeed);
							rects[i].glVector3[3].y += fabs(rects[i].yMoveSpeed);

							if (rects[i].oneCycle && rects[i].glVector3[0].y >= rects[i].startingPosition.y) {
								rects[i].toLeft = true;
								rects[i].toUp = false;
								rects[i].oneCycled = true;

							}

						}

						else if (rects[i].toUp) {


							while (rects[i].glVector3[0].y > screenLTY) {

								rects[i].glVector3[0].y -= 0.1;
								rects[i].glVector3[1].y -= 0.1;
								rects[i].glVector3[2].y -= 0.1;
								rects[i].glVector3[3].y -= 0.1;
							}

							rects[i].toUp = false;
							rects[i].toLeft = true;

						}




					}

					else if (rects[i].clock) {

						if (rects[i].toRight && rects[i].glVector3[1].x <= screenRBX) {
							rects[i].glVector3[0].x += fabs(rects[i].xMoveSpeed);
							rects[i].glVector3[1].x += fabs(rects[i].xMoveSpeed);
							rects[i].glVector3[2].x += fabs(rects[i].xMoveSpeed);
							rects[i].glVector3[3].x += fabs(rects[i].xMoveSpeed);


							if (rects[i].oneCycled && rects[i].glVector3[0].x >= rects[i].startingPosition.x) {
								rects[i].selected = false;
								rects[i].oneCycled = false;
								rects[i].oneCycle = false;


							}

						}

						else if (rects[i].toRight)
						{
							while (rects[i].glVector3[1].x > screenRBX) {

								rects[i].glVector3[0].x -= 0.1;
								rects[i].glVector3[1].x -= 0.1;
								rects[i].glVector3[2].x -= 0.1;
								rects[i].glVector3[3].x -= 0.1;
							}

							rects[i].toRight = false;

							rects[i].toDown = true;

						}


						if (rects[i].toDown && rects[i].glVector3[1].y >= screenRBY) {

							rects[i].glVector3[0].y -= fabs(rects[i].yMoveSpeed);
							rects[i].glVector3[1].y -= fabs(rects[i].yMoveSpeed);
							rects[i].glVector3[2].y -= fabs(rects[i].yMoveSpeed);
							rects[i].glVector3[3].y -= fabs(rects[i].yMoveSpeed);


						}

						else if (rects[i].toDown) {

							while (rects[i].glVector3[1].y < screenRBY) {

								rects[i].glVector3[0].y += 0.1;
								rects[i].glVector3[1].y += 0.1;
								rects[i].glVector3[2].y += 0.1;
								rects[i].glVector3[3].y += 0.1;
							}

							rects[i].toDown = false;
							rects[i].toLeft = true;
						}



						if (rects[i].toLeft && rects[i].glVector3[0].x >= screenLTX) {

							rects[i].glVector3[0].x -= fabs(rects[i].xMoveSpeed);
							rects[i].glVector3[1].x -= fabs(rects[i].xMoveSpeed);

							rects[i].glVector3[2].x -= fabs(rects[i].xMoveSpeed);
							rects[i].glVector3[3].x -= fabs(rects[i].xMoveSpeed);
						}

						else if (rects[i].toLeft) {


							while (rects[i].glVector3[0].x < screenLTX) {
								rects[i].glVector3[0].x += 0.1;
								rects[i].glVector3[1].x += 0.1;
								rects[i].glVector3[2].x += 0.1;
								rects[i].glVector3[3].x += 0.1;

							}

							rects[i].toLeft = false;
							rects[i].toUp = true;
						}

						if (rects[i].toUp && rects[i].glVector3[0].y <= screenLTY) {

							rects[i].glVector3[0].y += fabs(rects[i].yMoveSpeed);
							rects[i].glVector3[1].y += fabs(rects[i].yMoveSpeed);
							rects[i].glVector3[2].y += fabs(rects[i].yMoveSpeed);
							rects[i].glVector3[3].y += fabs(rects[i].yMoveSpeed);

							if (rects[i].oneCycle && rects[i].glVector3[0].y >= rects[i].startingPosition.y) {
								rects[i].toRight = true;
								rects[i].toUp = false;
								rects[i].oneCycled = true;

							}

						}

						else if (rects[i].toUp) {

							while (rects[i].glVector3[0].y > screenLTY) {
								rects[i].glVector3[0].y -= 0.1;
								rects[i].glVector3[1].y -= 0.1;
								rects[i].glVector3[2].y -= 0.1;
								rects[i].glVector3[3].y -= 0.1;

							}


							rects[i].toUp = false;
							rects[i].toRight = true;

						}
					}




				}


			}

			else if (rects[i].polygonNum == PKTr) {

			}

		}




	}


	/*
	if (value < rectNumLimit) {

	if (test[value].stack >= 6) {
	test[value].stack = 0;


	}


	if (test[value].stack < 3) {

	test[value].stack++;

	test[value].glVector3[0].x -= 20.0;
	test[value].glVector3[0].y += 20.0;

	test[value].glVector3[1].x += 20.0;
	test[value].glVector3[1].y -= 20.0;


	test[value].rGB[0].x += 0.07;
	test[value].rGB[0].y += 0.07;
	test[value].rGB[0].z += 0.07;

	}

	else if (test[value].stack >= 3) {
	test[value].stack++;

	test[value].glVector3[0].x += 20.0;
	test[value].glVector3[0].y -= 20.0;

	test[value].glVector3[1].x -= 20.0;
	test[value].glVector3[1].y += 20.0;

	test[value].rGB[0].x -= 0.07;
	test[value].rGB[0].y -= 0.07;
	test[value].rGB[0].z -= 0.07;

	}




	}


	*/

	glutPostRedisplay();

	if (timerActivate) {
		glutTimerFunc(100, TimerFunction, value);
	}




}

void MouseDrag(int x, int y) {

	printf("마우스 : %d,%d\n ", x, y);

	if (bigRects[0].activate) {

		bigRects[0].glVector3[0].x = (GLdouble)x - bigRects[0].width / 2;
		bigRects[0].glVector3[1].x = (GLdouble)x + bigRects[0].width / 2;
		bigRects[0].glVector3[0].y = screenLTY - (GLdouble)y + bigRects[0].height / 2;
		bigRects[0].glVector3[1].y = screenLTY - (GLdouble)y - bigRects[0].height / 2;
	}

}

void Mouse(int button, int state, int x, int y) {


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		//printf("드래그 시작 : %d,%d\n", x, y);
		SetPolygon(GLVectorBasic((GLdouble)x, screenLTY - (GLdouble)y, 0), PKBRe);


		printf("%d %d\n", bigRects[0].Available(), bigRects[0].Available());

	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

		printf("마우스를 뗀 장소 : %d,%d\n", x, y);
		bigRects[0].activate = false;
	}




}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case '1':
		printf("ㅁㄴㅇ");
		if (rects[0].activate) {
			rects[0].startingPosition = GLVectorBasic(rects[0].glVector3[0].x, rects[0].glVector3[0].y, rects[0].glVector3[0].z);
			rects[0].selected = true;

			ResetMoveRect(0);


		}

		break;
	case '2':
		if (rects[1].activate) {


			rects[1].startingPosition = GLVectorBasic(rects[1].glVector3[0].x, rects[1].glVector3[0].y, rects[1].glVector3[0].z);
			rects[1].selected = true;


			ResetMoveRect(1);

		}

		break;
	case '3':
		if (rects[2].activate) {


			//test[0].startingPosition = GLVector3(test[0].)
			rects[2].startingPosition = GLVectorBasic(rects[2].glVector3[0].x, rects[2].glVector3[0].y, rects[2].glVector3[0].z);
			rects[2].selected = true;

			ResetMoveRect(2);
		}
		break;
	case '4':
		if (rects[3].activate) {


			//test[0].startingPosition = GLVector3(test[0].)
			rects[3].startingPosition = GLVectorBasic(rects[3].glVector3[0].x, rects[3].glVector3[0].y, rects[3].glVector3[0].z);
			rects[3].selected = true;

			ResetMoveRect(3);
		}

		break;
	case '5':
		if (rects[4].activate) {


			//test[0].startingPosition = GLVector3(test[0].)
			rects[4].startingPosition = GLVectorBasic(rects[4].glVector3[0].x, rects[4].glVector3[0].y, rects[4].glVector3[0].z);
			rects[4].selected = true;

			ResetMoveRect(4);
		}

		break;
	case '6':
		if (rects[5].activate) {


			//test[0].startingPosition = GLVector3(test[0].)
			rects[5].startingPosition = GLVectorBasic(rects[5].glVector3[0].x, rects[5].glVector3[0].y, rects[5].glVector3[0].z);
			rects[5].selected = true;


			ResetMoveRect(5);
		}

		break;
	case '7':
		if (rects[6].activate) {


			//test[0].startingPosition = GLVector3(test[0].)
			rects[6].startingPosition = GLVectorBasic(rects[6].glVector3[0].x, rects[6].glVector3[0].y, rects[6].glVector3[0].z);
			rects[6].selected = true;

			ResetMoveRect(6);
		}

		break;
	case '8':
		if (rects[7].activate) {


			//test[0].startingPosition = GLVector3(test[0].)
			rects[7].startingPosition = GLVectorBasic(rects[7].glVector3[0].x, rects[7].glVector3[0].y, rects[7].glVector3[0].z);
			rects[7].selected = true;

			ResetMoveRect(7);
		}

		break;
	case '9':
		if (rects[8].activate) {


			//test[0].startingPosition = GLVector3(test[0].)

			rects[8].startingPosition = GLVectorBasic(rects[8].glVector3[0].x, rects[8].glVector3[0].y, rects[8].glVector3[0].z);
			rects[8].selected = true;


			ResetMoveRect(8);
		}

		break;
	case '0':

		for (int i = 0; i < objectNumLimit; ++i) {
			if (rects[i].activate) {


				//test[0].startingPosition = GLVector3(test[0].)

				rects[i].startingPosition = GLVectorBasic(rects[i].glVector3[0].x, rects[i].glVector3[0].y, rects[i].glVector3[0].z);
				rects[i].selected = true;
				rects[i].oneCycle = true;

				ResetMoveRect(i);
			}
		}
		break;

	case 'p':

		for (int i = 0; i < objectNumLimit; ++i) {
			rects[i].selected = false;


		}
		break;

	case 's':

		for (int i = 0; i < objectNumLimit; ++i) {
			timerFlag[i] = !timerFlag[i];

		}

		break;
	case 't':
		printf("키보드입력 %c\n", key);
		polygonKind = PKTr;

		break;
	case 'r':
		printf("키보드입력 %c\n", key);
		polygonKind = PKRe;
		break;

	case '+':
		printf("키보드입력 %c\n", key);
		WholeSpeedUp();

		for (int i = 0; i < objectNumLimit; ++i) {
			if (rects[i].activate) {



				if (rects[i].xMoveSpeed >= 0) {
					rects[i].xMoveSpeed = fabs(wholeSpeed * rects[i].xMoveSpeedOriginal);
				}

				else
				{
					rects[i].xMoveSpeed = -1 * fabs((wholeSpeed * rects[i].xMoveSpeedOriginal));

				}

				if (rects[i].yMoveSpeed >= 0) {
					rects[i].yMoveSpeed = fabs(wholeSpeed * rects[i].yMoveSpeedOriginal);
				}
				else {

					rects[i].yMoveSpeed = -1 * fabs(wholeSpeed * rects[i].yMoveSpeedOriginal);
				}

				printf("%f\n", rects[i].xMoveSpeed);
				printf("%f\n", rects[i].yMoveSpeed);
			}
		}
		break;
	case '-':
		printf("키보드입력 %c\n", key);
		WholeSpeedDown();

		for (int i = 0; i < objectNumLimit; ++i) {
			if (rects[i].activate) {

				if (rects[i].xMoveSpeed >= 0) {
					rects[i].xMoveSpeed = fabs(wholeSpeed * rects[i].xMoveSpeedOriginal);
				}

				else
				{
					rects[i].xMoveSpeed = -1 * fabs((wholeSpeed * rects[i].xMoveSpeedOriginal));

				}

				if (rects[i].yMoveSpeed >= 0) {
					rects[i].yMoveSpeed = fabs(wholeSpeed * rects[i].yMoveSpeedOriginal);
				}
				else {

					rects[i].yMoveSpeed = -1 * fabs(wholeSpeed * rects[i].yMoveSpeedOriginal);
				}

				printf("%f\n", rects[i].xMoveSpeed);
				printf("%f\n", rects[i].yMoveSpeed);
			}
		}

		break;
	}


}

GLvoid drawScene(GLvoid) {




	glClearColor(0.2f, 0.0f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 

								  //glRectf(-0.5f, -0.5f, 0.5f, 0.5f); // 사각형 그리기

	glColor4f(0.7f, 0.2f, 0.0f, 1.0f);


	DrawGraph(screenLTX, screenLTY, 200, 50, 1, 0);



	for (int i = 0; i < objectNumLimit; ++i) {

		if (rects[i].activate) {

			if (rects[i].polygonNum == (int)PKRe) {

				glColor4f(rects[i].rGB[0].x, rects[i].rGB[0].y, rects[i].rGB[0].z, 1.0);
				glBegin(GL_POLYGON);
				glVertex2d(rects[i].glVector3[0].x, rects[i].glVector3[0].y);
				glVertex2d(rects[i].glVector3[1].x, rects[i].glVector3[1].y);
				glVertex2d(rects[i].glVector3[2].x, rects[i].glVector3[2].y);
				glVertex2d(rects[i].glVector3[3].x, rects[i].glVector3[3].y);
				glEnd();


			}

			else if (rects[i].polygonNum == (int)PKTr) {

				glColor4f(rects[i].rGB[0].x, rects[i].rGB[0].y, rects[i].rGB[0].z, 1.0);
				glBegin(GL_POLYGON);

				glVertex3d(rects[i].glVector3[0].x, rects[i].glVector3[0].y, rects[i].glVector3[0].z);
				glVertex3d(rects[i].glVector3[1].x, rects[i].glVector3[1].y, rects[i].glVector3[1].z);
				glVertex3d(rects[i].glVector3[2].x, rects[i].glVector3[2].y, rects[i].glVector3[2].z);
				glEnd();

			}

		}

	}
	for (int i = 0; i < bigRectNumLimit; ++i) {

		if (bigRects[i].activate) {


			if (bigRects[i].polygonNum == (int)PKBRe) {

				glColor4f(bigRects[i].rGB[0].x, bigRects[i].rGB[0].y, bigRects[i].rGB[0].z, 1.0);
				glRectd(bigRects[i].glVector3[0].x, bigRects[i].glVector3[0].y, bigRects[i].glVector3[1].x, bigRects[i].glVector3[1].y);


				for (int j = 0; j < objectNumLimit; ++j) {

					if ((rects[j].Available() && rects[j].polygonNum == (int)PKRe) && checkCollision.CheckRectRect(Rect(rects[j].glVector3[0].x, rects[j].glVector3[0].y, rects[j].width, rects[j].height), Rect(bigRects[0].glVector3[0].x, bigRects[0].glVector3[0].y, bigRects[0].width, bigRects[0].height))) {



						rects[j].Destroy();


					}

				}

			}

		}

	}






	glFlush(); // 화면에 출력하기

}



GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho2(screenLTX, screenLTY, screenRBX, screenRBY);

}



void glOrtho2(GLdouble leftX, GLdouble leftY, GLdouble rightX, GLdouble rightY) {

	glOrtho(leftX, rightX, rightY, leftY, -1.0, 1.0);
}



void DrawGraph(GLdouble leftX, GLdouble leftY, GLdouble width, GLdouble height, int row, int column) {

	if (row == 0 && column == 0) {
		return;
	}

	GLdouble rightBottomX = leftX + width;
	GLdouble rightBottomY = leftY - height;



	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2d(leftX, leftY);
	glVertex2d(rightBottomX, leftY);

	glVertex2d(rightBottomX, rightBottomY);
	glVertex2d(leftX, rightBottomY);


	glEnd();

	GLdouble intervalWidth = width / row;
	GLdouble intervalHeight = height / column;

	for (int j = 0; j < row - 1; ++j) {




		glBegin(GL_LINE_LOOP);
		glVertex2d(leftX + (j + 1) * intervalWidth, leftY);
		glVertex2d(leftX + (j + 1) * intervalWidth, rightBottomY);



		glEnd();






	}




	for (int i = 0; i < column - 1; ++i) {


		glBegin(GL_LINE_LOOP);
		glVertex2d(leftX, leftY - (i + 1) * intervalHeight);
		glVertex2d(rightBottomX, leftY - (i + 1) * intervalHeight);



		glEnd();


	}








	int pointNum = (rand() % 4) + 2;

	GLdouble temp = 0.2f;

	bool incFlag = false;
	bool decFlag = false;

	incFlag = true;


	for (int j = 0; j < column; ++j) {

		for (int i = 0; i < row; ++i) {
			glColor4f((rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, 1.0f);



			switch (pointNum)
			{
			case 2:
				glBegin(GL_LINE_LOOP);

				glVertex2d(leftX + (i * intervalWidth) + (temp * intervalWidth), leftY - (j * intervalHeight) - (temp*intervalHeight));

				glVertex2d(leftX + (i * intervalWidth) + ((1.0f - temp) * intervalWidth), leftY - (j * intervalHeight) - ((1.0f - temp)*intervalHeight));

				glEnd();

				break;

			case 3:


				glBegin(GL_POLYGON);

				glVertex2d(leftX + (i * intervalWidth) + (0.5f * intervalWidth), leftY - (j * intervalHeight) - (temp*intervalHeight));

				glVertex2d(leftX + (i * intervalWidth) + (temp * intervalWidth), leftY - (j * intervalHeight) - (0.5f*intervalHeight));

				glVertex2d(leftX + (i * intervalWidth) + ((1.0f - temp) * intervalWidth), leftY - (j * intervalHeight) - ((1.0f - temp) * intervalHeight));


				glEnd();

				break;

			case 4:


				glBegin(GL_POLYGON);

				glVertex2d(leftX + (i * intervalWidth) + (temp * intervalWidth), leftY - (j * intervalHeight) - (temp*intervalHeight));

				glVertex2d(leftX + (i * intervalWidth) + ((1.0f - temp) * intervalWidth), leftY - (j * intervalHeight) - (temp*intervalHeight));

				glVertex2d(leftX + (i * intervalWidth) + ((1.0f - temp) * intervalWidth), leftY - (j * intervalHeight) - ((1.0f - temp) * intervalHeight));

				glVertex2d(leftX + (i * intervalWidth) + (temp * intervalWidth), leftY - (j * intervalHeight) - ((1.0f - temp) * intervalHeight));


				glEnd();


				break;

			case 5:



				glBegin(GL_POLYGON);

				glVertex2d(leftX + (i * intervalWidth) + (0.5f * intervalWidth), leftY - (j * intervalHeight) - (temp*intervalHeight));


				glVertex2d(leftX + (i * intervalWidth) + ((0.8f) * intervalWidth), leftY - (j * intervalHeight) - (0.4f*intervalHeight));


				glVertex2d(leftX + (i * intervalWidth) + ((0.7f) * intervalWidth), leftY - (j * intervalHeight) - ((1.0f - temp) * intervalHeight));




				glVertex2d(leftX + (i * intervalWidth) + ((0.3f) * intervalWidth), leftY - (j * intervalHeight) - ((1.0f - temp) * intervalHeight));



				glVertex2d(leftX + (i * intervalWidth) + ((0.2f) * intervalWidth), leftY - (j * intervalHeight) - (0.4f*intervalHeight));



				glEnd();


				break;


			default:
				break;
			}


			if (incFlag) {
				if (pointNum < 5) {
					++pointNum;
				}

				else if (pointNum >= 5) {

					--pointNum;

					incFlag = false;

					decFlag = true;
				}


			}

			else if (decFlag) {

				if (pointNum > 2) {

					--pointNum;
				}

				else if (pointNum <= 2) {

					++pointNum;

					incFlag = true;

					decFlag = false;
				}


			}





		}


	}




}
int PlusOrMinus() {

	int temp = rand() % 2;


	if (temp == 0) {

		temp = 1;
	}
	else if (temp == 1) {

		temp = -1;
	}

	return temp;
}

GLdouble GetRandomLinear() {




	return  PlusOrMinus() * (GLdouble)(((rand() % 10) / 10.0) + 0.5);



}

void LinearAddTimerFunction(int value) {


	//스크린의 좌표계 끝에 도달하면 기울기 방향을 바꿈
	//Timer함수를 얼마나 자주 부르냐가 속도에 기여


}


bool PoolingFull() {


	if (poolingNum >= objectNumLimit) {

		return true;

	}
	return false;

}

void PoolingCycle() {

	if (PoolingFull()) {

		poolingNum = 0;

	}

	PoolingCycle2();

}

void PoolingCycle2() {

	if (bigRectPoolingNum >= bigRectNumLimit) {


		bigRectPoolingNum = 0;

	}

}



bool IsTimerWorking() {

	return timerActivate;

}


void WholeSpeedUp() {



	wholeSpeed += 0.02;

	if (wholeSpeed >= 2.0) {

		wholeSpeed = 2.0;
	}
	return;

}
void WholeSpeedDown() {


	wholeSpeed -= 0.02;

	if (wholeSpeed <= 0) {
		wholeSpeed = 0;
	}

	return;

}

void ResetMoveRect(int i) {

	if (rects[i].counterClock) {

		rects[i].toRight = false;
		rects[i].toLeft = true;
		rects[i].toDown = false;
		rects[i].toUp = false;
	}
	else if (rects[i].clock) {
		rects[i].toRight = true;
		rects[i].toLeft = false;
		rects[i].toDown = false;
		rects[i].toUp = false;

	}

}