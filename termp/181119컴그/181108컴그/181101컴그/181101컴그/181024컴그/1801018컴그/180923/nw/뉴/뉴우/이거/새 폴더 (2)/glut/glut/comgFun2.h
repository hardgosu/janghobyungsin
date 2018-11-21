#pragma once
#include "comgFun3.h"
#include "stdafx.h"

#define M_E        2.71828182845904523536   // e
#define M_LOG2E    1.44269504088896340736   // log2(e)
#define M_LOG10E   0.434294481903251827651  // log10(e)
#define M_LN2      0.693147180559945309417  // ln(2)
#define M_LN10     2.30258509299404568402   // ln(10)
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_PI_4     0.785398163397448309616  // pi/4
#define M_1_PI     0.318309886183790671538  // 1/pi
#define M_2_PI     0.636619772367581343076  // 2/pi
#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#define M_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)



class Rect {

public:
	Rect() {
		leftTop.x = 0;
		leftTop.y = 100;


		width = 100;

		height = 100;

		rightBottom.x = leftTop.x + width;
		rightBottom.y = leftTop.y - height;



		center.x = leftTop.x + (rightBottom.x - leftTop.x) / 2;

		center.y = rightBottom.y + (leftTop.y - rightBottom.y) / 2;

	}
	Rect(int x1, int y1, int width, int height) {


		this->width = abs(width);
		this->height = abs(height);


		this->leftTop.x = x1;
		this->leftTop.y = y1;

		this->rightBottom.x = this->leftTop.x + this->width;
		this->rightBottom.y = this->leftTop.y - this->height;


		center.x = leftTop.x + (this->width / 2);

		center.y = leftTop.y - (this->height / 2);

	}
	int width;
	int height;
	Position2 center;

	Position2 LeftTop() {
		Calculate();
		return leftTop;
	}

	Position2 RightBottom() {
		Calculate();
		return rightBottom;
	}

	void Calculate() {

		leftTop.x = center.x - (width / 2);

		leftTop.y = center.y + (height / 2);

		rightBottom.x = leftTop.x + width;
		rightBottom.y = leftTop.y - height;
	}


private:


	Position2 leftTop;
	Position2 rightBottom;

};

class Circle {

public:

	Circle() {

		center.x = 0;
		center.y = 0;

		radius = 100;

		top.y = center.y + radius;
		top.x = center.x;

		right.x = center.x + radius;
		right.y = center.y;

		left.x = center.x - radius;
		left.y = center.y;

		bottom.x = center.x;

		bottom.y = center.y - radius;


	}



	Circle(int centerX, int centerY, int radius) {

		center.x = centerX;
		center.y = centerY;

		this->radius = radius;

		top.y = center.y + radius;
		top.x = center.x;

		right.x = center.x + radius;
		right.y = center.y;

		left.x = center.x - radius;
		left.y = center.y;

		bottom.x = center.x;

		bottom.y = center.y - radius;


	}




	Position2 Top() {

		Calculate();

		return this->top;
	}
	Position2 Left() {
		Calculate();

		return this->left;

	}
	Position2 Right() {

		Calculate();

		return this->right;
	}
	Position2 Bottom() {
		Calculate();

		return this->bottom;

	}



	int radius;
	Position2 center;
private:

	Position2 top;
	Position2 left;
	Position2 right;
	Position2 bottom;

	void Calculate() {



		top.y = center.y + radius;
		top.x = center.x;

		right.x = center.x + radius;
		right.y = center.y;

		left.x = center.x - radius;
		left.y = center.y;

		bottom.x = center.x;

		bottom.y = center.y - radius;

	}

};





class VectorOperator {



public:

	VectorOperator() {


	}

	int ScalarProduct(Vector3 v1, Vector3 v2) {

		return v1.position.x*v2.position.x + v1.position.y*v2.position.y + v1.position.z*v2.position.z;


	}

	Vector3 Vector3Cross(Vector3 v1, Vector3 v2) {

		return Vector3(
			v1.position.y * v2.position.z - v1.position.z * v2.position.y,
			v1.position.z * v2.position.x - v1.position.x * v2.position.z,
			v1.position.x * v2.position.y - v1.position.y * v2.position.x);






	}

	Vector3 Vector3Sum(Vector3 v1, Vector3 v2) {


		return Vector3(v1.position.x + v2.position.x, v1.position.y + v2.position.y, v1.position.z + v2.position.z);
	}
	Vector3 Vector3Sub(Vector3 v1, Vector3 v2) {

		return Vector3(v1.position.x - v2.position.x, v1.position.y - v2.position.y, v1.position.z - v2.position.z);
	}
	int Vector3BeforeRoot(Vector3 vector3) {

		return vector3.position.x * vector3.position.x + vector3.position.y * vector3.position.y + vector3.position.z * vector3.position.z;
	}

