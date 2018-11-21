
#include "stdafx.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLdouble screenLTX = -400;
GLdouble screenRBX = 400;
GLdouble screenRBY = 400;
GLdouble screenLTY = -400;

int widthNum = 33;
int heightNum = 33;


void glOrtho2(GLdouble, GLdouble, GLdouble, GLdouble);
void DrawGraph(GLdouble leftX, GLdouble leftY, GLdouble width, GLdouble height, int row, int column);

void main(int argc, char *argv[]) {
	srand((unsigned)time(NULL));


	glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 800); // 윈도우의 크기 지정 
	glutCreateWindow("Example2"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정 
	glutReshapeFunc(Reshape);
	glutMainLoop();
} // 윈도우 출력 함수 
GLvoid drawScene(GLvoid) {




	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 

								  //glRectf(-0.5f, -0.5f, 0.5f, 0.5f); // 사각형 그리기

	glColor4f(0.7f, 0.2f, 0.0f, 1.0f);



	DrawGraph(-200, 200, 500, 500, 3, 3);






	glFlush(); // 화면에 출력하기

}




void glOrtho2(GLdouble leftX, GLdouble leftY, GLdouble rightX, GLdouble rightY) {

	glOrtho(leftX, rightX, leftY, rightY, -1.0, 1.0);
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glOrtho2(screenLTX, screenLTY, screenRBX, screenRBY);

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