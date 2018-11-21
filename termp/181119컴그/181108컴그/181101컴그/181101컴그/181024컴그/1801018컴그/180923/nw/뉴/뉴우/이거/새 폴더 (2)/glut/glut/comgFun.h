#define NULL_VALUE -858993460
#define MAX_LIST_SIZE 2000
#define PI 3.141592
#pragma once
#include "stdafx.h"

extern void BeautifulTriangle();


enum PolygonKind {

	PKNone = 0,
	PKCi,
	PKLi,
	PKTr,
	PKRe,
	PKPe,
	PKHe,
	PKTCi,
	PKBRe

};

class Animator {
public:
	Animator() {

	}



};

class GLVectorBasic {

public:

	GLVectorBasic() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	GLVectorBasic(GLdouble x, GLdouble y, GLdouble z) {

		this->x = x;
		this->y = y;
		this->z = z;


	}

	GLdouble x;
	GLdouble y;
	GLdouble z;



};


class GLVector3List
{
public:


	GLVector3List()
	{
		sizeLimit = MAX_LIST_SIZE;
		length = 0;
		//printf("리스트 생성.\n");

		for (int i = 0; i < MAX_LIST_SIZE; ++i) {

			this->vector3[i] = ReturnNullVector3();

		}
	}

	GLVector3List(int size)
	{

		sizeLimit = size;
		length = 0;
		//printf("리스트 생성.\n");

		for (int i = 0; i < MAX_LIST_SIZE; ++i) {

			this->vector3[i] = ReturnNullVector3();

		}

	}



	void Add(GLVectorBasic vector3) {

		if (!OverTheSizeLimit()) {

			for (int i = 0; i < sizeLimit; ++i) {

				if (CheckVector3Equals(this->vector3[i], ReturnNullVector3())) {



					this->vector3[i].x = vector3.x;
					this->vector3[i].y = vector3.y;
					this->vector3[i].z = vector3.z;

					//printf("이 루틴\n");
					//printf("%d\n", i);
					//printf("z%f\n", this->vector3[i].x);
					length++;
					return;
				}
			}
			GLVectorBasic glVector3 = GLVectorBasic(vector3.x, vector3.y, vector3.z);


			this->vector3[length].x = glVector3.x;
			this->vector3[length].y = glVector3.y;
			this->vector3[length].z = glVector3.z;
			length++;
		}




	}

	/*
	void AddBottom(Vector3 vector3) {


	if (!OverTheSizeLimit()) {


	for (int i = 0; i < 2; ++i) {

	if (CheckVector3Equals(this->vector3[i], ReturnNullVector3())) {

	this->vector3[i] = vector3;
	length++;
	return;
	}
	}

	this->vector3[2] = vector3;


	++length;






	}


	}
	*/
	void AddAt(GLVectorBasic vector3, int index) {

		if (!OverTheSizeLimit()) {

			if (IndexAvailabilityCheck(index)) {


				for (int i = 0; i < LastIndex(); ++i) {

					if (CheckVector3Equals(this->vector3[i], ReturnNullVector3())) {


						this->vector3[i] = vector3;


						++length;

						return;
					}

				}



				for (int i = length; i > index; --i) {

					this->vector3[i] = this->vector3[i - 1];

				}

				this->vector3[index] = vector3;


				++length;



			}
		}

	}

	int AddReturnIndexAfter(GLVectorBasic vector3) {


		if (!OverTheSizeLimit()) {

			for (int i = 0; i < sizeLimit; ++i) {

				if (CheckVector3Equals(this->vector3[i], ReturnNullVector3())) {

					this->vector3[i] = vector3;
					length++;
					return length;
				}
			}

			this->vector3[length++] = vector3;
		}

		return length;
	}
	void Remove() {


		if (length > 0) {

			this->vector3[LastIndex()] = ReturnNullVector3();

			length--;
		}


	}
	void RemoveAt(int index) {

		if (IndexAvailabilityCheck(index)) {

			for (int i = index; i < length - 1; ++i) {
				this->vector3[i] = this->vector3[i + 1];
			}

			this->vector3[length] = ReturnNullVector3();

			length--;

		}


	}
	void RemoveAtRange(int index1, int index2) {

		if (IndexAvailabilityCheck(index1) && IndexAvailabilityCheck(index2)) {


			if (index1 <= index2) {

				for (int i = index1; i < index2 + 1; ++i) {

					this->vector3[i] = ReturnNullVector3();
					length--;

				}




				return;
			}

			else if (index1 > index2) {


				for (int i = index2; i < index1 + 1; ++i) {

					this->vector3[i] = ReturnNullVector3();
					length--;
				}

				return;

			}



		}




	}
	void RemoveAndStay(int index) {

		if (IndexAvailabilityCheck(index)) {

			if (!CheckVector3Equals(this->vector3[index], ReturnNullVector3())) {
				this->vector3[index] = ReturnNullVector3();
				--length;
			}


			return;
		}

	}


