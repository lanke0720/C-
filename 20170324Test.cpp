#include <iostream>
using namespace std;

/*
void FunTest()
{
	int* p1 = new int;
	int* p2 = new int(10);
	int* p3 = new int[10];

	delete p1;
	delete p2;
	delete[] p3;
}


int main()
{
	return 0;
}
*/

/*
class Test
{
public:
	Test()
	{
		_data = 10;
		cout<<"Test()"<<endl;
	}

	~Test()
	{
		cout<<"~Test()"<<endl;
	}
	int _data;
};

void FunTest()
{
	Test* p1 = new Test;
	Test* p2 = (Test*)malloc(sizeof(Test));
	//Test* p2 = new Test[10];

	free(p1);
	delete p2;
	//delete p1;
	//free(p2);
	//delete[] p2;
}

int main()
{
	FunTest();
	return 0;
}
*/

/*
class Test
{
public:
	Test()
	{
		_data = 0;
		cout<<"Test():"<<this<<endl;
	}

	~Test()
	{
		cout<<"~Test():"<<this<<endl;
	}
	int _data;
};

void FunTest()
{
	Test* p1 = new Test[10];//44

	//delete[] p1;
	delete p1;
}


void FunTest1()
{
	Test* p1 = (Test*)malloc(sizeof(Test));
	Test* p2 = (Test*)malloc(sizeof(Test));
	
	Test* p3 = new Test;
	Test* p4 = new Test;
			   
	Test* p5 = new Test[10];
	Test* p6 = new Test[10];

	delete p1;
	delete[] p2;
	free(p3);
	delete[] p4;

	free(p5);
	delete p6;

	/*
	int* p1 = (int*)malloc(sizeof(int));
	int* p2 = (int*)malloc(sizeof(int));

	int* p3 = new int;
	int* p4 = new int;

	int* p5 = new int[10];
	int* p6 = new int[10];

	delete p1;
	delete[] p2;
	free(p3);
	delete[] p4;

	free(p5);
	delete p6;
	*
}


int main()
{
	 FunTest1();
	//FunTest();
	return 0;
}
*/

/*
class Test
{
public:
	Test()
	{
		_data = 0;
		cout<<"Test():"<<this<<endl;
	}

	~Test()
	{
		cout<<"~Test():"<<this<<endl;
	}
	int _data;
};

void* operator new(size_t size, const char* nameFile, const char* funcName,
	size_t lineNo)
{
	cout<<nameFile<<":"<<funcName<<":"<<lineNo<<":"<<size<<endl;
	return malloc(size);
}

#ifdef _DEBUG
#define new new(__FILE__, __FUNCDNAME__, __LINE__)
#else
#endif

//delete

void FunTest()
{
	Test* p = new Test;
	int* p1 = new int;
}

int main()
{
	FunTest();
	return 0;
}

int main()
{
int array[10];
array[3] = 3;
*(array+3) = 3;

new(array+4) int(4);  //定位new表达式
return 0;
}
*/

/*
class Test
{
public:
	Test(int data)
		: _data(data)
	{
		cout<<"Test():"<<this<<endl;
	}

	~Test()
	{
		cout<<"~Test():"<<this<<endl;
	}
	int _data;
};


void FunTest()
{
	Test* p = (Test*)malloc(10*sizeof(Test));
	
	new(p) Test(0);
	new(p+1) Test(1);
	new(p+2) Test(2);
	new(p+3) Test(3);

	// 析构函数
	free(p);
}

int main()
{
	FunTest();
	return 0;
}
*/


class Test
{
public:
	Test(int data = 0)
		: _data(data)
	{
		cout<<"Test():"<<this<<endl;
	}

	~Test()
	{
		cout<<"~Test():"<<this<<endl;
	}
	int _data;
};

Test* New()
{
	Test* p = (Test*)malloc(sizeof(Test));
	new(p) Test();
	return p;
}

void Delete(Test*& p)
{
	p->~Test();
	free(p);
	p = NULL;
}

Test* NewArray(size_t N)
{
	Test* p = (Test*)malloc(sizeof(Test)*N + 4);
	*(int*)p = N;
	//p = (Test*)((int*)p + 1);
	p = (Test*)((int)p + 4);

	for (size_t idx = 0; idx < N; ++idx)
	{
		new(p+idx) Test();
	}

	return p;
}

//delete[] --> N --> 倒着释放每个对象的资源-->释放空间
void DeleteArray(Test*& p)
{
	int* pStart = (int*)p - 1;
	size_t N = *pStart;

	for (int idx = N-1; idx >= 0; --idx)
	{
		(p+idx)->~Test();
	}

	free(pStart);
	p = NULL;
}

void FunTest()
{
	//Test* p = New();
	//Delete(p);
	//p = NULL;

	Test* p = NewArray(10);
	DeleteArray(p);
}

int main()
{
	FunTest();
	return 0;
}