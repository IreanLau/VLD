//#define _CRT_SECURE_NO_WARNINGS
//
//#pragma once
//#include<iostream>
//#include <Windows.h>
//#include <stdio.h>
//using namespace std;
//
//typedef struct MemNode
//{
//	int size;
//	char* file;
//	int line;
//	struct MemNode* Link;
//}MemNode;
//
//static  MemNode* _AfxMem;		//用于计数
//
//void* operator new(size_t sz,char *filename,int ln)
//{
//	void* result;
//	int Total_Size = sz + sizeof(MemNode);
//	MemNode* p = (MemNode*)malloc(Total_Size);
//	p->size = sz;
//	p->file = filename;
//	p->line = ln;
//	p->Link = NULL;
//
//	if (_AfxMem)
//	{
//		_AfxMem = p;
//	}
//	else 
//	{
//		p->Link = _AfxMem;
//		_AfxMem = p;
//	}
//	result = p + 1;
//	return result;
//}
//
//
//
//
//void operator delete(void * ptr)
//{
//	if (_AfxMem == NULL)
//		return;
//	if (ptr == NULL)
//		return ;
//
//	MemNode* p;
//	if (_AfxMem + 1 == ptr)
//	{
//		p = _AfxMem;
//		_AfxMem = p->Link;
//		delete p;
//	}
//	else
//	{
//		p = _AfxMem;
//		while (p->Link != NULL && p->Link + 1 != ptr)
//			p = p->Link;
//		if (p->Link != NULL)
//		{
//			MemNode *q = p->Link;
//			p->Link = q->Link;
//			delete q;
//		}
//		
//	}
//}
//
//void operator delete[](void * ptr)
//{
//	operator delete(ptr);
//}
//
//
//
//void cheak_vld()
//{
//	if (_AfxMem == NULL)
//	{
//		OutputDebugStringA("__________________________________________________________________________\n");
//		OutputDebugStringA("No memory leaks detected. \n");
//		OutputDebugStringA("__________________________________________________________________________\n");
//		cout << "No memory leaks detected." << endl;
//	}
//	else
//	{
//		MemNode* p = _AfxMem;
//		OutputDebugStringA("__________________________________________________________________________\n\n");
//		OutputDebugStringA("WARNING: Detector \n");
//		cout << "WARNING: Detector" << endl;
//		while (p != NULL)
//		{
//			
//			char str[100] = { 0 };
//			
//			sprintf_s(str,"At: %p   total: %d Byte \n",p+1, p->size);
//			OutputDebugStringA(str);
//			sprintf_s(str, " FILE:%s   line:%d \n", p->file, p->line);
//			OutputDebugStringA(str);
//			OutputDebugStringA("__________________________________________________________________________\n");
//
//			cout << "At " << p + 1 << " " << p->size << " Byte!" << endl;
//			cout << " FILE:"<<p->file<<" line:"<<p->line<<endl;
//			p = p->Link;
//		}
//		
//	}
//}
//
//class VLD
//{
//public:
//	VLD()
//	{}
//	~VLD()
//	{
//		cheak_vld();
//		//cout << "VLD xigou" << endl;
//	}
//};
//
//static VLD obj;
//
//
//
//#define new new(__FILE__, __LINE__)
