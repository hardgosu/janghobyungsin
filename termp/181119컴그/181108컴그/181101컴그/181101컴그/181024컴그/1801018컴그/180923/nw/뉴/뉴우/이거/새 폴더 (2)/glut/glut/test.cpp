#include "stdafx.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLdouble screenLTX = -400;
GLdouble screenRBX = 400;
GLdouble screenRBY = -400;
GLdouble screenLTY = 400;

int widthNum = 60;
int heightNum = 60;


GLUquadric *sphere; // object ����

void glOrtho2(GLdouble, GLdouble, GLdouble, GLdouble);
void Start();
void Timer1(int value);
void main(int argc, char *argv[]) {
	srand((unsigned)time(NULL));

	widthNum = (rand() % 80) + 20;
	heightNum = (rand() % 80) + 20;
	glutInit(&argc, argv); glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 800); // �������� ũ�� ���� 
	glutCreateWindow("Example2"); // ������ ���� (������ �̸�) 


	glutDisplayFunc(drawScene); // ��� �Լ��� ���� 

	glutReshapeFunc(Reshape);
	glutTimerFunc(100, Timer1, 1);
	Start();

	glutMainLoop();
} // ������ ��� �Լ� 

void Timer1(int value) {

	glutPostRedisplay();
	if (true) {
		glutTimerFunc(1000 / 60, Timer1, value);
	}
}


GLvoid drawScene(GLvoid) {





	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	glLoadIdentity();
	//glRectf(-0.5f, -0.5f, 0.5f, 0.5f); // �簢�� �׸���
	glShadeModel(GL_SMOOTH);

	glTranslated(0.0, 0.0, -0.1);


	//sphere = gluNewQuadric(); // object ����
	//gluSphere(sphere, 420.0f, 50, 10);  // sphere �׸���

	

	glBegin(GL_POLYGON);

	glVertex3d(-100, -100,-20);
	glVertex3d(100, -100,-20);
	glVertex3d(100, 100,-20);
	glVertex3d(-100, 100,-20);

	glEnd();




	glFlush();
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�

}




void glOrtho2(GLdouble leftX, GLdouble leftY, GLdouble rightX, GLdouble rightY) {

	glOrtho(leftX, rightX, rightY, leftY, -1.0, 1.0);
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//printf("aasdzz");

	glOrtho2(screenLTX, screenLTY, screenRBX, screenRBY);

	gluPerspective(60, 1, 2.0, 50.0);
	glMatrixMode(GL_MODELVIEW);


}

void Start() {

	glClearColor(0.0, 0.0, 0.0, 1.0); // �������� 'blue' �� ����
	glColor3f(1.0, 0.0, 0.0);
}


