//#define _CRT_SECURE_NO_WARNINGS
//#pragma once
//
//#include <iostream>
//#include<Windows.h>
//#include<stdio.h>
//
//
//
//using namespace std;
//
//#define BUCKET_NUM 3
//#define P 13
//
//
//typedef struct MemCookie
//{
//	int size;
//	char* file;
//	int line;
//}MemCookie;
//
//typedef struct hash_node
//{
//	MemCookie* bucket[BUCKET_NUM];
//	hash_node* link;
//}hash_node;
//
//
//typedef hash_node hash_table[P];
//
//static hash_table ht;
//static int hash_table_size;
//
//void creatHashtable(hash_table& ht)
//{
//	for (int i = 0; i < P; i++)
//	{
//		for (int l = 0; l < BUCKET_NUM; l++)
//			ht[i].bucket[l] = NULL;
//		ht[i].link = NULL;
//	}
//}
//void inithashnode(hash_node*& t)
//{
//	t->link = NULL;
//	for (int l = 0; l < BUCKET_NUM; l++)
//		t->bucket[l] = NULL;
//}
//
//int Hash(void* point)
//{
//	return (int)point % P;
//}
//
//void* operator new(size_t sz, char* filename, int line)
//{
//	hash_table_size++;
//
//	void* result;
//	int totle_size = sz + sizeof(MemCookie);
//	MemCookie* s = (MemCookie*)malloc(totle_size);
//	s->file = filename;
//	s->line = line;
//	s->size = sz;
//	result = s + 1;
//	int index = Hash(result);
//
//for (int l = 0; l < BUCKET_NUM; l++)
//	if (ht[index].bucket[l] == NULL)
//	{
//		ht[index].bucket[l] = s;
//		return result;
//	}
//hash_node* prev = ht + index;
//while (prev->link != NULL)
//{
//	for (int l = 0; l < BUCKET_NUM; l++)
//		if (prev->link->bucket[l] == NULL)
//		{
//			prev->link->bucket[l] = s;
//			return result;
//		}
//	prev = prev->link;
//}
//	hash_node* t = (hash_node*)malloc(sizeof(hash_node));
//	inithashnode(t);
//	t->bucket[0] = s;
//	prev->link = t;
//
//	return result;
//}
//
//void operator delete(void* p)
//{
//	int index = Hash(p);
//	hash_node* s = ht + index;
//
//	while (s != NULL)
//	{
//		for (int l = 0; l < BUCKET_NUM; l++)
//			if (s->bucket[l] + 1 == p)
//			{
//				free(s->bucket[l]);
//				s->bucket[l] = NULL;
//				hash_table_size--;
//				return;
//			}
//		s = s->link;
//	}
//}
//
//void* operator new[](size_t sz, char* filename, int line)
//{
//	return operator new(sz, filename, line);
//}
//void* operator new(size_t sz, void* p, char* filename, int line)
//{
//	return p;
//}
//void operator delete[](void* p)
//{
//	operator delete(p);
//}
//
//void check_vld()
//{
//
//	if (hash_table_size == 0)
//	{
//		cout << "No memory leaks detected" << endl;
//		OutputDebugStringA("No memory leaks detected\n");
//		return;
//	}
//	OutputDebugStringA("                          WARNING : Memory leak\n");
//
//#ifdef PRINT1
//	cout << "                          WARNING : Memory leak" << endl;
//
//	cout << "______________________________________________________________________________________________" << endl;
//#endif // PRINT1
//
//
//	OutputDebugStringA("_____________________________________________________________________________________\n");
//
//	int count = 0, allsize = 0;
//	char str[100] = { 0 };
//
//	for (int i = 0; i < P; i++)
//	{
//		hash_node* s = ht + i;
//		while (s)
//		{
//			for (int l = 0; l < BUCKET_NUM; l++)
//			{
//				if (s->bucket[l] != NULL)
//				{
//					count++;
//					allsize += s->bucket[l]->size;
//					sprintf_s(str, "FILE:%s\n", s->bucket[l]->file);
//					OutputDebugStringA(str);
//					sprintf_s(str, "line:%d\n", s->bucket[l]->line);
//					OutputDebugStringA(str);
//					sprintf_s(str, "At:%p  Size:%d\n", s->bucket[l] + 1, s->bucket[l]->size);
//					OutputDebugStringA(str);
//					OutputDebugStringA("____________________________________________________________________________________________\n");
//
//#ifdef PRINT2
//					cout << "FILE:" << s->bucket[l]->file << endl;
//					cout << "LINE:" << s->bucket[l]->line << endl;
//					cout << "At:" << s->bucket[l] + 1 << "   Size:" << s->bucket[l]->size << endl;
//					cout << "-----------------------------------------------------------------------------------------" << endl;
//#endif
//				}
//			}
//			s = s->link;
//		}
//	}
//	sprintf_s(str, "Count: %d, Total %d \n", count, allsize);
//	OutputDebugStringA(str);
//}
//
//class VLD
//{
//public:
//	VLD()
//	{
//		creatHashtable(ht);
//		hash_table_size = 0;
//	}
//	~VLD()
//	{
//		check_vld();
//	}
//};
//
//
//static VLD obj;
//#define new new(__FILE__,__LINE__)
//
//
