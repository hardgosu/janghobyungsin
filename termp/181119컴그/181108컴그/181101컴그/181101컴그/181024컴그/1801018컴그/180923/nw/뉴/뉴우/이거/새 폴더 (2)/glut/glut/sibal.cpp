#include <gl/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
BITMAPINFO *m_bitInfo;   // 비트맵 헤더 저장할 변수
GLubyte *m_bitmap;   // 비트맵 데이터를 가리킬 포인터
GLuint texture[1];

void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void Timerfunction(int value);

struct POINT3D
{
	double x = 0, y = 0, z = 0;
};

void MakeXYZ();
void BaseCube();
void MakeMap_1();
void MakeMap_2();
void MakeMap_3();

POINT3D map_1[237];
POINT3D star_1[4];
POINT3D map_2[500];
POINT3D star_2[20];
POINT3D map_3[800];
POINT3D star_3[60];
int map1_index = 0, map2_index, map3_index;
int star1_index, star2_index, star3_index;

void RotateX(double x_, double y_, double z_, double Rtheta);
void RotateY(double x_, double y_, double z_, double Rtheta);
void RotateZ(double x_, double y_, double z_, double Rtheta);

POINT3D eye = { 0.0f, 0.0f, 2000.0f };
POINT3D eyeCopy = { 0.0f, 0.0f, 300.0f };
POINT3D up = { 0.0f, 1.0f, 0.0f };
POINT3D at = { 0.0f, 0.0f, -1.0f };

double vectorSize;

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Map");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);

	glutKeyboardFunc(Keyboard);                  // 키보드 입력 콜백 함수
	glutSpecialFunc(SpecialKeyboard);            // 키보드 입력 콜백 함수
	glutMouseFunc(Mouse);                     // 마우스 입력 콜백 함수
	glutPassiveMotionFunc(Motion);
	glutMotionFunc(Motion);                     // 마우스 이동 입력 콜백 함수
	glutTimerFunc(10, Timerfunction, 1);         // 타이머 함수 설정

	glEnable(GL_DEPTH_TEST);

	//m_bitmap = LoadDIBitmap("brick.bmp", &m_bitInfo);

	FILE *fp_map1 = NULL, *fp_star1, *fp_map2, *fp_star2, *fp_map3, *fp_star3;

	

	fopen_s(&fp_map1,"map1.txt", "r");

	while (fscanf_s(fp_map1, "%lf %lf %lf", &(map_1[map1_index].x), &(map_1[map1_index].y), &(map_1[map1_index].z)) != EOF)
	{

		printf("%f %f %f \n", map_1[map1_index].x, map_1[map1_index].y, map_1[map1_index].z);
		map1_index++;



	}
	




	fclose(fp_map1);

	

	/*

	fopen_s(&fp_star1, "star1.txt", "r");
	while (fscanf_s(fp_star1, "%lf %lf %lf", &(star_1[star1_index].x), &(star_1[star1_index].y), &(star_1[star1_index].z)) != EOF)
	{
		star1_index++;
	}
	fclose(fp_star1);


	fopen_s(&fp_map2, "map2.txt", "r");
	while (fscanf_s(fp_map2, "%lf %lf %lf", &(map_2[map2_index].x), &(map_2[map2_index].y), &(map_2[map2_index].z)) != EOF)
	{
		map2_index++;
	}
	fclose(fp_map2);

	fopen_s(&fp_star2, "star2.txt", "r");
	while (fscanf_s(fp_star2, "%lf %lf %lf", &(star_2[star2_index].x), &(star_2[star2_index].y), &(star_2[star2_index].z)) != EOF)
	{
		star2_index++;
	}
	fclose(fp_star2);

	fopen_s(&fp_map3, "map3.txt", "r");
	while (fscanf_s(fp_map3, "%lf %lf %lf", &(map_3[map3_index].x), &(map_3[map3_index].y), &(map_3[map3_index].z)) != EOF)
	{
		map3_index++;
	}
	fclose(fp_map3);

	fopen_s(&fp_star3, "star3.txt", "r");
	while (fscanf_s(fp_star3, "%lf %lf %lf", &(star_3[star3_index].x), &(star_3[star3_index].y), &(star_3[star3_index].z)) != EOF)
	{
		star3_index++;
	}
	fclose(fp_star3);

	*/

	glutMainLoop();

	//free(m_bitmap);
	//free(m_bitInfo);
}

