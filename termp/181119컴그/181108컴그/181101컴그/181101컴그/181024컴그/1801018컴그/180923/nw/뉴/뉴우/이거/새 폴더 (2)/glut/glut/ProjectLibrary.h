#pragma once
#define PI6 3.14159265358979323846264338327950288
#define MAX_LIST_SIZE2 1000;

#include <iostream>
class WorldObejct3D;



using namespace std;

namespace TestNameSpace
{


	class MyAnimatorParameter
	{
	public:
		MyAnimatorParameter()
		{


			//this->asd = new list<TestNameSpace::GLAnimator::AnimatorParameter>;
		}


		struct AnimatorParameter
		{


			int keyFrame;
			int currentFrame;
			bool animationActivate;
			bool loop;


		};


		AnimatorParameter animatorParameter;


		void InitializeAnimatorParameter(int keyFrame, int currentFrame, bool animationActivate, bool loop);








	};




	class GLVector2
	{

	public:

		GLVector2()
		{
			this->x = 0.0f;
			this->y = 0.0f;

		}

		GLVector2(GLdouble x, GLdouble y)
		{

			this->x = x;
			this->y = y;



		}

		GLdouble x;
		GLdouble y;




	};


	class GLVector3
	{

	public:

		GLVector3()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
		}

		GLVector3(GLdouble x, GLdouble y, GLdouble z)
		{

			this->x = x;
			this->y = y;
			this->z = z;


		}

