#include "stdafx.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLdouble screenLTX = -400;
GLdouble screenRBX = 400;
GLdouble screenRBY = -400;
GLdouble screenLTY = 400;

int widthNum = 60;
int heightNum = 60;


GLUquadric *sphere; // object 선언

void glOrtho2(GLdouble, GLdouble, GLdouble, GLdouble);
void Start();
void Timer1(int value);
void main(int argc, char *argv[]) {
	srand((unsigned)time(NULL));

	widthNum = (rand() % 80) + 20;
	heightNum = (rand() % 80) + 20;
	glutInit(&argc, argv); glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 800); // 윈도우의 크기 지정 
	glutCreateWindow("Example2"); // 윈도우 생성 (윈도우 이름) 


	glutDisplayFunc(drawScene); // 출력 함수의 지정 

	glutReshapeFunc(Reshape);
	glutTimerFunc(100, Timer1, 1);
	Start();

	glutMainLoop();
} // 윈도우 출력 함수 

void Timer1(int value) {

	glutPostRedisplay();
	if (true) {
		glutTimerFunc(1000 / 60, Timer1, value);
	}
}


GLvoid drawScene(GLvoid) {





	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 

	glLoadIdentity();
	//glRectf(-0.5f, -0.5f, 0.5f, 0.5f); // 사각형 그리기
	glShadeModel(GL_SMOOTH);

	glTranslated(0.0, 0.0, -0.1);


	//sphere = gluNewQuadric(); // object 생성
	//gluSphere(sphere, 420.0f, 50, 10);  // sphere 그리기

	

	glBegin(GL_POLYGON);

	glVertex3d(-100, -100,-20);
	glVertex3d(100, -100,-20);
	glVertex3d(100, 100,-20);
	glVertex3d(-100, 100,-20);

	glEnd();




	glFlush();
	glutSwapBuffers(); // 화면에 출력하기

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

	glClearColor(0.0, 0.0, 0.0, 1.0); // 바탕색을 'blue' 로 지정
	glColor3f(1.0, 0.0, 0.0);
}


