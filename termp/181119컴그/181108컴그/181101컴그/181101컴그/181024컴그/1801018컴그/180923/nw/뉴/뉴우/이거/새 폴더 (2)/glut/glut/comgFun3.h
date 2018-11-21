#pragma once
#define MAX_LIST_SIZE 200
#define NULL_VALUE -858993460

enum Direction {
	Stand,
	Up,
	Right,
	Down,
	Left

};

struct Position2 {

	int x;
	int y;

};



struct Position3 {

	int x;
	int y;
	int z;

};

class Vector2 {
public:
	Vector2() {

		this->position.x = 0;
		this->position.y = 0;

	}
	Vector2(int x, int y) {

		this->position.x = x;
		this->position.y = y;
	}

	Position2 position;
};

class Vector3 {

public:

	Vector3() {

		this->position.x = 0;
		this->position.y = 0;
		this->position.y = 0;

	}
	Vector3(int x, int y, int z) {

		this->position.x = x;
		this->position.y = y;
		this->position.z = z;
	}

	Position3 position;
};

class TurnInfo {
public:

	Vector2 vector2;

	int oneSideStack = 0;

	Direction direction;


	TurnInfo() {

		this->vector2.position.x = 0;
		this->vector2.position.y = 0;
		direction = Stand;
		oneSideStack = 0;

	}
	TurnInfo(int x, int y) {
		this->vector2.position.x = x;
		this->vector2.position.y = y;
		direction = Stand;
		oneSideStack = 0;
	}
	TurnInfo(int x, int y, Direction direction) {
		this->vector2.position.x = x;
		this->vector2.position.y = y;
		this->direction = direction;
		oneSideStack = 0;
	}

	TurnInfo(int x, int y, Direction direction, int oneSideStack) {
		this->vector2.position.x = x;
		this->vector2.position.y = y;
		this->direction = direction;
		this->oneSideStack = oneSideStack;

	}
};



class TurnInfoList {

public:

	TurnInfoList()
	{
		sizeLimit = MAX_LIST_SIZE;
		length = 0;
		//printf("리스트 생성.\n");

		for (int i = 0; i < MAX_LIST_SIZE; ++i) {

			this->turnInfo[i] = ReturnNullVector2();

		}
	}

	TurnInfoList(int size)
	{

		sizeLimit = size;
		length = 0;
		//printf("리스트 생성.\n");

		for (int i = 0; i < MAX_LIST_SIZE; ++i) {

			this->turnInfo[i] = ReturnNullVector2();

		}

	}


	void Add(TurnInfo turnInfo) {

		if (!OverTheSizeLimit()) {
			this->turnInfo[length++] = turnInfo;
		}




	}
	void AddAt(TurnInfo turnInfo, int index) {

		if (!OverTheSizeLimit()) {

			if (IndexAvailabilityCheck(index)) {

				for (int i = length; i > index; --i) {

					this->turnInfo[i] = this->turnInfo[i - 1];

				}

				this->turnInfo[index] = turnInfo;


				++length;



			}
		}

	}

	int AddReturnIndexAfter(TurnInfo turnInfo) {

		if (!OverTheSizeLimit()) {
			this->turnInfo[length++] = turnInfo;
		}

		return length;
	}
	void Remove() {


		if (length > 0) {

			this->turnInfo[length - 1] = ReturnNullVector2();

			length--;
		}


	}
	void RemoveAt(int index) {

		if (IndexAvailabilityCheck(index)) {

			for (int i = index; i < length - 1; ++i) {
				this->turnInfo[i] = this->turnInfo[i + 1];
			}

			this->turnInfo[length] = ReturnNullVector2();

			length--;

		}


	}
	void RemoveAtRange(int index1, int index2) {

		if (IndexAvailabilityCheck(index1) && IndexAvailabilityCheck(index2)) {


			if (index1 <= index2) {

				for (int i = index1; i < index2 + 1; ++i) {

					this->turnInfo[i] = ReturnNullVector2();
					length--;

				}




				return;
			}

			else if (index1 > index2) {


				for (int i = index2; i < index1 + 1; ++i) {

					this->turnInfo[i] = ReturnNullVector2();
					length--;
				}

				return;

			}



		}




	}
	void RemoveAndStay(int index) {

		if (IndexAvailabilityCheck(index)) {


			this->turnInfo[0] = ReturnNullVector2();
			--length;

			return;
		}

	}


