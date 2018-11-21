
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



const int objectNumLimit = 10;




class Test {

public:

	Test() {

		activate = false;
		being = false;
		polygonNum = 0;
	}
	Test(GLVector3List vector3List, bool state, PolygonKind polygonKind) {

		activate = false;
		being = false;


		polygonNum = 0;


		for (int i = 0; i < vector3List.Length(); ++i) {
			this->glVector3[i].x = vector3List.GetDataOfIndex(i).x;
			this->glVector3[i].y = vector3List.GetDataOfIndex(i).y;
			this->glVector3[i].z = vector3List.GetDataOfIndex(i).z;


			this->original[i].x = vector3List.GetDataOfIndex(i).x;
			this->original[i].y = vector3List.GetDataOfIndex(i).y;
			this->original[i].z = vector3List.GetDataOfIndex(i).z;


		}
		this->polygonNum = (int)polygonKind;

		this->activate = state;

	}




	static const int size = 100;

	int aniStack = 0;
	GLVectorBasic original[size];
	GLVectorBasic glVector3[size];
	GLVectorBasic rGB[size];
	GLVectorBasic rGBOriginal[size];

	int polygonNum = 0;

	bool activate;

	bool being;

	GLdouble linearMoveCoefficient;
	GLdouble xMoveSpeed;
	GLdouble yMoveSpeed;
	GLdouble zMoveSpeed;

	GLdouble xMoveSpeedOriginal;
	GLdouble yMoveSpeedOriginal;
	GLdouble zMoveSpeedOriginal;

};


static GLVector3List vector3List[objectNumLimit];
static Test test[objectNumLimit];
static bool timerFlag[objectNumLimit];

static int poolingNum = 0;

static PolygonKind polygonKind = PKNone;
static GLdouble wholeSpeed = 1.0;


static bool timerActivate = false;

//함수부


void glOrtho2(GLdouble, GLdouble, GLdouble, GLdouble);
void DrawGraph(GLdouble leftX, GLdouble leftY, GLdouble width, GLdouble height, int row, int column);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void MouseDrag(int x, int y);
void SetPolygon(GLVectorBasic datumPoint, PolygonKind polygonKind);
void DraggingShape(Test test);
void WholeSpeedUp();
void WholeSpeedDown();

bool IsTimerWorking();

GLdouble GetRandomLinear();

void LinearAddTimerFunction(int value);



bool PoolingFull();
void PoolingCycle();


int PlusOrMinus();

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


	glutMainLoop();
} // 윈도우 출력 함수 








void SetPolygon(GLVectorBasic datumPoint, PolygonKind polygonKind) {

	int size = 100;

	PoolingCycle();

	if (poolingNum < objectNumLimit) {
		size = (rand() % 100) + 20;
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



			test[poolingNum] = Test(vector3List[poolingNum], true, PKRe);

			test[poolingNum].rGB[0] = glRGB;
			test[poolingNum].rGBOriginal[0] = glRGB;


			test[poolingNum].linearMoveCoefficient = GetRandomLinear();
			test[poolingNum].xMoveSpeed = ((rand() % 3) + 5) * PlusOrMinus();
			test[poolingNum].yMoveSpeed = test[poolingNum].xMoveSpeed * test[poolingNum].linearMoveCoefficient;


			test[poolingNum].xMoveSpeedOriginal = test[poolingNum].xMoveSpeed;
			test[poolingNum].yMoveSpeedOriginal = test[poolingNum].yMoveSpeed;


			if (true) {//애니메이션 쓸건지에 대한 플레그

				timerFlag[poolingNum] = true;
				if (!IsTimerWorking()) {

					timerActivate = true;
					glutTimerFunc(100, TimerFunction, poolingNum);
				}
				printf("%dppol\n", poolingNum);
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



			test[poolingNum] = Test(vector3List[poolingNum], true, PKTr);

			test[poolingNum].rGB[0] = glRGB;
			test[poolingNum].rGBOriginal[0] = glRGB;


			if (true) {//애니메이션 쓸건지에 대한 플레그

				timerFlag[poolingNum] = true;
				if (!IsTimerWorking()) {
					timerActivate = true;

					glutTimerFunc(100, TimerFunction, poolingNum);
				}
				printf("%dppol\n", poolingNum);
			}


			poolingNum++;

		}



	}




}

