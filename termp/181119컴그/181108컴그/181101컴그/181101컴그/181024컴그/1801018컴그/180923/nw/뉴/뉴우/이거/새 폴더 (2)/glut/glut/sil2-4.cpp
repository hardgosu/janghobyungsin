
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


	}
	Test(GLVector3List vector3List, bool state) {


		for (int i = 0; i < vector3List.Length(); ++i) {
			this->glVector3[i].x = vector3List.GetDataOfIndex(i).x;
			this->glVector3[i].y = vector3List.GetDataOfIndex(i).y;
			this->glVector3[i].z = vector3List.GetDataOfIndex(i).z;


			this->original[i].x = vector3List.GetDataOfIndex(i).x;
			this->original[i].y = vector3List.GetDataOfIndex(i).y;
			this->original[i].z = vector3List.GetDataOfIndex(i).z;
		}


		this->activate = state;

	}



	int stack = 0;
	GLVectorBasic original[100];
	GLVectorBasic glVector3[100];
	GLVectorBasic rGB[100];
	GLVectorBasic rGBOriginal[100];

	bool activate;

};
static GLVector3List vector3List[objectNumLimit];
static Test test[objectNumLimit];
static bool timerFlag[objectNumLimit];

static int poolingNum = 0;






void glOrtho2(GLdouble, GLdouble, GLdouble, GLdouble);
void DrawGraph(GLdouble leftX, GLdouble leftY, GLdouble width, GLdouble height, int row, int column);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);





void main(int argc, char *argv[]) {
	srand((unsigned)time(NULL));


	glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example2"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정 

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);



	glutMainLoop();
} // 윈도우 출력 함수 








void TimerFunction(int value) {



	if (value < objectNumLimit) {

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




	glutPostRedisplay();


	glutTimerFunc(100, TimerFunction, value);





}

void Mouse(int button, int state, int x, int y) {


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {



		if (poolingNum >= objectNumLimit) {

			poolingNum = 0;

		}

		if (poolingNum < objectNumLimit) {


			vector3List[poolingNum].RemoveAll();

			int size = (rand() % 100) + 20;

			GLVectorBasic glvector3[2] = {
				GLVectorBasic((GLdouble)x, screenLTY - (GLdouble)y, 0.0),
				GLVectorBasic((GLdouble)x + size, screenLTY - (GLdouble)y - size, 0.0)

			};

			GLVectorBasic glRGB = GLVectorBasic((rand() % 10 / 10.0), (rand() % 10 / 10.0), (rand() % 10 / 10.0));


			for (int i = 0; i < 2; ++i) {
				vector3List[poolingNum].Add(glvector3[i]);
			}



			test[poolingNum] = Test(vector3List[poolingNum], true);

			test[poolingNum].rGB[0] = glRGB;
			test[poolingNum].rGBOriginal[0] = glRGB;


			if (timerFlag[poolingNum] == false) {
				glutTimerFunc(100, TimerFunction, poolingNum);

				timerFlag[poolingNum] = true;
			}
			poolingNum++;



		}



	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

	}







}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 't':
		break;
	case 'r':
		break;
	}


}

GLvoid drawScene(GLvoid) {




	glClearColor(0.2f, 0.0f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 

								  //glRectf(-0.5f, -0.5f, 0.5f, 0.5f); // 사각형 그리기

	glColor4f(0.7f, 0.2f, 0.0f, 1.0f);

	for (int i = 0; i < objectNumLimit; ++i) {

		if (test[i].activate) {
			glColor4f(test[i].rGB[0].x, test[i].rGB[0].y, test[i].rGB[0].z, 1.0);
			glRectd(test[i].glVector3[0].x, test[i].glVector3[0].y, test[i].glVector3[1].x, test[i].glVector3[1].y);
		}
		//printf("%d\n", test[i].activate);
		//printf("i : %d x : %f y : %f\n", i, vector3List[i].GetDataOfIndex(i).x, vector3List[i].GetDataOfIndex(i).y);
	}



	//printf("%d\n", mousePositionX);
	//printf("%d\n", mousePositionY);

	glFlush(); // 화면에 출력하기

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

	if (row == 0 || column == 0) {
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