GLvoid drawScene()
{
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glPushMatrix();

	MakeXYZ();


	glPushMatrix();

	MakeMap_1();
	//MakeMap_2();
	//MakeMap_3();

	glPopMatrix();



	glPopMatrix();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 3000.0); // projection mtx: Orthographic, Perspective

											// view mtx
	gluLookAt(eye.x, eye.y, eye.z,
		at.x, at.y, at.z,
		up.x, up.y, up.z);

	glMatrixMode(GL_MODELVIEW);
}

void MakeXYZ()
{
	glLineWidth(3.0);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1000, 0, 0);
	glVertex3f(1000, 0, 0);
	glEnd();
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, -1000, 0);
	glVertex3f(0, 1000, 0);
	glEnd();
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, -1000);
	glVertex3f(0, 0, 1000);
	glEnd();
	glLineWidth(1.0);
}

void MakeGround()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f(0.3f, 1.0f, 0.5f, 1.0f);
	glVertex3f(-150, 0, -150);
	glVertex3f(-150, 0, 150);
	glVertex3f(150, 0, 150);
	glVertex3f(150, 0, -150);
	glEnd();
	glPopMatrix();
}

void BaseCube()
{
	glPushMatrix();
	glColor4f(0.5f, 0.8f, 0.0f, 1.0f);

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	m_bitmap = LoadDIBitmap("brick.bmp", &m_bitInfo);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);      // 정면
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexCoord2f(1, 0);
	glVertex3d(-25, 25, 25);
	glTexCoord2f(0, 0);
	glVertex3d(-25, -25, 25);
	glTexCoord2f(0, 1);
	glVertex3d(25, -25, 25);
	glTexCoord2f(1, 1);
	glVertex3d(25, 25, 25);
	glEnd();

	glBegin(GL_QUADS);      // 후면
	glVertex3d(-25, 25, -25);
	glVertex3d(25, 25, -25);
	glVertex3d(25, -25, -25);
	glVertex3d(-25, -25, -25);
	glEnd();

	glBegin(GL_QUADS);      // 좌측
	glVertex3d(-25, 25, -25);
	glVertex3d(-25, -25, -25);
	glVertex3d(-25, -25, 25);
	glVertex3d(-25, 25, 25);
	glEnd();

	glBegin(GL_QUADS);      // 우측
	glVertex3d(25, 25, 25);
	glVertex3d(25, -25, 25);
	glVertex3d(25, -25, -25);
	glVertex3d(25, 25, -25);
	glEnd();

	glBegin(GL_QUADS);      // 상단
	glVertex3d(-25, 25, -25);
	glVertex3d(-25, 25, 25);
	glVertex3d(25, 25, 25);
	glVertex3d(25, 25, -25);
	glEnd();

	glBegin(GL_QUADS);      // 하단
	glVertex3d(-25, -25, 25);
	glVertex3d(-25, -25, -25);
	glVertex3d(25, -25, -25);
	glVertex3d(25, -25, 25);
	glEnd();




	glLineWidth(3.0f);
	glColor4f(1.f, 1.f, 1.f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-25, 25, 25);
	glVertex3f(-25, -25, 25);
	glVertex3f(25, -25, 25);
	glVertex3f(25, 25, 25);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(-25, 25, -25);
	glVertex3f(25, 25, -25);
	glVertex3f(25, -25, -25);
	glVertex3f(-25, -25, -25);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-25, 25, 25);
	glVertex3f(-25, 25, -25);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(25, 25, 25);
	glVertex3f(25, 25, -25);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-25, -25, 25);
	glVertex3f(-25, -25, -25);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(25, -25, 25);
	glVertex3f(25, -25, -25);
	glEnd();
	glPopMatrix();
}

void MakeMap_1()
{
	for (int i = 0; i < map1_index; i++)
	{
		glPushMatrix();
		glTranslated(map_1[i].x, map_1[i].y, map_1[i].z);
		BaseCube();
		glPopMatrix();
	}

	for (int i = 0; i < star1_index; i++)
	{
		glPushMatrix();
		glColor4f(1, 1, 0, 1);
		glTranslated(star_1[i].x, star_1[i].y, star_1[i].z);
		glutSolidSphere(25, 10, 10);
		glPopMatrix();
	}
}