	void RemoveAll() {

		for (int i = 0; i < length; ++i) {

			this->turnInfo[i] = ReturnNullVector2();


		}

		length = 0;
	}
	int Length() {

		return length;
	}

	int SizeLimit() {

		return sizeLimit;
	}

	TurnInfo GetDataOfIndex(int index) {



		return this->turnInfo[index];


		//반환값이 없으면 어떻게돼냐?

	}
	bool OverTheSizeLimit() {

		return length >= sizeLimit;
	}

	bool IndexAvailabilityCheck(int index) {


		return ((index < length) && (index >= 0));


	}

	TurnInfo ReturnNullVector2() {

		return TurnInfo(NULL_VALUE, NULL_VALUE);

	}

private:


	TurnInfo turnInfo[MAX_LIST_SIZE];
	int length;
	int sizeLimit;





};




class Matrix {

public:

	Matrix() {




		SetMatrix();




	}

	void SetMatrix() {

		srand((unsigned)time(NULL));

		for (int i = 0; i < this->size; ++i) {

			for (int j = 0; j < this->size; ++j) {

				matrix[i][j] = rand() % 2;

			}

		}
		for (int i = 0; i < this->size; ++i) {

			for (int j = 0; j < this->size; ++j) {

				matrix2[i][j] = rand() % 2;

			}

		}

	}

	int Determinant() {


		return matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1] - (matrix[0][0] * matrix[1][2] * matrix[2][1]) - (matrix[0][1] * matrix[1][0] * matrix[2][2]) - (matrix[0][2] * matrix[1][1] * matrix[2][0]);

	}

	void ShowDeterminant() {




		for (int i = 0; i < 3; ++i) {

			printf("| ");
			for (int j = 0; j < 3; ++j) {



				printf("%d ", matrix[i][j]);

			}
			printf("| ");

			if (i == 1) {

				printf(" = ");
			}
			else
			{
				printf("   ");
			}



			if (i == 1) {


				printf("%d", Determinant());
			}




			printf("\n");


		}

	}

	void ShowMatrix(int dimension) {

		if (dimension > size) {
			printf("\n");
			return;
		}

		for (int i = 0; i < dimension; ++i) {

			printf("| ");
			for (int j = 0; j < dimension; ++j) {



				printf("%d ", matrix[i][j]);

			}
			printf("| ");
			printf("\n");


		}


	}
	void ShowMatrixPair(int dimension, char oper) {


		if (dimension > size) {
			printf("\n");
			return;
		}


		printf("\n");

		for (int i = 0; i < dimension; ++i) {
			printf("| ");


			for (int j = 0; j < dimension; ++j) {



				printf("%d ", matrix[i][j]);

			}

			printf("| ");

			for (int k = 0; k < 3; ++k) {

				if (k == 1 && i == dimension / 2) {
					printf("%c", oper);

				}
				else {

					printf(" ");
				}
			}

			printf("| ");


			for (int j = 0; j < dimension; ++j) {



				printf("%d ", matrix2[i][j]);

			}

			printf("| ");

			for (int k = 0; k < 3; ++k) {

				if (k == 1 && i == dimension / 2) {
					printf("%c", '=');

				}
				else {

					printf(" ");
				}
			}

			printf("| ");


			for (int j = 0; j < dimension; ++j) {



				printf("%d ", result[i][j]);

			}

			printf("| ");






			printf("\n");

		}





	}

	void ShowOperating(int dimension, char oper) {
		if (dimension > size) {
			return;
		}
		int temp = 0;
		switch (oper)
		{

		case 'M':




			for (int j = 0; j < dimension; ++j) {


				for (int k = 0; k < dimension; ++k) {

					for (int l = 0; l < dimension; ++l) {
						temp += matrix[j][l] * matrix2[l][k];
					}


					result[j][k] = temp;

					temp = 0;

				}




			}




			ShowMatrixPair(dimension, '*');

			break;



		case 'm':




			for (int j = 0; j < dimension; ++j) {


				for (int k = 0; k < dimension; ++k) {

					for (int l = 0; l < dimension; ++l) {
						temp += matrix[j][l] * matrix2[l][k];
					}


					result[j][k] = temp;

					temp = 0;

				}




			}




			ShowMatrixPair(dimension, '*');

			break;


		case 'D':


			for (int i = 0; i < dimension; ++i) {

				for (int j = 0; j < dimension; ++j) {


					result[i][j] = matrix[i][j] - matrix2[i][j];

				}


			}

			ShowMatrixPair(dimension, '-');


			break;

		case 'd':


			for (int i = 0; i < dimension; ++i) {

				for (int j = 0; j < dimension; ++j) {



					result[i][j] = matrix[i][j] - matrix2[i][j];

				}


			}

			ShowMatrixPair(dimension, '-');


			break;

		case 'A':




			for (int i = 0; i < dimension; ++i) {

				for (int j = 0; j < dimension; ++j) {



					result[i][j] = matrix[i][j] + matrix2[i][j];

				}


			}

			ShowMatrixPair(dimension, '+');

			break;

		case 'a':


			for (int i = 0; i < dimension; ++i) {

				for (int j = 0; j < dimension; ++j) {



					result[i][j] = matrix[i][j] + matrix2[i][j];

				}


			}

			ShowMatrixPair(dimension, '+');


			break;


		case 'R':

			ShowDeterminant();

			break;

		case 'r':

			ShowDeterminant();
			break;



		case 'H':

			printf("현재행렬\n");
			ShowMatrix(3);


			for (int i = 0; i < 4; ++i) {

				matrix[3][i] = 0;

				matrix[i][3] = 0;

			}

			matrix[3][3] = 1;

			printf("\n");
			printf("4*4행렬\n");


			ShowMatrix(4);

			break;

		case 'h':
			printf("현재행렬\n");
			ShowMatrix(3);


			for (int i = 0; i < 4; ++i) {

				matrix[3][i] = 0;

				matrix[i][3] = 0;

			}

			matrix[3][3] = 1;

			printf("\n");
			printf("4*4행렬\n");


			ShowMatrix(4);

			break;

		case 'q':

			printf("프로그램을 종료합니다\n");
			exit(1);

			break;
		case 'Q':

			printf("프로그램을 종료합니다\n");
			exit(1);

			break;

		default:
			printf("잘못된 입력입니다.");
			break;
		}


		printf("\n");

	}