void RandomMovingTimerFunction(int value) {


	for (int i = 0; i < poolingNum; ++i) {


		if (test[i].activate) {




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


		if (test[i].activate && timerFlag[i] == true) {



			if (test[i].polygonNum == PKRe) {
				//확대축소 애니메이션(추후 모듈화 하기)
				if (test[i].aniStack >= 6) {
					test[i].aniStack = 0;


				}


				if (test[i].aniStack < 3) {

					test[i].aniStack++;

					test[i].glVector3[0].x -= 20.0;
					test[i].glVector3[0].y += 20.0;

					test[i].glVector3[1].x += 20.0;
					test[i].glVector3[1].y -= 20.0;


					test[i].rGB[0].x += 0.07;
					test[i].rGB[0].y += 0.07;
					test[i].rGB[0].z += 0.07;

				}

				else if (test[i].aniStack >= 3) {
					test[i].aniStack++;

					test[i].glVector3[0].x += 20.0;
					test[i].glVector3[0].y -= 20.0;

					test[i].glVector3[1].x -= 20.0;
					test[i].glVector3[1].y += 20.0;

					test[i].rGB[0].x -= 0.07;
					test[i].rGB[0].y -= 0.07;
					test[i].rGB[0].z -= 0.07;

				}



				//이동 모듈

				if (test[i].glVector3[0].y >= screenLTY ||
					test[i].glVector3[1].y <= screenRBY) {



					printf("왜바뀌는데 \n");

					test[i].yMoveSpeed *= -1;

				}
				if (test[i].glVector3[0].x <= screenLTX ||
					test[i].glVector3[1].x >= screenRBX) {


					printf("왜바뀌는데 \n");

					test[i].xMoveSpeed *= -1;
				}





				test[i].glVector3[0].x += test[i].xMoveSpeed;
				test[i].glVector3[0].y += test[i].yMoveSpeed;

				test[i].glVector3[1].x += test[i].xMoveSpeed;
				test[i].glVector3[1].y += test[i].yMoveSpeed;




			}

			else if (test[i].polygonNum == PKTr) {

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

	//printf("마우스 : %d,%d\n ", x, y);

}

void Mouse(int button, int state, int x, int y) {


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		printf("드래그 시작 : %d,%d\n", x, y);
		SetPolygon(GLVectorBasic((GLdouble)x, screenLTY - (GLdouble)y, 0), polygonKind);

	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

		printf("마우스를 뗀 장소 : %d,%d\n", x, y);
	}







}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
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
			if (test[i].activate) {



				if (test[i].xMoveSpeed >= 0) {
					test[i].xMoveSpeed = fabs(wholeSpeed * test[i].xMoveSpeedOriginal);
				}

				else
				{
					test[i].xMoveSpeed = -1 * fabs((wholeSpeed * test[i].xMoveSpeedOriginal));

				}

				if (test[i].yMoveSpeed >= 0) {
					test[i].yMoveSpeed = fabs(wholeSpeed * test[i].yMoveSpeedOriginal);
				}
				else {

					test[i].yMoveSpeed = -1 * fabs(wholeSpeed * test[i].yMoveSpeedOriginal);
				}

				printf("%f\n", test[i].xMoveSpeed);
				printf("%f\n", test[i].yMoveSpeed);
			}
		}
		break;
	case '-':
		printf("키보드입력 %c\n", key);
		WholeSpeedDown();

		for (int i = 0; i < objectNumLimit; ++i) {
			if (test[i].activate) {

				if (test[i].xMoveSpeed >= 0) {
					test[i].xMoveSpeed = fabs(wholeSpeed * test[i].xMoveSpeedOriginal);
				}

				else
				{
					test[i].xMoveSpeed = -1 * fabs((wholeSpeed * test[i].xMoveSpeedOriginal));

				}

				if (test[i].yMoveSpeed >= 0) {
					test[i].yMoveSpeed = fabs(wholeSpeed * test[i].yMoveSpeedOriginal);
				}
				else {

					test[i].yMoveSpeed = -1 * fabs(wholeSpeed * test[i].yMoveSpeedOriginal);
				}

				printf("%f\n", test[i].xMoveSpeed);
				printf("%f\n", test[i].yMoveSpeed);
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

		if (test[i].activate) {

			if (test[i].polygonNum == (int)PKRe) {

				glColor4f(test[i].rGB[0].x, test[i].rGB[0].y, test[i].rGB[0].z, 1.0);
				glRectd(test[i].glVector3[0].x, test[i].glVector3[0].y, test[i].glVector3[1].x, test[i].glVector3[1].y);


			}

			else if (test[i].polygonNum == (int)PKTr) {

				glColor4f(test[i].rGB[0].x, test[i].rGB[0].y, test[i].rGB[0].z, 1.0);
				glBegin(GL_POLYGON);

				glVertex3d(test[i].glVector3[0].x, test[i].glVector3[0].y, test[i].glVector3[0].z);
				glVertex3d(test[i].glVector3[1].x, test[i].glVector3[1].y, test[i].glVector3[1].z);
				glVertex3d(test[i].glVector3[2].x, test[i].glVector3[2].y, test[i].glVector3[2].z);
				glEnd();

			}

		}

	}







	glFlush(); // 화면에 출력하기

}

void DraggingShape(Test test) {



	glColor4f(test.rGB[0].x, test.rGB[0].y, test.rGB[0].z, 0.3f);

	glBegin(GL_POLYGON);






	glEnd();





}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

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




	return  PlusOrMinus() * (GLdouble)(((rand() % 10) / 10.0) + 0.001);



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
		timerFlag[0] = false;
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