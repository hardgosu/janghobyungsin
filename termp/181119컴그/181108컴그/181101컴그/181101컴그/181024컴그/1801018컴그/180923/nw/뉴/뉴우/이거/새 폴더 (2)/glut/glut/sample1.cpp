
#include "stdafx.h"

GLvoid drawScene(GLvoid); 
GLvoid Reshape(int w, int h);
void main(int argc, char *argv[]) {
	glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(250, 250); // �������� ũ�� ���� 
	glutCreateWindow("Example2"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(drawScene); // ��� �Լ��� ���� 
	glutReshapeFunc(Reshape);
	glutMainLoop();
} // ������ ��� �Լ� 
GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // �׸��� ���� 'green' ���� ���� 
	//glRectf(-0.5f, -0.5f, 0.5f, 0.5f); // �簢�� �׸���



	glBegin(GL_TRIANGLES);
	glVertex3f(0, 1, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(1, -1, 0);
	glEnd();


	glFlush(); // ȭ�鿡 ����ϱ�





}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}