private:
	static const int size = 4;
	int row;
	int column;
	int matrix[size][size];
	int matrix2[size][size];
	int result[size][size];

};

class Vector3List
{
public:


	Vector3List()
	{
		sizeLimit = MAX_LIST_SIZE;
		length = 0;
		printf("리스트 생성.\n");

		for (int i = 0; i < MAX_LIST_SIZE; ++i) {

			this->vector3[i] = ReturnNullVector3();

		}
	}

	Vector3List(int size)
	{

		sizeLimit = size;
		length = 0;
		printf("리스트 생성.\n");

		for (int i = 0; i < MAX_LIST_SIZE; ++i) {

			this->vector3[i] = ReturnNullVector3();

		}

	}



	void Add(Vector3 vector3) {

		if (!OverTheSizeLimit()) {

			for (int i = 0; i < sizeLimit; ++i) {

				if (CheckVector3Equals(this->vector3[i], ReturnNullVector3())) {

					this->vector3[i] = vector3;
					length++;
					return;
				}
			}

			this->vector3[length++] = vector3;
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
	void AddAt(Vector3 vector3, int index) {

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

	int AddReturnIndexAfter(Vector3 vector3) {


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

	Vector3 GetDataOfIndex(int index) {



		return this->vector3[index];


		//반환값이 없으면 어떻게돼냐?

	}
	bool OverTheSizeLimit() {

		return length >= sizeLimit;
	}

	bool IndexAvailabilityCheck(int index) {


		return ((index < sizeLimit) && (index >= 0));


	}

	Vector3 ReturnNullVector3() {

		return Vector3(NULL_VALUE, NULL_VALUE, NULL_VALUE);

	}

	bool CheckVector3Equals(Vector3 v1, Vector3 v2) {

		if (v1.position.x == v2.position.x && v1.position.y == v2.position.y) {

			return true;
		}
		return false;
	}
private:


	Vector3 vector3[MAX_LIST_SIZE];
	int length;
	int sizeLimit;
	int lastIndex;
	int firstIndex;

};




__interface IInterface
{

};
