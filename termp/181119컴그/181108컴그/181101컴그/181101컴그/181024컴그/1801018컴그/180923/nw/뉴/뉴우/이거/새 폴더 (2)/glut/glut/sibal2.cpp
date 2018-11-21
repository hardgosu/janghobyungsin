
#include "stdafx.h"
#include "ProjectLibrary.h"



using namespace TestNameSpace;

int main()
{


	std::vector<int> sibal;
	std::vector<GLVector3> sibal2;

	sibal.push_back(33);
	sibal.push_back(33);

	sibal.push_back(33);

	sibal.pop_back();
	printf("%d\n", sibal.size());


	for (int i = 0; i < sibal.size(); ++i)
	{
		sibal[i] *= i;
		printf("%d\n", sibal[i]);
	}


	for (int i = 0; i < sibal2.size(); ++i)
	{
		sibal2[i].x = i * 4;
		printf("%f %f %f\n", sibal2[i].x, sibal2[i].y, sibal2[i].z);

	}


	printf("%dddd\n", sibal.back());
}


/*
int main()
{


	FILE *fp = NULL;

	fp = fopen("data.txt", "r");

	char vari[30];

	if (fp == NULL)
	{
		printf("파일을 열수없다");
		return 1;
		fclose(fp);
		return 1;
	}

	else
	{

		printf("파일열기성공\n");
	}

	while (fscanf(fp, "%s", vari) != EOF)
	{

		printf("%s\n", vari);
	}

	fclose(fp);
	return 0;
}

*/