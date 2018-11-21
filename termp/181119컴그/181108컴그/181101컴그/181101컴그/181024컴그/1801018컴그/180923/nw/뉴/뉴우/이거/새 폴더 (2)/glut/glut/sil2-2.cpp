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
	glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 800); // �������� ũ�� ���� 
	glutCreateWindow("Example2"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(drawScene); // ��� �Լ��� ���� 
	glutReshapeFunc(Reshape);
	glutMainLoop();
} // ������ ��� �Լ� 
GLvoid drawScene(GLvoid) {




	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

								  //glRectf(-0.5f, -0.5f, 0.5f, 0.5f); // �簢�� �׸���

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




	glFlush(); // ȭ�鿡 ����ϱ�

}


void glOrtho2(GLdouble leftX, GLdouble leftY, GLdouble rightX, GLdouble rightY) {

	glOrtho(leftX, rightX, leftY, rightY, -1.0, 1.0);
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glOrtho2(screenLTX, screenLTY, screenRBX, screenRBY);

}