	void RemoveAll() {

		for (int i = 0; i < sizeLimit; ++i) {

			this->vector3[i] = ReturnNullVector3();


		}

		length = 0;
	}
	int FirstIndex() {

		for (int i = 0; i < sizeLimit; ++i) {

			if (!CheckVector3Equals(this->vector3[i], ReturnNullVector3())) {


				this->firstIndex = i;

				return this->firstIndex;

			}


		}

		return 0;

	}
	int LastIndex() {



		for (int i = sizeLimit - 1; i >= 0; --i) {

			if (!CheckVector3Equals(this->vector3[i], ReturnNullVector3())) {


				this->lastIndex = i;

				return this->lastIndex;

			}


		}

		return 0;
	}

	int Length() {

		return length;
	}

	int SizeLimit() {

		return sizeLimit;
	}

	GLVectorBasic GetDataOfIndex(int index) {



		return this->vector3[index];


		//반환값이 없으면 어떻게돼냐?

	}
	bool OverTheSizeLimit() {

		return length >= sizeLimit;
	}

	bool IndexAvailabilityCheck(int index) {


		return ((index < sizeLimit) && (index >= 0));


	}

	GLVectorBasic ReturnNullVector3() {

		return GLVectorBasic(NULL_VALUE, NULL_VALUE, NULL_VALUE);

	}

	bool CheckVector3Equals(GLVectorBasic v1, GLVectorBasic v2) {

		if (v1.x == v2.x && v1.y == v2.y) {

			return true;
		}
		return false;
	}

	GLVectorBasic* ReturnPointer() {


		static GLVectorBasic* glvector3;

		glvector3 = this->vector3;

		return glvector3;


	}



	GLVectorBasic vector3[MAX_LIST_SIZE];
private:



	int length;
	int sizeLimit;
	int lastIndex;
	int firstIndex;

};

class PolygonObject {

public:

	PolygonObject() {

		activate = false;
		being = false;
		polygonNum = 0;
	}
	PolygonObject(GLVector3List vector3List, bool state, PolygonKind polygonKind) {

		activate = state;
		being = true;


		polygonNum = 0;

		this->polygonNum = (int)polygonKind;


		for (int i = 0; i < vector3List.Length(); ++i) {
			this->glVector3[i].x = vector3List.GetDataOfIndex(i).x;
			this->glVector3[i].y = vector3List.GetDataOfIndex(i).y;
			this->glVector3[i].z = vector3List.GetDataOfIndex(i).z;


			this->original[i].x = vector3List.GetDataOfIndex(i).x;
			this->original[i].y = vector3List.GetDataOfIndex(i).y;
			this->original[i].z = vector3List.GetDataOfIndex(i).z;


		}

		if (this->polygonNum == (int)PKTr) {






		}

		else if (this->polygonNum == (int)PKRe) {


			if (this->glVector3[0].x > this->glVector3[1].x) {

				GLdouble temp = this->glVector3[0].x;

				this->glVector3[0].x = this->glVector3[1].x;

				this->glVector3[1].x = temp;


			}

			if (this->glVector3[0].y < this->glVector3[1].y) {

				GLdouble temp = this->glVector3[0].y;

				this->glVector3[0].y = this->glVector3[1].y;

				this->glVector3[1].y = temp;


			}
			this->glVector3[2].x = this->glVector3[1].x;
			this->glVector3[2].y = this->glVector3[1].y;

			this->glVector3[1].y = this->glVector3[0].y;

			this->glVector3[3].x = this->glVector3[0].x;
			this->glVector3[3].y = this->glVector3[2].y;





			this->width = fabs(this->glVector3[0].x - this->glVector3[1].x);
			this->height = fabs(this->glVector3[0].y - this->glVector3[1].y);



		}
		else if (this->polygonNum == (int)PKBRe) {


			if (this->glVector3[0].x > this->glVector3[1].x) {

				GLdouble temp = this->glVector3[0].x;

				this->glVector3[0].x = this->glVector3[1].x;

				this->glVector3[1].x = temp;


			}

			if (this->glVector3[0].y < this->glVector3[1].y) {

				GLdouble temp = this->glVector3[0].y;

				this->glVector3[0].y = this->glVector3[1].y;

				this->glVector3[1].y = temp;


			}




			this->width = fabs(this->glVector3[0].x - this->glVector3[1].x);
			this->height = fabs(this->glVector3[0].y - this->glVector3[1].y);

			this->rGB[0] = GLVectorBasic(0, 0, 0);
			this->rGBOriginal[0] = this->rGB[0];

		}




		else if (this->polygonNum == PKCi || this->polygonNum == PKTCi) {




			this->radius = fabs(this->glVector3[0].y - this->glVector3[1].y);
			this->originalRadius = this->radius;
			this->tornadoDegreeMax = 360;
		}

		else {

			Destroy();
		}


	}

