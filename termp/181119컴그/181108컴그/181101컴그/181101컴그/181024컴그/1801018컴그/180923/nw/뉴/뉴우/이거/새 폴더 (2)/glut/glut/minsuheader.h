#pragma once
#pragma once
#include <gl/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <float.h>

#define MY_WINDOW_WIDTH      800.f
#define MY_WINDOW_HEIGHT   600.f

#define MAX_WINDOW_X      800.f
#define MIN_WINDOW_X      0.f

#define MAX_WINDOW_Y      600.f
#define MIN_WINDOW_Y      0.f

#define MAX_WINDOW_Z      400.f
#define MIN_WINDOW_Z      -400.f

#define GROUND_SIZE         300.f

#define PI 3.1415926535f

struct Vector
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

GLfloat dotproduct(Vector a, Vector b);
GLvoid normalize(Vector* v);
GLfloat getNorm(Vector v);
GLfloat getDistance(Vector a, Vector b);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void timerfunction(int value);
void mousemovefunction(int button, int state, int x, int y);
void keydownfunction(unsigned char key, int x, int y);

/*
<<   �������� �ǽ� �䱸����   >>

1.   ���� ���۸� ���� (�ǽ� 11������ ���� ����)
glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
�Լ� ����� �κп��� glutSwapBuffers(); ȣ��

2.   �� �࿡ ���� ȸ�� �� �̵� ��� (������ ��� ��� �����ϵ���, ���������� �ǽ� 11������ ���� ����)

��� �ǽ��� glOrtho(0.0, 800.0, 0.0, 600.0, -400.0, 400.0); �� z�� ������ �ο��ϵ��� �Ѵ�.
*/