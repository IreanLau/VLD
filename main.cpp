#define _CRT_SECURE_NO_WARNINGS


//#include "VLD.h"
//#include "HashVld.h"
#include "_VLD_.h"

class Test
{
public:
	Test()
	{}
	Test(char *str)
	{
		ch = new char[strlen(str) + 1];
		strcpy(ch, str);
	}
	~Test()
	{
		delete[] ch;
		ch = NULL;
		//cout << "xigou" << endl;
	}
private:
	char *ch;
	int a;
	double b;
	char c;
};

void fun()
{
	cout << "error" << endl;
}




void main()
{

	int a;
	int *x = &a;
	;
	delete x;

	//int* a = new int(1);
	//delete a;

	/*int *q = new int[10];
	delete[] q;*/

	
	
	/*Test* p = new Test[10];
	Test t("hello");*/
	/*atexit(fun);
	cheak_vld();*/
	
}