void MakeMap_2()
{
	for (int i = 0; i < map2_index; i++)
	{
		glPushMatrix();
		glTranslated(map_2[i].x, map_2[i].y, map_2[i].z);
		BaseCube();
		glPopMatrix();
	}

	for (int i = 0; i < star2_index; i++)
	{
		glPushMatrix();
		glColor4f(1, 1, 0, 1);
		glTranslated(star_2[i].x, star_2[i].y, star_2[i].z);
		glutSolidSphere(25, 10, 10);
		glPopMatrix();
	}
}

void MakeMap_3()
{
	for (int i = 0; i < map3_index; i++)
	{
		glPushMatrix();
		glTranslated(map_3[i].x, map_3[i].y, map_3[i].z);
		BaseCube();
		glPopMatrix();
	}

	for (int i = 0; i < star3_index; i++)
	{
		glPushMatrix();
		glColor4f(1, 1, 0, 1);
		glTranslated(star_3[i].x, star_3[i].y, star_3[i].z);
		glutSolidSphere(25, 10, 10);
		glPopMatrix();
	}
}

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{


	FILE *fp;
	GLubyte *bits;

	int bitsize;
	int infosize;
	BITMAPFILEHEADER header;

	if ((fopen_s(&fp, filename, "rb")) == NULL)   // 비트맵 파일을 바이너리 모드로 연다.
		return NULL;

	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)   // 비트맵의 헤더 정보를 읽는다.
	{
		fclose(fp);
		return NULL;
	}

	if (header.bfType != 'MB')      // 만일 비트맵이 아니라면 실행을 중지한다.
	{
		fclose(fp);
		return NULL;
	}

	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);      // BITMAPINFO의 위치를 계산한다.

	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
	{
		fclose(fp);
		return NULL;
	}

	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize)      // BITMAPINFO를 읽는다.
	{
		free(*info);
		fclose(fp);
		return NULL;
	}

	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)      // 비트맵 이미지의 크기를 계산한다.
	{
		bitsize = ((*info)->bmiHeader.biWidth *
			(*info)->bmiHeader.biBitCount + 7) / 8 *
			abs((*info)->bmiHeader.biHeight);
	}

	if ((bits = (unsigned char*)malloc(bitsize)) == NULL)      // 비트맵 데이터를 읽고 파일을 닫는다.
	{
		free(*info);
		fclose(fp);
		return NULL;
	}

	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize)
	{
		free(*info);
		free(bits);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return bits;
}

void RotateX(double x_, double y_, double z_, double Rtheta)
{
	eye.x = x_;
	eye.y = y_ * cos(Rtheta) - z_ * sin(Rtheta);
	eye.z = y_ * sin(Rtheta) + z_ * cos(Rtheta);
	printf("eye.x : %lf,     eye.y : %lf,     eye.z : %lf\n", eye.x, eye.y, eye.z);
	printf("at.x : %lf,     at.y : %lf,     at.z : %lf\n", at.x, at.y, at.z);
}

void RotateY(double x_, double y_, double z_, double Rtheta)
{
	eye.x = x_ * cos(Rtheta) + z_ * sin(Rtheta);
	eye.y = y_;
	eye.z = -x_ * sin(Rtheta) + z_ * cos(Rtheta);
	printf("eye.x : %lf,     eye.y : %lf,     eye.z : %lf\n", eye.x, eye.y, eye.z);
	printf("at.x : %lf,     at.y : %lf,     at.z : %lf\n", at.x, at.y, at.z);
}

void RotateZ(double x_, double y_, double z_, double Rtheta)
{
	eye.x = x_ * cos(Rtheta) - y_ * sin(Rtheta);
	eye.y = x_ * sin(Rtheta) + y_ * cos(Rtheta);
	eye.z = z_;
	printf("eye.x : %lf,     eye.y : %lf,     eye.z : %lf\n", eye.x, eye.y, eye.z);
	printf("at.x : %lf,     at.y : %lf,     at.z : %lf\n", at.x, at.y, at.z);
}