		GLdouble x;
		GLdouble y;
		GLdouble z;



	};
	class GLVector4
	{

	public:

		GLVector4()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			this->w = 0.0f;
		}

		GLVector4(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
		{

			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;

		}

		GLdouble x;
		GLdouble y;
		GLdouble z;
		GLdouble w;


	};


	class GLVector3List
	{
	public:


		GLVector3List()
		{
			sizeLimit = MAX_LIST_SIZE;
			length = 0;
			//printf("리스트 생성.\n");

			for (int i = 0; i < MAX_LIST_SIZE; ++i)
			{

				this->vector3[i] = ReturnNullVector3();

			}
		}

		GLVector3List(int size)
		{

			sizeLimit = size;
			length = 0;
			//printf("리스트 생성.\n");

			for (int i = 0; i < MAX_LIST_SIZE; ++i)
			{

				this->vector3[i] = ReturnNullVector3();

			}

		}



		void Add(GLVector3 vector3)
		{

			if (!OverTheSizeLimit())
			{

				for (int i = 0; i < sizeLimit; ++i)
				{

					if (CheckVector3Equals(this->vector3[i], ReturnNullVector3()))
					{



						this->vector3[i].x = vector3.x;
						this->vector3[i].y = vector3.y;
						this->vector3[i].z = vector3.z;


						length++;
						return;
					}
				}
				GLVector3 glVector3 = GLVector3(vector3.x, vector3.y, vector3.z);


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
		void AddAt(GLVector3 vector3, int index)
		{

			if (!OverTheSizeLimit())
			{

				if (IndexAvailabilityCheck(index))
				{


					for (int i = 0; i < LastIndex(); ++i)
					{

						if (CheckVector3Equals(this->vector3[i], ReturnNullVector3()))
						{


							this->vector3[i] = vector3;


							++length;

							return;
						}

					}



					for (int i = length; i > index; --i)
					{

						this->vector3[i] = this->vector3[i - 1];

					}

					this->vector3[index] = vector3;


					++length;



				}
			}

		}

		int AddReturnIndexAfter(GLVector3 vector3)
		{


			if (!OverTheSizeLimit())
			{

				for (int i = 0; i < sizeLimit; ++i)
				{

					if (CheckVector3Equals(this->vector3[i], ReturnNullVector3()))
					{

						this->vector3[i] = vector3;
						length++;
						return length;
					}
				}

				this->vector3[length++] = vector3;
			}

			return length;
		}
		void Remove()
		{


			if (length > 0)
			{

				this->vector3[LastIndex()] = ReturnNullVector3();

				length--;
			}


		}
		void RemoveAt(int index)
		{

			if (IndexAvailabilityCheck(index))
			{

				for (int i = index; i < length - 1; ++i)
				{
					this->vector3[i] = this->vector3[i + 1];
				}

				this->vector3[length] = ReturnNullVector3();

				length--;

			}


		}
		void RemoveAtRange(int index1, int index2)
		{

			if (IndexAvailabilityCheck(index1) && IndexAvailabilityCheck(index2))
			{


				if (index1 <= index2)
				{

					for (int i = index1; i < index2 + 1; ++i)
					{

						this->vector3[i] = ReturnNullVector3();
						length--;

					}




					return;
				}

				else if (index1 > index2)
				{


					for (int i = index2; i < index1 + 1; ++i)
					{

						this->vector3[i] = ReturnNullVector3();
						length--;
					}

					return;

				}



			}




		}
		void RemoveAndStay(int index)
		{

			if (IndexAvailabilityCheck(index))
			{

				if (!CheckVector3Equals(this->vector3[index], ReturnNullVector3()))
				{
					this->vector3[index] = ReturnNullVector3();
					--length;
				}


				return;
			}

		}


		void RemoveAll()
		{

			for (int i = 0; i < sizeLimit; ++i)
			{

				this->vector3[i] = ReturnNullVector3();


			}

			length = 0;
		}
		int FirstIndex()
		{

			for (int i = 0; i < sizeLimit; ++i)
			{

				if (!CheckVector3Equals(this->vector3[i], ReturnNullVector3()))
				{


					this->firstIndex = i;

					return this->firstIndex;

				}


			}

			return 0;

		}
		int LastIndex()
		{



			for (int i = sizeLimit - 1; i >= 0; --i)
			{

				if (!CheckVector3Equals(this->vector3[i], ReturnNullVector3()))
				{


					this->lastIndex = i;

					return this->lastIndex;

				}


			}

			return 0;
		}

		int Length()
		{

			return length;
		}

		int SizeLimit()
		{

			return sizeLimit;
		}

		GLVector3 GetDataOfIndex(int index)
		{



			return this->vector3[index];


			//반환값이 없으면 어떻게돼냐?

		}
		bool OverTheSizeLimit()
		{

			return length >= sizeLimit;
		}

		bool IndexAvailabilityCheck(int index)
		{


			return ((index < sizeLimit) && (index >= 0));


		}

		GLVector3 ReturnNullVector3()
		{

			return GLVector3(NULL_VALUE, NULL_VALUE, NULL_VALUE);

		}

		bool CheckVector3Equals(GLVector3 v1, GLVector3 v2)
		{

			if (v1.x == v2.x && v1.y == v2.y)
			{

				return true;
			}
			return false;
		}

		GLVector3* ReturnPointer()
		{


			static GLVector3* glvector3;

			glvector3 = this->vector3;

			return glvector3;


		}



		GLVector3 vector3[MAX_LIST_SIZE];
	private:



		int length;
		int sizeLimit;
		int lastIndex;
		int firstIndex;

	};












	class Position
	{
	public:

		GLVector3 vector3;

	};
	struct OrthoData
	{

		double screenLTX;
		double screenLTY;
		double screenRBX;
		double screenRBY;
		double zNear;
		double zFar;
		double width;
		double height;
		double zSize;

	};

	struct Camera
	{
		GLdouble eyeX, /* gluLookAt */

			eyeY,

			eyeZ,

			centerX,

			centerY,

			centerZ,

			upX,

			upY,

			upZ,
			/* gluPerspective  */

			fovy,

			aspect,

			zNear,

			zFar;

	};

	class MasterMatrix
	{
	public:


		MasterMatrix();

		MasterMatrix(bool);




		MasterMatrix(OrthoData viewportData);
		MasterMatrix(Camera);
		MasterMatrix(Camera, OrthoData);

		void glMultMasterMatrix(GLdouble* pMatrix);
		void glLoadMasterMatrix();

		void glSetMasterMatrix(GLdouble* translateMatrix, GLdouble* rotateMatrix, GLdouble* scaleMatrix);

		GLdouble* MuliplyMatrix44(GLdouble* pMatrix1, GLdouble* pMatrix2);
		GLdouble* MuliplyMatrix441(GLdouble* pMatrix1, GLdouble* pMatrix2);
		void PrintMatrix44(GLdouble* pMatrix);
		void InitializeCamera();
		void InitializeCamera(Camera camera);
		void InitializeOrthoData();
		void InitializeOrthoData(OrthoData orthoData);

		void PerspectiveSetting();
		void OrthoSetting();

		void OrthoOrPerspective();


		bool ortho = false;
		bool perspective = false;

		bool orthoOrPerspective = false;

		int a;

		GLdouble identityMatrix[16]
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
		GLdouble currentTranslateMatrix[16]
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1


		};
		GLdouble currentXRotateMatrix[4]
		{
			0,0,0,0

		};
		GLdouble currentYRotateMatrix[4]
		{
			0,0,0,0

		};
		GLdouble currentZRotateMatrix[4]
		{
			0,0,0,0

		};
		GLdouble currentScaleMatrix[3]
		{
			1,1,1

		};



		bool created = false;
		OrthoData orthoData;
		Camera thisCamera;

		GLVector3 GiveMeRotatedCoordinate(int axisKind, double theta, GLVector3 what)
		{
			static double pi = 3.1415926535;



			if (axisKind == 1)
			{
				return GLVector3(
					what.x,
					cos((pi * theta) / 180.0) * what.y - sin((pi * theta) / 180.0) * what.z,
					sin((pi * theta) / 180.0)* what.y + cos((pi * theta) / 180.0) * what.z
				);


			}
			else if (axisKind == 2)
			{
				return GLVector3(
					cos((pi * theta) / 180.0) * what.x + sin((pi * theta) / 180.0) * what.z,
					what.y,
					-sin((pi * theta) / 180.0) * what.x + cos((pi * theta) / 180.0) * what.z
				);
			}

			else if (axisKind == 3)
			{
				return GLVector3(
					cos((pi * theta) / 180.0) * what.x - sin((pi * theta) / 180.0) * what.y,
					sin((pi * theta) / 180.0) * what.x + cos((pi * theta) / 180.0) * what.y,
					what.z
				);

			}
			return what;
		}


		int ScalarProduct(GLVector3 v1, GLVector3 v2)
		{

			return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;


		}

		GLVector3 Vector3Cross(GLVector3 v1, GLVector3 v2)
		{

			return GLVector3(
				v1.y * v2.z - v1.z * v2.y,
				v1.z * v2.x - v1.x * v2.z,
				v1.x * v2.y - v1.y * v2.x);






		}

		GLVector3 Vector3Sum(GLVector3 v1, GLVector3 v2)
		{


			return GLVector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
		}
		GLVector3 Vector3Sub(GLVector3 v1, GLVector3 v2)
		{

			return GLVector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
		}
		int Vector3BeforeRoot(GLVector3 vector3)
		{

			return vector3.x * vector3.x + vector3.y * vector3.y + vector3.z * vector3.z;
		}

		float DistanceBetweenZero(GLVector3 pos1)
		{


			return round(fabsf(sqrtf((pos1.x)*(pos1.x) + (pos1.y)*(pos1.y) + (pos1.z)*(pos1.z))));



		}


		float DistanceBetween3DPosition(GLVector3 pos1, GLVector3 pos2)
		{


			return round(fabsf(sqrtf((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y) + (pos1.z - pos2.z)*(pos1.z - pos2.z))));



		}


	};






	class Collider3D
	{


	};




	class WorldObject3D
	{
	public:




		WorldObject3D()
		{

		}

		void ClearCurrentTranslate()
		{
			this->currentTranslateMatrix[12] = 0;
			this->currentTranslateMatrix[13] = 0;
			this->currentTranslateMatrix[14] = 0;
		}
		void ClearCurrentRotate()
		{
			for (int i = 0; i < 4; ++i)
			{
				this->currentXRotateMatrix[i] = 0;
				this->currentYRotateMatrix[i] = 0;
				this->currentZRotateMatrix[i] = 0;

			}
		}
		void ClearCurrentScale()
		{

			this->currentScaleMatrix[0] = 1;
			this->currentScaleMatrix[1] = 1;
			this->currentScaleMatrix[2] = 1;

		}

		void RotateNoGimbalLock(double x, double y, double z)
		{

			if (x != 0)
			{
				this->xyzDegree[0] = x;
				this->xyzDegreeRecord[0] += x;
				return;
			}

			if (y != 0)
			{
				this->xyzDegree[1] = y;
				this->xyzDegreeRecord[1] += y;
				return;
			}

			if (z != 0)
			{
				this->xyzDegree[2] = z;
				this->xyzDegreeRecord[2] += z;
				return;
			}

		}


		//쿼터니온으로 짐벌락을 해결해볼까
		void RotationPriorityOrder()
		{








		}


		void TranslateFreeXAxis(GLdouble x, GLdouble y, GLdouble z)
		{
			for (int i = 0; i < 2; ++i)
			{
				freeXAxisPoints[i].x += x;
				freeXAxisPoints[i].y += y;
				freeXAxisPoints[i].z += z;

			}


		}
		void TranslateFreeYAxis(GLdouble x, GLdouble y, GLdouble z)
		{
			for (int i = 0; i < 2; ++i)
			{
				freeYAxisPoints[i].x += x;
				freeYAxisPoints[i].y += y;
				freeYAxisPoints[i].z += z;

			}

		}
		void TranslateFreeZAxis(GLdouble x, GLdouble y, GLdouble z)
		{
			for (int i = 0; i < 2; ++i)
			{
				freeZAxisPoints[i].x += x;
				freeZAxisPoints[i].y += y;
				freeZAxisPoints[i].z += z;

			}

		}

		void FreeAxisRotate2(GLdouble xDegree, GLdouble yDegree, GLdouble zDegree)
		{
			if ((int)xDegree != 0)
			{

				FreeXAxisRotate2(xDegree);
			}
			else if ((int)yDegree != 0)
			{
				FreeYAxisRotate2(yDegree);
			}

			else if ((int)zDegree != 0)
			{
				FreeZAxisRotate2(zDegree);

			}


		}


		void FreeXAxisRotate(GLdouble degree)
		{


			this->xFree = true;
			this->yFree = false;
			this->zFree = false;

			this->freeXAxisRotateDegree = degree;

			if (this->freeXAxisRotateDegree > 360.0)
			{
				this->freeXAxisRotateDegree -= 360.0*floor(this->freeXAxisRotateDegree / 360.0);   // Don't allow overflow
			}
			else if (this->freeXAxisRotateDegree < -360.0)
			{
				this->freeXAxisRotateDegree += 360.0*floor(-this->freeXAxisRotateDegree / 360.0);   // Don't allow overflow
			}

		}
		void FreeXAxisRotate2(GLdouble degree)
		{
			this->xFree = true;
			this->yFree = false;
			this->zFree = false;


			this->freeXAxisRotateDegree += degree;


			if (this->freeXAxisRotateDegree > 360.0)
			{
				this->freeXAxisRotateDegree -= 360.0*floor(this->freeXAxisRotateDegree / 360.0);   // Don't allow overflow
			}
			else if (this->freeXAxisRotateDegree < -360.0)
			{
				this->freeXAxisRotateDegree += 360.0*floor(-this->freeXAxisRotateDegree / 360.0);   // Don't allow overflow
			}
		}

		void FreeYAxisRotate(GLdouble degree)
		{
			this->xFree = false;
			this->yFree = true;
			this->zFree = false;

			this->freeYAxisRotateDegree = degree;


			if (this->freeYAxisRotateDegree > 360.0)
			{
				this->freeYAxisRotateDegree -= 360.0*floor(this->freeYAxisRotateDegree / 360.0);   // Don't allow overflow
			}
			else if (this->freeYAxisRotateDegree < -360.0)
			{
				this->freeYAxisRotateDegree += 360.0*floor(-this->freeYAxisRotateDegree / 360.0);   // Don't allow overflow
			}
		}
		void FreeYAxisRotate2(GLdouble degree)
		{

			this->xFree = false;
			this->yFree = true;
			this->zFree = false;

			this->freeYAxisRotateDegree += degree;


			if (this->freeYAxisRotateDegree > 360.0)
			{
				this->freeYAxisRotateDegree -= 360.0*floor(this->freeYAxisRotateDegree / 360.0);   // Don't allow overflow
			}
			else if (this->freeYAxisRotateDegree < -360.0)
			{
				this->freeYAxisRotateDegree += 360.0*floor(-this->freeYAxisRotateDegree / 360.0);   // Don't allow overflow
			}
		}

		void FreeZAxisRotate(GLdouble degree)
		{

			this->xFree = false;
			this->yFree = false;
			this->zFree = true;

			this->freeZAxisRotateDegree = degree;


			if (this->freeZAxisRotateDegree > 360.0)
			{
				this->freeZAxisRotateDegree -= 360.0*floor(this->freeZAxisRotateDegree / 360.0);   // Don't allow overflow
			}
			else if (this->freeZAxisRotateDegree < -360.0)
			{
				this->freeZAxisRotateDegree += 360.0*floor(-this->freeZAxisRotateDegree / 360.0);   // Don't allow overflow
			}

		}
		void FreeZAxisRotate2(GLdouble degree)
		{


			this->xFree = false;
			this->yFree = false;
			this->zFree = true;


			this->freeZAxisRotateDegree += degree;


			if (this->freeZAxisRotateDegree > 360.0)
			{
				this->freeZAxisRotateDegree -= 360.0*floor(this->freeZAxisRotateDegree / 360.0);   // Don't allow overflow
			}
			else if (this->freeZAxisRotateDegree < -360.0)
			{
				this->freeZAxisRotateDegree += 360.0*floor(-this->freeZAxisRotateDegree / 360.0);   // Don't allow overflow
			}

		}



		//개선된 축 정하기
		void SetFreeRotateXAxis(GLVector3 point1, GLVector3 point2)
		{
			this->freeXAxisPoints[0] = point1;
			this->freeXAxisPoints[1] = point2;


			this->freeXAxisPointsOriginal[0] = GLVector3(point1.x, point1.y, point1.z);
			this->freeXAxisPointsOriginal[1] = GLVector3(point2.x, point2.y, point2.z);


		}
		void SetFreeRotateYAxis(GLVector3 point1, GLVector3 point2)
		{
			this->freeYAxisPoints[0] = point1;
			this->freeYAxisPoints[1] = point2;

			this->freeYAxisPointsOriginal[0] = GLVector3(point1.x, point1.y, point1.z);
			this->freeYAxisPointsOriginal[1] = GLVector3(point2.x, point2.y, point2.z);

		}
		void SetFreeRotateZAxis(GLVector3 point1, GLVector3 point2)
		{
			this->freeZAxisPoints[0] = point1;
			this->freeZAxisPoints[1] = point2;

			this->freeZAxisPointsOriginal[0] = GLVector3(point1.x, point1.y, point1.z);
			this->freeZAxisPointsOriginal[1] = GLVector3(point2.x, point2.y, point2.z);

		}



		void SetXYZDistance(GLdouble x, GLdouble y, GLdouble z)
		{
			this->xYZDistanceFromAxis[0] = x;
			this->xYZDistanceFromAxis[1] = y;
			this->xYZDistanceFromAxis[2] = z;
		}
		void SetXYZDistance(GLVector3 vector3)
		{
			this->xYZDistanceFromAxis[0] = vector3.x;
			this->xYZDistanceFromAxis[1] = vector3.y;
			this->xYZDistanceFromAxis[2] = vector3.z;

		}
		void AxisTranslate(GLVector3 vector3)
		{
			this->axisTranslateMatrix[12] += vector3.x;
			this->axisTranslateMatrix[13] += vector3.y;
			this->axisTranslateMatrix[14] += vector3.z;
		}
		void AxisTranslate(GLdouble x, GLdouble y, GLdouble z)
		{
			this->axisTranslateMatrix[12] += x;
			this->axisTranslateMatrix[13] += y;
			this->axisTranslateMatrix[14] += z;

		}
		void SetAxisTranslate(GLdouble x, GLdouble y, GLdouble z)
		{
			this->axisTranslateMatrix[12] = x;
			this->axisTranslateMatrix[13] = y;
			this->axisTranslateMatrix[14] = z;

		}

		void SetAxisTranslate(GLVector3 vector3)
		{
			this->axisTranslateMatrix[12] = vector3.x;
			this->axisTranslateMatrix[13] = vector3.y;
			this->axisTranslateMatrix[14] = vector3.z;
		}
		void Translate(GLdouble x, GLdouble y, GLdouble z)
		{


			this->currentTranslateMatrix[12] += x;
			this->currentTranslateMatrix[13] += y;
			this->currentTranslateMatrix[14] += z;
		}

		void Translate(GLVector3 vector3)
		{


			this->currentTranslateMatrix[12] += vector3.x;
			this->currentTranslateMatrix[13] += vector3.y;
			this->currentTranslateMatrix[14] += vector3.z;
		}
		void AxisRotate(GLdouble x, GLdouble y, GLdouble z, GLdouble w, int flag)
		{


			if (flag == 0)
			{

				this->axisXRotateMatrix[0] = x;
				this->axisXRotateMatrix[1] = y;
				this->axisXRotateMatrix[2] = z;
				this->axisXRotateMatrix[3] = w;
			}
			else if (flag == 1)
			{
				this->axisYRotateMatrix[0] = x;
				this->axisYRotateMatrix[1] = y;
				this->axisYRotateMatrix[2] = z;
				this->axisYRotateMatrix[3] = w;

			}
			else if (flag == 2)
			{
				this->axisZRotateMatrix[0] = x;
				this->axisZRotateMatrix[1] = y;
				this->axisZRotateMatrix[2] = z;
				this->axisZRotateMatrix[3] = w;

			}


			if (this->axisXRotateMatrix[0] > 360.0)
			{
				this->axisXRotateMatrix[0] -= 360.0*floor(this->axisXRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

			if (this->axisYRotateMatrix[0] > 360.0)
			{
				this->axisYRotateMatrix[0] -= 360.0*floor(this->axisYRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

			if (this->axisZRotateMatrix[0] > 360.0)
			{
				this->axisZRotateMatrix[0] -= 360.0*floor(this->axisZRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

		}
		void AxisRotate(GLVector4 vector4, int flag)
		{


			if (flag == 0)
			{

				this->axisXRotateMatrix[0] = vector4.x;
				this->axisXRotateMatrix[1] = vector4.y;
				this->axisXRotateMatrix[2] = vector4.z;
				this->axisXRotateMatrix[3] = vector4.w;
			}
			else if (flag == 1)
			{
				this->axisYRotateMatrix[0] = vector4.x;
				this->axisYRotateMatrix[1] = vector4.y;
				this->axisYRotateMatrix[2] = vector4.z;
				this->axisYRotateMatrix[3] = vector4.w;

			}
			else if (flag == 2)
			{
				this->axisZRotateMatrix[0] = vector4.x;
				this->axisZRotateMatrix[1] = vector4.y;
				this->axisZRotateMatrix[2] = vector4.z;
				this->axisZRotateMatrix[3] = vector4.w;

			}


			if (this->axisXRotateMatrix[0] > 360.0)
			{
				this->axisXRotateMatrix[0] -= 360.0*floor(this->axisXRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

			if (this->axisYRotateMatrix[0] > 360.0)
			{
				this->axisYRotateMatrix[0] -= 360.0*floor(this->axisYRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

			if (this->axisZRotateMatrix[0] > 360.0)
			{
				this->axisZRotateMatrix[0] -= 360.0*floor(this->axisZRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

		}


		void AxisRotate2(GLdouble x, GLdouble y, GLdouble z, GLdouble w, int flag)
		{


			if (flag == 0)
			{

				this->axisXRotateMatrix[0] += x;
				this->axisXRotateMatrix[1] = y;
				this->axisXRotateMatrix[2] = z;
				this->axisXRotateMatrix[3] = w;
			}
			else if (flag == 1)
			{
				this->axisYRotateMatrix[0] += x;
				this->axisYRotateMatrix[1] = y;
				this->axisYRotateMatrix[2] = z;
				this->axisYRotateMatrix[3] = w;

			}
			else if (flag == 2)
			{
				this->axisZRotateMatrix[0] += x;
				this->axisZRotateMatrix[1] = y;
				this->axisZRotateMatrix[2] = z;
				this->axisZRotateMatrix[3] = w;

			}


			if (this->axisXRotateMatrix[0] > 360.0)
			{
				this->axisXRotateMatrix[0] -= 360.0*floor(this->axisXRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

			if (this->axisYRotateMatrix[0] > 360.0)
			{
				this->axisYRotateMatrix[0] -= 360.0*floor(this->axisYRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

			if (this->axisZRotateMatrix[0] > 360.0)
			{
				this->axisZRotateMatrix[0] -= 360.0*floor(this->axisZRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

		}


		void AxisRotate2(GLVector4 vector4, int flag)
		{


			if (flag == 0)
			{

				this->axisXRotateMatrix[0] += vector4.x;
				this->axisXRotateMatrix[1] = vector4.y;
				this->axisXRotateMatrix[2] = vector4.z;
				this->axisXRotateMatrix[3] = vector4.w;
			}
			else if (flag == 1)
			{
				this->axisYRotateMatrix[0] += vector4.x;
				this->axisYRotateMatrix[1] = vector4.y;
				this->axisYRotateMatrix[2] = vector4.z;
				this->axisYRotateMatrix[3] = vector4.w;

			}
			else if (flag == 2)
			{
				this->axisZRotateMatrix[0] += vector4.x;
				this->axisZRotateMatrix[1] = vector4.y;
				this->axisZRotateMatrix[2] = vector4.z;
				this->axisZRotateMatrix[3] = vector4.w;

			}


			if (this->axisXRotateMatrix[0] > 360.0)
			{
				this->axisXRotateMatrix[0] -= 360.0*floor(this->axisXRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

			if (this->axisYRotateMatrix[0] > 360.0)
			{
				this->axisYRotateMatrix[0] -= 360.0*floor(this->axisYRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

			if (this->axisZRotateMatrix[0] > 360.0)
			{
				this->axisZRotateMatrix[0] -= 360.0*floor(this->axisZRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

		}
		void Rotate2(GLVector4 vector4, int flag)
		{
			if (flag == 0)
			{

				this->currentXRotateMatrix[0] += vector4.x;
				this->currentXRotateMatrix[1] = vector4.y;
				this->currentXRotateMatrix[2] = vector4.z;
				this->currentXRotateMatrix[3] = vector4.w;


			}
			else if (flag == 1)
			{

				this->currentYRotateMatrix[0] += vector4.x;
				this->currentYRotateMatrix[1] = vector4.y;
				this->currentYRotateMatrix[2] = vector4.z;
				this->currentYRotateMatrix[3] = vector4.w;


			}
			else if (flag == 2)
			{

				this->currentZRotateMatrix[0] += vector4.x;
				this->currentZRotateMatrix[1] = vector4.y;
				this->currentZRotateMatrix[2] = vector4.z;
				this->currentZRotateMatrix[3] = vector4.w;


			}


			if (this->currentXRotateMatrix[0] > 360.0)
			{
				this->currentXRotateMatrix[0] -= 360.0*floor(this->currentXRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

			if (this->currentYRotateMatrix[0] > 360.0)
			{
				this->currentYRotateMatrix[0] -= 360.0*floor(this->currentYRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

			if (this->currentZRotateMatrix[0] > 360.0)
			{
				this->currentZRotateMatrix[0] -= 360.0*floor(this->currentZRotateMatrix[0] / 360.0);   // Don't allow overflow
			}


		}

		void Rotate2(GLdouble x, GLdouble y, GLdouble z, GLdouble w, int flag)
		{
			if (flag == 0)
			{

				this->currentXRotateMatrix[0] += x;
				this->currentXRotateMatrix[1] = y;
				this->currentXRotateMatrix[2] = z;
				this->currentXRotateMatrix[3] = w;


			}
			else if (flag == 1)
			{

				this->currentYRotateMatrix[0] += x;
				this->currentYRotateMatrix[1] = y;
				this->currentYRotateMatrix[2] = z;
				this->currentYRotateMatrix[3] = w;


			}
			else if (flag == 2)
			{

				this->currentZRotateMatrix[0] += x;
				this->currentZRotateMatrix[1] = y;
				this->currentZRotateMatrix[2] = z;
				this->currentZRotateMatrix[3] = w;


			}


			if (this->currentXRotateMatrix[0] > 360.0)
			{
				this->currentXRotateMatrix[0] -= 360.0*floor(this->currentXRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

			if (this->currentYRotateMatrix[0] > 360.0)
			{
				this->currentYRotateMatrix[0] -= 360.0*floor(this->currentYRotateMatrix[0] / 360.0);   // Don't allow overflow
			}

			if (this->currentZRotateMatrix[0] > 360.0)
			{
				this->currentZRotateMatrix[0] -= 360.0*floor(this->currentZRotateMatrix[0] / 360.0);   // Don't allow overflow
			}


		}

		void Rotate(GLVector4 vector4, int flag)
		{
			if (flag == 0)
			{

				this->currentXRotateMatrix[0] = vector4.x;
				this->currentXRotateMatrix[1] = vector4.y;
				this->currentXRotateMatrix[2] = vector4.z;
				this->currentXRotateMatrix[3] = vector4.w;


			}
			else if (flag == 1)
			{

				this->currentYRotateMatrix[0] = vector4.x;
				this->currentYRotateMatrix[1] = vector4.y;
				this->currentYRotateMatrix[2] = vector4.z;
				this->currentYRotateMatrix[3] = vector4.w;


			}
			else if (flag == 2)
			{

				this->currentZRotateMatrix[0] = vector4.x;
				this->currentZRotateMatrix[1] = vector4.y;
				this->currentZRotateMatrix[2] = vector4.z;
				this->currentZRotateMatrix[3] = vector4.w;


			}

		}


		void Rotate(GLdouble x, GLdouble y, GLdouble z, GLdouble w, int flag)
		{
			if (flag == 0)
			{

				this->currentXRotateMatrix[0] = x;
				this->currentXRotateMatrix[1] = y;
				this->currentXRotateMatrix[2] = z;
				this->currentXRotateMatrix[3] = w;


			}
			else if (flag == 1)
			{

				this->currentYRotateMatrix[0] = x;
				this->currentYRotateMatrix[1] = y;
				this->currentYRotateMatrix[2] = z;
				this->currentYRotateMatrix[3] = w;


			}
			else if (flag == 2)
			{

				this->currentZRotateMatrix[0] = x;
				this->currentZRotateMatrix[1] = y;
				this->currentZRotateMatrix[2] = z;
				this->currentZRotateMatrix[3] = w;


			}

		}



		void Scale(GLdouble x, GLdouble y, GLdouble z)
		{

			this->currentScaleMatrix[0] = x;
			this->currentScaleMatrix[1] = y;
			this->currentScaleMatrix[2] = z;
		}



		void Scale(GLVector3 vector3)
		{

			this->currentScaleMatrix[0] = vector3.x;
			this->currentScaleMatrix[1] = vector3.y;
			this->currentScaleMatrix[2] = vector3.z;
		}

		void SetScaleOriginally()
		{

			for (int i = 0; i < 3; ++i)
			{
				this->currentScaleMatrix[i] = 1.0;

			}

		}

		void SetRotateOriginally()
		{

			for (int i = 0; i < 4; ++i)
			{
				this->currentXRotateMatrix[i] = 0;
				this->currentYRotateMatrix[i] = 0;
				this->currentZRotateMatrix[i] = 0;
			}

		}

		void SetTranslateOriginally()
		{

			for (int i = 0; i < 16; ++i)
			{

				this->currentTranslateMatrix[i] = this->identityMatrix[i];

			}
		}

		void SetPosition(GLVector3 vector3)
		{

			this->currentTranslateMatrix[12] = vector3.x;
			this->currentTranslateMatrix[13] = vector3.y;
			this->currentTranslateMatrix[14] = vector3.z;
		}

		void SetPosition(GLdouble x, GLdouble y, GLdouble z)
		{

			this->currentTranslateMatrix[12] = x;
			this->currentTranslateMatrix[13] = y;
			this->currentTranslateMatrix[14] = z;
		}

		GLVector3 Position()
		{

			return GLVector3(
				this->masterMatrixs->currentTranslateMatrix[12] + this->currentTranslateMatrix[12],
				this->masterMatrixs->currentTranslateMatrix[13] + this->currentTranslateMatrix[13],
				this->masterMatrixs->currentTranslateMatrix[14] + this->currentTranslateMatrix[14]
			);


		}





		bool Availability()
		{




			return false;
		}
		enum XYZ
		{
			NoneXYZ = 0,
			X = 1,
			Y,
			Z

		};
		//field

		struct PhysicsData
		{
			//GLVector2 force2D;
			//GLVector2 acceleration2D;

			GLVector3 force3D;
			GLVector3 acceleration3D;
			GLVector3 velocity;


			double mass = 1;

			int xDir = 0;
			int yDir = 0;
			int zDir = 0;

			bool _2DOr3D = true;
			bool apply = true;



		};
		struct Rect3D
		{

			double minX;
			double maxX;

			double minZ;
			double maxZ;

			double minY;
			double maxY;



		};


		PhysicsData physicsData;

		MasterMatrix* masterMatrixs;


		bool rotatePriorityOrder = false;
		bool objectActivate = false;
		bool axisRotate = false;
		bool freeAxisRotate = false;
		bool xFree = false;
		bool yFree = false;
		bool zFree = false;
		bool rotationAccumulate = false;


		double xyzDegree[3] = { 0,0,0 };
		double xyzDegreeRecord[3] = { 0,0,0 };




		list<int>* freeAxisOrder = new list<int>;

		XYZ xyzKind = NoneXYZ;
		double rotationMatrix[16]
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1




		};

		double translationMatrix[16]
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1



		};

		double scaleMatrinx[16]
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1



		};



		int currentAxis = 0;
		int beforeAxis = 0;






		GLdouble freeXAxisRotateDegree = 0;
		GLdouble freeYAxisRotateDegree = 0;
		GLdouble freeZAxisRotateDegree = 0;

		GLVector3 freeXAxisPoints[2];
		GLVector3 freeYAxisPoints[2];
		GLVector3 freeZAxisPoints[2];

		GLVector3 freeXAxisPointsOriginal[2];
		GLVector3 freeYAxisPointsOriginal[2];
		GLVector3 freeZAxisPointsOriginal[2];


		GLdouble identityMatrix[16]
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
		GLdouble currentTranslateMatrix[16]
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1


		};
		GLdouble currentXRotateMatrix[4]
		{
			0,0,0,0

		};
		GLdouble currentYRotateMatrix[4]
		{
			0,0,0,0

		};
		GLdouble currentZRotateMatrix[4]
		{
			0,0,0,0

		};
		GLdouble currentScaleMatrix[3]
		{
			1,1,1

		};

		GLdouble axisXRotateMatrix[4]
		{

			0,0,0,0

		};
		GLdouble axisYRotateMatrix[4]
		{

			0,0,0,0

		};
		GLdouble axisZRotateMatrix[4]
		{

			0,0,0,0

		};

		GLdouble axisTranslateMatrix[16]
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1


		};

		GLdouble xYZDistanceFromAxis[3]
		{
			0,0,0

		};



		Rect3D GetCollisionBox3D()
		{

		};

		void ApplyPhysics()
		{

		}


	private:

	};


	class InitializeData
	{
	public:
		float size;
		bool rainbowColorOption;
		bool randomColorOption;
		bool wireOption;
		bool animationOption;

		double etc[100];

	};


	class Polygon0 : public WorldObject3D
	{

	public:


		enum PolygonKind
		{


		};
		PolygonKind objectKind;

		Polygon0()
		{

			this->masterMatrixs = new MasterMatrix();

		}

		Polygon0(MasterMatrix* masterMatrixs)
		{

			this->masterMatrixs = masterMatrixs;
			this->objectActivate = true;

		}
		/*
		Polygon0(MasterMatrix* masterMatrixs, GLVector3List vector3List, PolygonKind objectKind)
		{

			this->masterMatrixs = masterMatrixs;
			this->objectActivate = true;

			this->objectKind = objectKind;




		}
		*/
		GLVector3 color3D = GLVector3(0, 0, 1);
		GLVector4 color4D = GLVector4(0, 0, 1, 1);
		double red = 1.0;
		double greed = 0;
		double blue = 0;
		double alpha = 1;




		virtual void AddPoints(GLVector3 point);
		virtual void ObjectiveRendering();
		virtual void Initialize();

		void Confirm();
		void Undo();

		void Disable();
		int NumberOfPoint();

		void ApplyMatrix();


		void DrawWireRectangle(float size, bool colorRandomOption, bool rainbowColorOption);
		void DrawRectangle(float size, bool colorRandomOption, bool rainbowColorOption);

		void DrawTriangle(float size, bool colorRandomOption, bool rainbowColorOption);

		void DrawCube(float size, bool colorRandomOption, bool rainbowColorOption);
		void DrawCube(MasterMatrix* masterMatrixs, float);
		void DrawCube(MasterMatrix* masterMatrixs, float, int*, GLdouble* pMatrix);
		void DrawSphere(float size, bool colorRandomOption, bool rainbowColorOption);
		void DrawSphere(float size, bool colorRandomOption, bool rainbowColorOption, bool wireOption);

		void DrawWireSphere(float size, bool colorRandomOption, bool rainbowColorOption);
		void DrawWireTorus(float size, bool colorRandomOption, bool rainbowColorOption);
		void DrawWireCone(float size, bool colorRandomOption, bool rainbowColorOption);
		void DrawWireCube(float size, bool colorRandomOption, bool rainbowColorOption);
		void DrawWireTriangle(float size, bool colorRandomOption, bool rainbowColorOption);

		void DrawSpring(float size, bool colorRandomOption, bool rainbowColorOption, bool animationFlag);
		void DrawSineGraph(float size, bool colorRandomOption, bool rainbowColorOption, bool animationFlag);

		void DrawRibbon(float size, bool colorRandomOption, bool rainbowColorOption, bool animationFlag);

		void DrawRectEscalator(float size, bool colorRandomOption, bool rainbowColorOption, bool animationFlag);
		void DrawXYLine(float size, bool colorRandomOption, bool rainbowColorOption);
		void Create3DObject(int num, float size, bool colorRandomOption, bool rainbowColorOption);
		void DrawCircle(float radius, bool colorRandomOption, bool rainbowColorOption);
		void DrawZigzag(float size, bool colorRandomOption, bool rainbowColorOption);

		void DrawLine(float size, bool colorRandomOption, bool rainbowColorOption);
		void DrawBoard(float size, bool colorRandomOption, bool rainbowColorOption);
		void DrawBoard(InitializeData initializeData);

		void DrawHexahedron(float size, bool colorRandomOption, bool rainbowColorOption, bool wireOption);
		void DrawHexahedron(InitializeData initializeData);


		void DrawTeapot(float size, bool colorRandomOption, bool rainbowColorOption, bool wireOption);
		void DrawTeapot(InitializeData initializeData);


		void DrawCone(float size, bool colorRandomOption, bool rainbowColorOption, bool wireOption);
		void DrawCone(InitializeData initializeData);

		void ColorSetting(bool colorRandomOption, bool rainbowColorOption);

		void DrawXYZLine(float size, bool colorRandomOption, bool rainbowColorOption);
		void DrawXYZLine(InitializeData initializeData);

		void SetBasicParameter(float size, bool colorRandomOption, bool rainbowColorOption);

		bool rendering = false;
		GLVector3List vector3List;
		InitializeData initializeData;
		float size = 1;

		bool colorRandomOption = false;
		bool rainbowColorOption = false;



	};
	//2D
	class DraggingLine : Polygon0
	{
	public:
		DraggingLine() : Polygon0()
		{
			//this->color4D = new GLVector4()

		}


		DraggingLine(MasterMatrix* masterMatrix) : Polygon0(masterMatrix)
		{


		}


		void SetPosition(GLVector3 endPoint);
		void SetPosition(GLVector3 startPoint, GLVector3 endPoint);
		void DrawDraggingLine(InitializeData initializedata);
		void DrawDraggingLine(bool colorRandomOption, bool rainbowColorOption);
		void Disable();
		void Enable();
		bool onMyMouse = false;

		GLVector3 startPoint;
		GLVector3 endPoint;


	};

	class TwinCube : Polygon0
	{
	public:
		TwinCube()
		{

		}

		void DrawTwinCube(MasterMatrix* masterMatrixs, float size, GLdouble space, bool horVerFlag, GLdouble* pMatrix);




	};

	class RectangularClock
	{


	public:
		RectangularClock()
		{

		}


		//void RectangularClockNum(int n, GLdouble size);
		void RectangularClockNum(MasterMatrix* masterMatrixs, int n, GLdouble size, GLdouble* pMatrix, bool wireOption, GLdouble* color4D);
		void DrawBlock(MasterMatrix* masterMatrixs, int n, GLdouble size, GLdouble* pMatrix);

		bool wireOption = false;
		GLdouble* color4D;

	};

	class SpringLine : public Polygon0
	{
	public:
		SpringLine()
		{

			this->masterMatrixs = new MasterMatrix();
			this->Initialize(50, 6, false, true);

		}
		SpringLine(MasterMatrix* mastermatrix)
		{
			this->masterMatrixs = mastermatrix;
			this->Initialize(50, 6, false, true);
			this->Confirm();

		}
		void ObjectiveRendering();
		void AddPoints(GLVector3);
		void Initialize(double size, int cycle, bool colorRandomOption, bool rainbowColorOption);
		bool animationFlag;
		bool colorRandomOption = false;
		bool rainbowColorOption = false;
		double size = 1;


		int cycle = 0;

	};

	class DrawingLine : public Polygon0
	{
	public:

		DrawingLine()
		{
			this->masterMatrixs = new MasterMatrix();
			Initialize();
		}

		DrawingLine(MasterMatrix* mastermatrix)
		{
			this->masterMatrixs = mastermatrix;
			Initialize();
		}

		void ObjectiveRendering();
		void AddPoints(GLVector3 point);






		const int lineLimit = 5;
	protected:
		bool confirm = false;


	};


	class GLAnimator
	{
	public:
		GLAnimator()
		{


			this->asd = new list<TestNameSpace::GLAnimator::AnimatorParameter>;
		}

		enum AnimationKind
		{
			Scaling,
			AlphaBlending
		};

		struct AnimatorParameter
		{


			int keyFrame;
			int currentFrame;
			bool animationActivate;
			bool loop;
			AnimationKind animationKind;


		};


		list<TestNameSpace::GLAnimator::AnimatorParameter> *asd;
		int animatorParameterPoolingNum = 0;


		bool temp1 = true;
		bool temp2 = false;



		void ScalingAnimation(Polygon0* objectPointer);
		void AlphaBlendingAnimation(Polygon0* objectPointer);





	};


	class Greed : public Polygon0
	{
	public:

		Greed() : Polygon0()
		{

		}
		Greed(MasterMatrix* masterMatrix) : Polygon0(masterMatrix)
		{

		}


		struct GreedData
		{

			//20*20

			int width = 300;
			int height = 200;
			int size = 50;
			bool greed[24 * 2];
			int pointer = 0;

		};



		GreedData greedData;



		void DrawGreed();
		void FillTriangle();




	};


	class RunningMachine : public Polygon0
	{

	public:

		RunningMachine() : Polygon0()
		{



		}
		RunningMachine(MasterMatrix* masterMatrix) : Polygon0(masterMatrix)
		{

		}

		//슬슬 오버라이드로 해보자

		void DrawRunningMachine(float size, bool colorRandomOption, bool rainbowColorOption);
		void Generate();



	};

	class RunningPeople : public Polygon0
	{
	public:
		RunningPeople() : Polygon0()
		{



		}
		RunningPeople(MasterMatrix* masterMatrix) : Polygon0(masterMatrix)
		{


		}

		void DrawingRunningPeople(float size, bool colorRandomOption, bool rainbowColorOption);




	};


	class ChulbongPeople : public Polygon0
	{

	public:
		ChulbongPeople() : Polygon0()
		{


		}
		ChulbongPeople(MasterMatrix* masterMatrix) : Polygon0(masterMatrix)
		{

		}


		void DrawingChulbongPeople(float size, bool colorRandomOption, bool rainbowColorOption);




	};



	class BenchPressPeople : public Polygon0
	{
	public:
		BenchPressPeople() :Polygon0()
		{


		}

		BenchPressPeople(MasterMatrix* masterMatrix) :Polygon0(masterMatrix)
		{


		}


		void DrawingBenchPressPeople(float size, bool colorRandomOption, bool rainbowColorOption);





	};

	class GymTree : public Polygon0
	{
	public:
		GymTree() : Polygon0()
		{


		}
		GymTree(MasterMatrix* masterMatrix) : Polygon0(masterMatrix)
		{


		}

		void DrawingGymTree(float size, bool colorRandomOption, bool rainbowColorOption);

	};


	class Star : public Polygon0
	{
	public:
		Star() : Polygon0()
		{

			this->color4D = GLVector4((rand() % 11) / 10.0, (rand() % 11) / 10.0, (rand() % 11) / 10.0, 1);
		}
		Star(MasterMatrix* mastermatrix) : Polygon0(mastermatrix)
		{

			this->color4D = GLVector4((rand() % 11) / 10.0, (rand() % 11) / 10.0, (rand() % 11) / 10.0, 1);
		}


		void DrawingStar(float size, bool colorRandomOption, bool rainbowColorOption);


	};

	class Plane : public Polygon0
	{
	public:
		Plane() : Polygon0()
		{


		}

		Plane(MasterMatrix* masterMatrix) : Polygon0(masterMatrix)
		{


		}

		bool axisRotation = true;
		void Set(bool axisRotation);
		void DrawingPlane(float size, bool colorRandomOption, bool rainbowColorOption);




	};

	class OpenCube : public Polygon0
	{
	public:
		OpenCube() : Polygon0()
		{

			for (int i = 0; i < 6; ++i)
			{
				faceFluid[i] = false;
			}



			for (int i = 0; i < 4; ++i)
			{
				this->myAnimatorParameter[i].InitializeAnimatorParameter(120, 0, false, false);


			}

		}

		OpenCube(MasterMatrix* masterMatrix) : Polygon0(masterMatrix)
		{
			for (int i = 0; i < 6; ++i)
			{
				faceFluid[i] = false;
			}




			for (int i = 0; i < 4; ++i)
			{
				this->myAnimatorParameter[i].InitializeAnimatorParameter(120, 0, false, false);


			}
		}


		//반시계정렬
		GLfloat cube_vertices_fluid[8][3] =
		{
			{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};


		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};
		GLfloat cube_vertex_colors[8][3] =
		{
		{ 1.0, 0.0, 0.0 }, //Red
		{ 0.0, 1.0, 0.0 }, //Green
		{ 0.0, 0.0, 1.0 }, //Blue
		{ 1.0, 1.0, 1.0 }, //Yellow
		{ 0.0, 1.0, 1.0 }, //Cyan
		{ 1.0, 0.0, 1.0 }, //Magenta
		{ 1.0, 1.0, 1.0 }, //White
		{ 0.0, 0.0, 0.0 }  //Black
		};
		GLint cube_num_faces = 6;
		const short cube_faces[6][4] =
		{
		{ 3, 2, 1, 0 },
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 3, 0, 4, 7 },
		{ 1, 2, 6, 5 },
		{ 4, 5, 6, 7 }
		};

		MyAnimatorParameter myAnimatorParameter[4];

		bool faceFluid[6];

		bool frontControl = false;
		bool topControl = false;



		bool test[8];
		void OpenFront();
		void RollFront();

		void CloseFront();
		void RollBackFront();


		void OpenTop();
		void SpringRise();

		void CloseTop();
		void SpringContract();









		void DrawingOpenCube(float size, bool colorRandomOption, bool rainbowColorOption);



	};



	class Bezier : public Polygon0
	{

	public:
		Bezier() : Polygon0()
		{


		}
		Bezier(MasterMatrix* masterMatrix) : Polygon0(masterMatrix)
		{


		}





		void DrawCurveLine();


	};


	class BounceBall : public Polygon0
	{

	public:
		BounceBall() : Polygon0()
		{



		}

		BounceBall(MasterMatrix* masterMatrix) : Polygon0(masterMatrix)
		{



		}




		void Draw();
		//크기,색상정함

		void InitializeBall(
			float size,
			bool doYouWantDrawBoundingBox,
			bool landingActivate,
			GLVector3 velocity,
			GLVector3 jumpPower,
			int state
		);

		void StateEnter();


		void HandleEvent();

		void Update();
		void GetBoundingBoxVertices();
		void DrawBoundingBox();

		bool CollisionCheck();

		void AllProcess();

		GLVector3 boundingBoxRange[2];

		//FSM은 생략
		enum SimpleState
		{

			Idle,
			JumpUp,
			Fall


		};
		std::vector<int> stateStack;

		struct BounceBallProperty
		{

			
			SimpleState state = Idle;

			GLVector3 velocity;

			GLVector3 jumpPower;


			bool doYouWantDrawBoundingBox = false;

			//착지를 할것인가. 안한다면 떨어진다.
			bool landingActivate = false;

			double landingYPosition = 0;






		};
		BounceBallProperty bounceBallProperty;




	};

}