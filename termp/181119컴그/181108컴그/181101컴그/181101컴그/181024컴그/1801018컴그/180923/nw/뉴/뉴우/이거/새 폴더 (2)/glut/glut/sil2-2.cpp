#include "stdafx.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLdouble screenLTX = -400;
GLdouble screenRBX = 400;
GLdouble screenRBY = 400;
GLdouble screenLTY = -400;

int widthNum = 60;
int heightNum = 60;


void glOrtho2(GLdouble, GLdouble, GLdouble, GLdouble);


void main(int argc, char *argv[]) {
	srand((unsigned)time(NULL));

	widthNum = (rand() % 80) + 20;
	heightNum = (rand() % 80) + 20;
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

	GLdouble r = (rand() % 100) / 100.0f;
	GLdouble g = (rand() % 100) / 100.0f;
	GLdouble b = (rand() % 100) / 100.0f;

	for (int i = 0; i < heightNum; ++i) {

		for (int j = 0; j < widthNum; ++j) {
			//glColor4f((rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, 1.0f);



			glColor4f(r + (((1 - r) / widthNum) * (j + 1)), g + (((1 - g) / widthNum) * (j + 1)), b + (((1 - b) / widthNum) * (j + 1)), 1.0f);


			glRectf(screenLTX + (j *(fabs(screenLTX - screenRBX) / widthNum)), (screenLTY + (i *(fabs(screenLTY - screenRBY) / heightNum))), screenLTX + ((j + 1) *(fabs(screenLTX - screenRBX) / widthNum)), (screenLTY + ((i + 1) *(fabs(screenLTY - screenRBY) / heightNum))));


		}
		r = (rand() % 100) / 100.0f;
		g = (rand() % 100) / 100.0f;
		b = (rand() % 100) / 100.0f;

	}




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