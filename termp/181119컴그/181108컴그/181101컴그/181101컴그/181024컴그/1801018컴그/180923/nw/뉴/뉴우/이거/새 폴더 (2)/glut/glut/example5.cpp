/*
* ================================================================
* example5.cpp
*
* glut���̺귯���� ����� OpenGL�� ���� ���α׷� �Դϴ�.
* ����Ʈ ������� ���� �����Դϴ�.
* ================================================================
*/

#include<gl/glut.h>

static GLfloat rot;		// ������ü ȸ������
static GLuint cubelist;	// ������ü ����Ʈ

						//================================================================
						// ȭ�鰻�� ó��
						//================================================================
void display_func(void)
{
	// ȭ��� �����۸� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ������ǥ�踦 ����
	glPushMatrix();

	// �켱 ��ǥ���� ȭ���� �������� �̵�
	glTranslatef(0.0, 0.0, -15.0);
	// ��ǥ�踦 Y���� �������� ȸ��
	glRotatef(rot, 0.0, 1.0, 0.0);

	// 1. ù��° ������ü�� �׸�. ���� ��ǥ�踦 ����
	glPushMatrix();
	// ��ǥ�� ��ȯ
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(rot * 2, 1.0, 0.0, 0.0);
	glCallList(cubelist);
	// ù��° ������ü �Ϸ�. ��ǥ�踦 ������� ��������
	glPopMatrix();

	// 2. �ι�° ������ü�� �׸�. ���� ��ǥ�踦 ����
	glPushMatrix();
	// ��ǥ�� ��ȯ
	glTranslatef(0.0, 0.0, 5.0);
	glRotatef(rot * 2, 1.0, 0.0, 0.0);
	glCallList(cubelist);
	// �ι�° ������ü �Ϸ�. ��ǥ�踦 ������� ��������
	glPopMatrix();

	// ��ǥ�踦 ������� ��������
	glPopMatrix();

	// ��������� ���۸� ��ü�Ͽ� ȭ���� ����
	glutSwapBuffers();
}


//================================================================
// ������ü ����Ʈ�� �ۼ�
//================================================================
GLuint make_cube(void)
{
	GLint list;

	// ������ü�� ����
	static GLfloat vert[][4] = {
		{ 1.0,  1.0,  1.0 },
	{ -1.0,  1.0,  1.0 },
	{ -1.0, -1.0,  1.0 },
	{ 1.0, -1.0,  1.0 },
	{ 1.0,  1.0, -1.0 },
	{ -1.0,  1.0, -1.0 },
	{ -1.0, -1.0, -1.0 },
	{ 1.0, -1.0, -1.0 },
	};

	// ������ü�� ���� ����
	static GLfloat color[][4] = {
		{ 1.0, 0.0, 0.0, 0.0 },
	{ 0.0, 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0, 0.0 },
	{ 0.0, 1.0, 1.0, 0.0 },
	{ 1.0, 0.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0, 0.0 },
	};

	// ���ο� ����Ʈ ��ȣ�� ��´�.
	list = glGenLists(1);

	// ���ο� ����Ʈ�� �ۼ�
	glNewList(list, GL_COMPILE);

	// ������ü�� �׸�
	glBegin(GL_QUADS);
	glColor3fv(color[0]);
	glVertex3fv(vert[0]);
	glVertex3fv(vert[1]);
	glVertex3fv(vert[2]);
	glVertex3fv(vert[3]);

	glColor3fv(color[1]);
	glVertex3fv(vert[4]);
	glVertex3fv(vert[5]);
	glVertex3fv(vert[6]);
	glVertex3fv(vert[7]);

	glColor3fv(color[2]);
	glVertex3fv(vert[0]);
	glVertex3fv(vert[1]);
	glVertex3fv(vert[5]);
	glVertex3fv(vert[4]);

	glColor3fv(color[3]);
	glVertex3fv(vert[2]);
	glVertex3fv(vert[3]);
	glVertex3fv(vert[7]);
	glVertex3fv(vert[6]);

	glColor3fv(color[4]);
	glVertex3fv(vert[3]);
	glVertex3fv(vert[0]);
	glVertex3fv(vert[4]);
	glVertex3fv(vert[7]);

	glColor3fv(color[5]);
	glVertex3fv(vert[1]);
	glVertex3fv(vert[2]);
	glVertex3fv(vert[6]);
	glVertex3fv(vert[5]);
	glEnd();

	// ����Ʈ �ۼ� �Ϸ�
	glEndList();

	return list;
}

//================================================================
// ������ ����� �����Ҷ� ó��
//================================================================
void reshape_func(int width, int height)
{
	// ǥ�ù��� ����
	glViewport(0, 0, width, height);

	// ������� ����
	glMatrixMode(GL_PROJECTION);

	// ��ǥ��ȯ ����� �ʱ�ȭ(�������ȭ)
	glLoadIdentity();

	// ���������� ����
	glFrustum(-1.0, 1.0, -1.0, 1.0, 3.0, 10000.0);

	glMatrixMode(GL_MODELVIEW);
}

//================================================================
// ó���� �̺�Ʈ�� ���� �� ȣ��Ǵ� �̺�Ʈ�Լ�
// ������ü�� ȸ������ �����Ѵ�.
//================================================================
void idle_func(void)
{
	// �ð��� �� ȸ�������� ����Ѵ�
	rot = 0.1*(GLfloat)glutGet(GLUT_ELAPSED_TIME);

	// ȭ���� �ٽ� �׸��ʿ䰡 �ִٴ°��� glut���� �˷���
	glutPostRedisplay();
}

//================================================================
// �����Լ�
//================================================================
int main(int argc, char *argv[])
{
	// glut�� �ʱ�ȭ
	glutInit(&argc, argv);

	// ȭ��ǥ�� ����
	// 3Dǥ�ø� �ϱ⶧���� �����۸� ����Ѵ�.
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// �������� �ʱ����� ����
	glutInitWindowSize(300, 300);

	// �����츦 ����
	glutCreateWindow("Sample 5");

	// ȭ�鰻�ſ� �Լ��� ���
	glutDisplayFunc(display_func);

	// ���������� ���������� �Լ��� ���
	glutReshapeFunc(reshape_func);

	// �̺�Ʈ�� ������ ó�� �Լ��� ���
	glutIdleFunc(idle_func);

	// �����۸� ����ϵ��� ����
	glEnable(GL_DEPTH_TEST);

	// ����Ʈ�� �ۼ�
	cubelist = make_cube();

	// �̺�Ʈó���� ����
	glutMainLoop();

	return 0;
}
