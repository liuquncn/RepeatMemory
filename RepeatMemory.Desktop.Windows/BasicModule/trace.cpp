
#include <windows.h>
#include "trace.h"


fstream trace::tracefile;

bool trace::traceflag;
bool trace::trace_time_flag;
bool trace::trace_memory_flag;

long trace::trace_time::gettime()
{
	return GetTickCount();
}

int trace::trace_memory::newnumber;
int trace::trace_memory::delnumber;
int trace::trace_memory::memrecord[1000000];

void trace::trace_memory::setrecord(int index,bool value)
{
	int i=index>>5;
	int j=index&31;
	int mask=1<<j;
	if (value) memrecord[i]|=mask;
	else memrecord[i]&=~mask;
}

bool trace::trace_memory::getrecord(int index)
{
	int i=index>>5;
	int j=index&31;
	int mask=1<<j;
	return (memrecord[i]&mask)!=0;
}

void * trace::trace_memory::mynew(size_t n)
{
	/* debug --
	if (newnumber>=1625927 && newnumber<=1625941 || newnumber==1626652)
	{
		int x=0;
	}
	-- debug */
	void * p=malloc(n+4);
	if (p!=NULL)
	{
		*(int*)p=newnumber;
		setrecord(newnumber,true);
		newnumber++;
		return (char *)p+4;
	}
	else return NULL;
}

void trace::trace_memory::mydelete(void * p)
{
	if (p)
	{
		delnumber++;
		int number=*(int *)((char *)p-4);
		setrecord(number,false);
		::free((char *)p-4);
	}
}

void trace::trace_memory::mymemory()
{
	fstream tracefile("trace.txt",ios::app|ios::out);
	tracefile << "newnumber = " << newnumber << endl;
	tracefile << "delnumber = " << delnumber << endl;
	for (int i=0;i<newnumber;i++)
	{
		if (getrecord(i)==true)
			tracefile << "Memory Leak: " << i << endl;
	}
	tracefile.close();
}

/* --------------------------------------------------------- 
检查程序内存泄漏的方法：
 1. 请将下面程序的注释去掉；
 2. 并在整个程序退出时调用trace::trace_memory::mymemory()函数，
    运行时就会生成一个trace.txt文件，报告内存泄漏的newnumber值，
 3. 然后在trace::trace_memory::mynew()函数中设置相应断点，
    就可以检查哪次申请的内存没有被释放。
-----------------------------------------------------------*/

/*
using namespace trace;
using namespace trace_memory;

void * operator new(size_t n) { return mynew(n); }
void operator delete(void * p) { mydelete(p); }
*/

