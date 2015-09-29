#define _CRT_SECURE_NO_WARNINGS
#pragma once

//#pragma comment(lib,"my_vld.lib")

#include <iostream>
#include<Windows.h>
#include<stdio.h>
using namespace std;

#define BUCKET_NUM 3
#define P 13


typedef struct MemCookie
{
	int size;
	char* file;
	int line;
}MemCookie;

typedef struct hash_node
{
	MemCookie* bucket[BUCKET_NUM];
	hash_node* link;
}hash_node;

typedef hash_node hash_table[P];

static hash_table ht;
static int hash_table_size;

size_t Hash(void* point)
{
	return (size_t)point%P;	// size_t£º·ÀÖ¹Ö¸Õë¹ý´ó
}

void creatHashtable(hash_table& ht)
{
	for (int i = 0; i < P; ++i)
	{
		for (int j = 0; j < BUCKET_NUM; j++)
			ht[i].bucket[j] = NULL;
		ht[i].link = NULL;
	}	
}

void inithashnode(hash_node*& t)
{
	t->link = NULL;
	for (int i = 0; i < BUCKET_NUM; i++)
	{
		t->bucket[i] = NULL;
	}
}



void* operator new(size_t sz, char* filename, int line)
{
	hash_table_size++;

	void *result;
	int total = sz + sizeof(MemCookie);
	MemCookie* s = (MemCookie*)malloc(sizeof(total));
	s->file = filename;
	s->line = line;
	s->size = sz;
	result = s + 1;
	int index = Hash(result);

	for (int i = 0; i < BUCKET_NUM; ++i)
	{
		if (ht[index].bucket[i] == NULL)
		{
			ht[index].bucket[i] = s;
			return result;
		}
			
	}

	hash_node* p = ht+index;
	while (p->link)
	{
		for (int i = 0; i < BUCKET_NUM; ++i)
		{
			if (p->bucket[i] == NULL)
			{
				p->bucket[i] = s;
				return result;
			}
		}
		p = p->link;		
	}

	hash_node* t = (hash_node*)malloc(sizeof(hash_node));
	inithashnode(t);
	t->bucket[0] = s;
	p->link = t;

	return result;
	
}

void operator delete(void * p)
{
	int index = Hash(p);
	hash_node* s = ht + index;

	while (s)
	{
		for (int i = 0; i < BUCKET_NUM; ++i)
		{
			if (s->bucket[i]+1 == p)
			{
				s->bucket[i] = NULL;
				delete s->bucket[i];
				hash_table_size--;
			}
		}
		s = s->link;
	}
	if (NULL == s)
		abort();
}

void* operator new[](size_t sz, char* filename, int line)
{
	return operator new(sz,filename,line);
}

void* operator new(size_t sz, void* p, char* filename, int line)
{
	return p;
}

void operator delete[](void * p)
{
	operator delete(p);
}

void cheak_vld()
{

	if (hash_table_size == 0)
	{
		cout << "No memory leaks detected" << endl;
		OutputDebugStringA("No memory leaks detected\n");
		return;
	}
	OutputDebugStringA("_____________________________________________________________________________________\n");
	OutputDebugStringA("                          WARNING : Memory leak\n");

#ifdef PRINT1
	cout << "                          WARNING : Memory leak" << endl;

	cout << "______________________________________________________________________________________________" << endl;
#endif // PRINT1


	OutputDebugStringA("_____________________________________________________________________________________\n");

	int count = 0, allsize = 0;
	char str[100] = { 0 };

	for (int i = 0; i < P; i++)
	{
		hash_node* s = ht + i;
		while (s)
		{
			for (int l = 0; l < BUCKET_NUM; l++)
			{
				if (s->bucket[l] != NULL)
				{
					count++;
					allsize += s->bucket[l]->size;
					sprintf_s(str, "FILE:%s\n", s->bucket[l]->file);
					OutputDebugStringA(str);
					sprintf_s(str, "LINE:%d\n", s->bucket[l]->line);
					OutputDebugStringA(str);
					sprintf_s(str, "At: %p  Size: %d\n", s->bucket[l] + 1, s->bucket[l]->size);
					OutputDebugStringA(str);
					OutputDebugStringA("____________________________________________________________________________________________\n");

#ifdef PRINT2
					cout << "FILE:" << s->bucket[l]->file << endl;
					cout << "LINE:" << s->bucket[l]->line << endl;
					cout << "At:" << s->bucket[l] + 1 << "   Size:" << s->bucket[l]->size << endl;
					cout << "-----------------------------------------------------------------------------------------" << endl;
#endif
				}
			}
			s = s->link;
		}
	}
	sprintf_s(str, "Count: %d, Total %d \n", count, allsize);
	OutputDebugStringA(str);
}




class VLD
{
public:

	void clear(hash_table& ht)
	{
		hash_node* p;
		hash_node* cur;
		for (int i = 0; i < P; ++i)
		{
			p = &ht[i];
			cur = p->link;
			while (cur)
			{
				p->link = cur->link;
				delete cur;
				cur = NULL;
			}
			for (int j = 0; j < BUCKET_NUM; ++j)
				p->bucket[j] = NULL;
		}
		hash_table_size = 0;
	}
public:
	VLD()
	{
		creatHashtable(ht);
		hash_table_size = 0;
	}
	~VLD()
	{
		cheak_vld();
		clear(ht);
	}
};

VLD obj;
#define new new(__FILE__,__LINE__)