
#include "stdafx.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void main(int argc, char *argv[]) {
	glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example2"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(drawScene); // ��� �Լ��� ���� 
	glutReshapeFunc(Reshape);
	glutMainLoop();
} // ������ ��� �Լ� 
GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

									   //glRectf(-0.5f, -0.5f, 0.5f, 0.5f); // �簢�� �׸���

	glColor4f(0.0f, 0.2f, 0.0f, 1.0f);

	glBegin(GL_LINES);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, -1, 0);
	glEnd();


	glColor4f(0.5f, 0.3f, 0.2f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3d(-0.1, -0.1, 0);
	glVertex3d(0.1, -0.1, 0);
	glVertex3d(0, 0.1, 0);
	glEnd();


	glColor4f(0.5f, 0.2f, 0.8f, 1.0f);

	glRectf(-1, 1, -0.75, 0.7);

	glFlush(); // ȭ�鿡 ����ϱ�

}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}