void Keyboard(unsigned char key, int X_, int Y_)
{
	switch (key)
	{
	case 'q':
		exit(1);
		break;
	case 'x':
		RotateX(eye.x, eye.y, eye.z, 0.1);
		break;
	case 'X':
		RotateX(eye.x, eye.y, eye.z, -0.1);
		break;
	case 'y':
		RotateY(eye.x, eye.y, eye.z, 0.1);
		break;
	case 'Y':
		RotateY(eye.x, eye.y, eye.z, -0.1);
		break;
	case 'z':
		RotateZ(eye.x, eye.y, eye.z, 0.1);
		break;
	case 'Z':
		RotateZ(eye.x, eye.y, eye.z, -0.1);
		break;
	case 'w':
		eye.y += 10;
		printf("eye.x : %lf,     eye.y : %lf,     eye.z : %lf\n", eye.x, eye.y, eye.z);
		break;
	case 's':
		eye.y -= 10;
		printf("eye.x : %lf,     eye.y : %lf,     eye.z : %lf\n", eye.x, eye.y, eye.z);
		break;
	case 'a':
		eye.x -= 10;
		printf("eye.x : %lf,     eye.y : %lf,     eye.z : %lf\n", eye.x, eye.y, eye.z);
		break;
	case 'd':
		eye.x += 10;
		printf("eye.x : %lf,     eye.y : %lf,     eye.z : %lf\n", eye.x, eye.y, eye.z);
		break;
	case '+':
		eye.z += 10;
		printf("eye.x : %lf,     eye.y : %lf,     eye.z : %lf\n", eye.x, eye.y, eye.z);
		break;
	case '-':
		eye.z -= 10;
		printf("eye.x : %lf,     eye.y : %lf,     eye.z : %lf\n", eye.x, eye.y, eye.z);
		break;

	case 'n':      // 줌 인
		eyeCopy.x = fabs(eye.x);
		eyeCopy.y = fabs(eye.y);
		eyeCopy.z = fabs(eye.z);

		vectorSize = sqrt(pow(eyeCopy.x, 2) + pow(eyeCopy.y, 2) + pow(eyeCopy.z, 2));

		eyeCopy.x = eyeCopy.x / vectorSize;
		eyeCopy.y = eyeCopy.y / vectorSize;
		eyeCopy.z = eyeCopy.z / vectorSize;

		if (fabs(eyeCopy.x) > 0)
			eye.x -= eyeCopy.x * 10;
		else
			eye.x += eyeCopy.x * 10;
		if (fabs(eyeCopy.y) > 0)
			eye.y -= eyeCopy.y * 10;
		else
			eye.y += eyeCopy.y * 10;
		if (fabs(eyeCopy.z) > 0)
			eye.z -= eyeCopy.z * 10;
		else
			eye.z += eyeCopy.z * 10;


		printf("eye.x : %lf,     eye.y : %lf,     eye.z : %lf\n", eye.x, eye.y, eye.z);
		break;
	case 'm':      // 줌 아웃
		eyeCopy.x = fabs(eye.x);
		eyeCopy.y = fabs(eye.y);
		eyeCopy.z = fabs(eye.z);

		vectorSize = sqrt(pow(eyeCopy.x, 2) + pow(eyeCopy.y, 2) + pow(eyeCopy.z, 2));

		eyeCopy.x = eyeCopy.x / vectorSize;
		eyeCopy.y = eyeCopy.y / vectorSize;
		eyeCopy.z = eyeCopy.z / vectorSize;

		if (fabs(eyeCopy.x) > 0)
			eye.x += eyeCopy.x * 10;
		else
			eye.x -= eyeCopy.x * 10;
		if (fabs(eyeCopy.y) > 0)
			eye.y += eyeCopy.y * 10;
		else
			eye.y -= eyeCopy.y * 10;
		if (fabs(eyeCopy.z) > 0)
			eye.z += eyeCopy.z * 10;
		else
			eye.z -= eyeCopy.z * 10;

		printf("eye.x : %lf,     eye.y : %lf,     eye.z : %lf\n", eye.x, eye.y, eye.z);
		break;
	case 'i':      // 초기화
		eye.x = 0, eye.y = 0, eye.z = 700;
		break;
	}
	Reshape(800, 600);
	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y)      // esc, backspace, delete : ASCII
{

	//   glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
	}

	//glutPostRedisplay();
}

void Motion(int x, int y)
{

	//glutPostRedisplay();
}

void Timerfunction(int value)         // 이 함수는 한 번만 실행되므로 지속적인 애니메이션을 위해서는
{                              // 타이머 함수 내에 타이머를 다시 호출해야 한다.




	glutPostRedisplay();                  // 화면 재출력
	glutTimerFunc(10, Timerfunction, 1);      // 타이머함수 재설정
}