// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// glut.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

void BeautifulTriangle();

// TODO: 필요한 추가 헤더는
// 이 파일이 아닌 STDAFX.H에서 참조합니다.


class Draw {

public:
	Draw() {


	}

	void BeautifulTriangle() {
		glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex2f(-200, -200);
		glColor3f(0, 1, 0);
		glVertex2f(200, -200);
		glColor3f(0, 0, 1);
		glVertex2f(0, 200);
		glEnd();

	}

};

void BeautifulTriangle() {
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(-200, -200);
	glColor3f(0, 1, 0);
	glVertex2f(200, -200);
	glColor3f(0, 0, 1);
	glVertex2f(0, 200);
	glEnd();

}