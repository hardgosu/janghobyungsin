/*
* ================================================================
* example5.cpp
*
* glut라이브러리를 사용한 OpenGL의 샘플 프로그램 입니다.
* 리스트 사용방법에 대한 샘플입니다.
* ================================================================
*/

#include<gl/glut.h>

static GLfloat rot;		// 정육면체 회전각도
static GLuint cubelist;	// 정육면체 리스트

						//================================================================
						// 화면갱신 처리
						//================================================================
void display_func(void)
{
	// 화면과 딥버퍼를 지움
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 현재좌표계를 보존
	glPushMatrix();

	// 우선 좌표계을 화면의 안쪽으로 이동
	glTranslatef(0.0, 0.0, -15.0);
	// 좌표계를 Y축을 기준으로 회전
	glRotatef(rot, 0.0, 1.0, 0.0);

	// 1. 첫번째 정육면체를 그림. 현재 좌표계를 보존
	glPushMatrix();
	// 좌표계 변환
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(rot * 2, 1.0, 0.0, 0.0);
	glCallList(cubelist);
	// 첫번째 정육면체 완료. 좌표계를 원래대로 돌려놓음
	glPopMatrix();

	// 2. 두번째 정육면체를 그림. 현재 좌표계를 보존
	glPushMatrix();
	// 좌표계 변환
	glTranslatef(0.0, 0.0, 5.0);
	glRotatef(rot * 2, 1.0, 0.0, 0.0);
	glCallList(cubelist);
	// 두번째 정육면체 완료. 좌표계를 원래대로 돌려놓음
	glPopMatrix();

	// 좌표계를 원래대로 돌려놓음
	glPopMatrix();

	// 더블버퍼의 버퍼를 교체하여 화면을 갱신
	glutSwapBuffers();
}


//================================================================
// 정육면체 리스트를 작성
//================================================================
GLuint make_cube(void)
{
	GLint list;

	// 정육면체의 정점
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

	// 정육면체의 면의 색상
	static GLfloat color[][4] = {
		{ 1.0, 0.0, 0.0, 0.0 },
	{ 0.0, 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0, 0.0 },
	{ 0.0, 1.0, 1.0, 0.0 },
	{ 1.0, 0.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0, 0.0 },
	};

	// 새로운 리스트 번호를 얻는다.
	list = glGenLists(1);

	// 새로운 리스트를 작성
	glNewList(list, GL_COMPILE);

	// 정육면체를 그림
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

	// 리스트 작성 완료
	glEndList();

	return list;
}

//================================================================
// 윈도우 사이즈를 갱신할때 처리
//================================================================
void reshape_func(int width, int height)
{
	// 표시범위 설정
	glViewport(0, 0, width, height);

	// 투영방법 설정
	glMatrixMode(GL_PROJECTION);

	// 좌표변환 행렬의 초기화(단위행렬화)
	glLoadIdentity();

	// 투영범위를 설정
	glFrustum(-1.0, 1.0, -1.0, 1.0, 3.0, 10000.0);

	glMatrixMode(GL_MODELVIEW);
}

//================================================================
// 처리할 이벤트가 없을 때 호출되는 이벤트함수
// 정육면체의 회전각을 갱신한다.
//================================================================
void idle_func(void)
{
	// 시간을 얻어서 회전각도를 계산한다
	rot = 0.1*(GLfloat)glutGet(GLUT_ELAPSED_TIME);

	// 화면을 다시 그릴필요가 있다는것을 glut에게 알려줌
	glutPostRedisplay();
}

//================================================================
// 메인함수
//================================================================
int main(int argc, char *argv[])
{
	// glut의 초기화
	glutInit(&argc, argv);

	// 화면표시 설정
	// 3D표시를 하기때문에 딥버퍼를 사용한다.
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// 윈도우의 초기사이즈를 설정
	glutInitWindowSize(300, 300);

	// 윈도우를 생성
	glutCreateWindow("Sample 5");

	// 화면갱신용 함수를 등록
	glutDisplayFunc(display_func);

	// 윈도우사이즈를 변경했을때 함수를 등록
	glutReshapeFunc(reshape_func);

	// 이벤트가 없을때 처리 함수를 등록
	glutIdleFunc(idle_func);

	// 딥버퍼를 사용하도록 설정
	glEnable(GL_DEPTH_TEST);

	// 리스트를 작성
	cubelist = make_cube();

	// 이벤트처리를 시작
	glutMainLoop();

	return 0;
}