	bool Available() {


		return being && activate;

	}

	void Destroy() {

		being = false;
		activate = false;
	}

	GLVectorBasic RectMiddlePoint() {


		return GLVectorBasic((this->glVector3[0].x + this->glVector3[1].x) / 2, (this->glVector3[0].y + this->glVector3[1].y) / 2, (this->glVector3[0].z + this->glVector3[1].z) / 2);

	}

	void DrawByGLBegin() {

		if (polygonNum == (int)PKTr) {


			glBegin(GL_POLYGON);
			glVertex3d(this->glVector3[0].x, this->glVector3[0].y, this->glVector3[0].z);
			glVertex3d(this->glVector3[1].x, this->glVector3[1].y, this->glVector3[1].z);
			glVertex3d(this->glVector3[2].x, this->glVector3[2].y, this->glVector3[2].z);
			glEnd();




		}

		else if (polygonNum == (int)PKRe) {

			glBegin(GL_POLYGON);
			glVertex3d(this->glVector3[0].x, this->glVector3[0].y, this->glVector3[0].z);
			glVertex3d(this->glVector3[1].x, this->glVector3[0].y, this->glVector3[0].z);
			glVertex3d(this->glVector3[1].x, this->glVector3[1].y, this->glVector3[0].z);
			glVertex3d(this->glVector3[0].x, this->glVector3[1].y, this->glVector3[0].z);
			glEnd();

		}


		else if (polygonNum == (int)PKCi) {



		}
	}



	static const int size = 100;

	int aniStack = 0;
	GLVectorBasic original[size];
	GLVectorBasic glVector3[size];
	GLVectorBasic rGB[size];
	GLVectorBasic rGBOriginal[size];

	int polygonNum = 0;

	bool activate;

	bool being = false;

	GLdouble linearMoveCoefficient;
	GLdouble xMoveSpeed;
	GLdouble yMoveSpeed;
	GLdouble zMoveSpeed;

	GLdouble xMoveSpeedOriginal;
	GLdouble yMoveSpeedOriginal;
	GLdouble zMoveSpeedOriginal;

	GLdouble radius = 0;
	GLdouble originalRadius = 0;
	GLdouble width = 0;
	GLdouble height = 0;


	int tornadoDegreeMax = 0;
	int tornadoDegree = 0;

	bool specialFlag = false;


	GLVectorBasic tornadoPoints[1080];

	bool processingDirection = false;

	bool selected = false;


	bool clock = false;
	bool counterClock = false;
	bool toLeft = false;
	bool toRight = false;
	bool toUp = false;
	bool toDown = false;
	GLVectorBasic startingPosition;
	bool oneCycled = false;
	bool oneCycle = false;


	bool transformTriangle = false;
	int transformTriangleAniStack = 0;


};