	float DistanceBetweenZero(Vector3 pos1) {


		return round(fabsf(sqrtf((pos1.position.x)*(pos1.position.x) + (pos1.position.y)*(pos1.position.y) + (pos1.position.z)*(pos1.position.z))));



	}


	float DistanceBetween3DPosition(Vector3 pos1, Vector3 pos2) {


		return round(fabsf(sqrtf((pos1.position.x - pos2.position.x)*(pos1.position.x - pos2.position.x) + (pos1.position.y - pos2.position.y)*(pos1.position.y - pos2.position.y) + (pos1.position.z - pos2.position.z)*(pos1.position.z - pos2.position.z))));



	}

};

class CheckCollision {

public:
	CheckCollision() {


	}



	bool CheckRectRect(Rect rectA, Rect rectB) {


		if (((rectA.LeftTop().x >= rectB.LeftTop().x && rectA.LeftTop().x <= rectB.RightBottom().x) || (rectA.RightBottom().x >= rectB.LeftTop().x && rectA.RightBottom().x <= rectB.RightBottom().x)) || ((rectB.LeftTop().x >= rectA.LeftTop().x && rectB.LeftTop().x <= rectA.RightBottom().x) || (rectB.RightBottom().x >= rectA.LeftTop().x && rectB.RightBottom().x <= rectA.RightBottom().x)))
		{
			if (((rectA.LeftTop().y <= rectB.LeftTop().y && rectA.LeftTop().y >= rectB.RightBottom().y) || (rectA.RightBottom().y >= rectB.RightBottom().y && rectA.RightBottom().y <= rectB.LeftTop().y)) || ((rectB.LeftTop().y <= rectA.LeftTop().y && rectB.LeftTop().y >= rectA.RightBottom().y) || (rectB.RightBottom().y >= rectA.RightBottom().y && rectB.RightBottom().y <= rectA.LeftTop().y)))
			{
				return true;
			}
		}




		return false;
	}


	bool CheckRectCircle(Rect rectA, Circle circle) {

		//printf("%d %d\n", circle.right.x, rectA.leftTop.x);
		if ((
			(circle.Right().x >= rectA.LeftTop().x && circle.Right().x <= rectA.RightBottom().x)
			&& (circle.Right().y >= rectA.RightBottom().y && circle.Right().y <= rectA.LeftTop().y)
			) || (
			(circle.Left().x <= rectA.RightBottom().x && circle.Left().x >= rectA.LeftTop().x)
				&& (circle.Left().y >= rectA.RightBottom().y && circle.Left().y <= rectA.LeftTop().y)
				) || (
				(circle.Top().y >= rectA.RightBottom().y && circle.Top().y <= rectA.LeftTop().y)
					&& (circle.Top().x <= rectA.RightBottom().x && circle.Top().x >= rectA.LeftTop().x)
					) || (
					(circle.Bottom().y <= rectA.LeftTop().y && circle.Bottom().y >= rectA.RightBottom().y)
						&& (circle.Bottom().x <= rectA.RightBottom().x && circle.Bottom().x >= rectA.LeftTop().x))) {



			return true;
		}


		if (((int)DistanceBetween3DPosition(Vector3(circle.center.x, circle.center.y, 0), Vector3(rectA.LeftTop().x, rectA.LeftTop().y, 0)) <= circle.radius) || ((int)DistanceBetween3DPosition(Vector3(circle.center.x, circle.center.y, 0), Vector3(rectA.RightBottom().x, rectA.LeftTop().y, 0)) <= circle.radius) || ((int)DistanceBetween3DPosition(Vector3(circle.center.x, circle.center.y, 0), Vector3(rectA.RightBottom().x, rectA.RightBottom().y, 0)) <= circle.radius) || ((int)DistanceBetween3DPosition(Vector3(circle.center.x, circle.center.y, 0), Vector3(rectA.LeftTop().x, rectA.RightBottom().y, 0)) <= circle.radius)) {

			return true;
		}


		return false;
	}


	bool CheckCircleCircle(Circle circleA, Circle circleB) {


		if (circleA.radius + circleB.radius >= DistanceBetween3DPosition(Vector3(circleA.center.x, circleA.center.y, 0), Vector3(circleB.center.x, circleB.center.y, 0))) {

			return true;
		}




		return false;
	}

	float DistanceBetweenZero(Vector3 pos1) {


		return round(fabsf(sqrtf((pos1.position.x)*(pos1.position.x) + (pos1.position.y)*(pos1.position.y) + (pos1.position.z)*(pos1.position.z))));



	}


	float DistanceBetween3DPosition(Vector3 pos1, Vector3 pos2) {


		return round(fabsf(sqrtf((pos1.position.x - pos2.position.x)*(pos1.position.x - pos2.position.x) + (pos1.position.y - pos2.position.y)*(pos1.position.y - pos2.position.y) + (pos1.position.z - pos2.position.z)*(pos1.position.z - pos2.position.z))));



	}


};

