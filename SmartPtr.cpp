//#include <iostream>
//#include <string>
//using namespace std;
//
//class Exception
//{
//public:
//	Exception(int id = 0, const char* msg = "")
//		:_errId(id)
//		,_errMsg(msg)
//	{}
//
//	virtual const char* What() = 0 ;
//
//	int GetErrId()
//	{
//		return _errId;
//	}
//protected:
//	int _errId;
//	string _errMsg;
//};
//
//class OutOfRange : public Exception
//{
//public:
//	OutOfRange(const char* msg = "")
//		:Exception(1, msg)
//	{}
//	
//	virtual const char* What()
//	{
//		_errMsg += "越界";
//		return _errMsg.c_str();
//	}
//
//};
//
//class BadAlloc : public Exception
//{
//public:
//	BadAlloc(const char* msg = "")
//		:Exception(2, msg)
//	{}
//
//	virtual const char* What()
//	{
//		_errMsg += "申请内存失败";
//		return _errMsg.c_str();
//	}
//};
//
//class OverFlow : public Exception
//{};
//
//template<class T, size_t N = 100>
//class Array
//{
//public:
//	T& operator[](size_t index)
//	{
//		if (index >= N)
//		{
//			throw OutOfRange(__FUNCTION__);
//		}
//
//		return _a[index];
//	}
//protected:
//	T _a[N];
//};
//
//// new[]
//template<class T>
//T* NewArray(size_t N)
//{
//	T* p = (T*)malloc(sizeof(T)*N);
//	if (p == 0)
//	{
//		//throw BadAlloc("模拟实现new[]的NewArray抛异常");
//		throw BadAlloc(__FUNCTION__);
//	}
//
//	for (size_t i = 0; i < N; ++i)
//	{
//		new(p+i)T();
//	}
//
//	return p;
//}
//
//#include <vector>
//
//int main()
//{
//	//try
//	//{
//	//	// vector
//	//	Array<int, 10> a1;
//	//	a1[0] = 0;
//	//	a1[10] = 10;
//
//	//	// new new[]
//	//	string* p = NewArray<string>(10);
//	//	char* p1 = NewArray<char>(0x7fffffff);
//	//}
//	//catch (Exception& e)
//	//{
//	//	cout<<e.What()<<endl;
//	//}
//	//try
//	//{
//	//	//char* p1 = new char[0x7fffffff];
//	//	vector<int> v1;
//	//	v1[1] = 0;
//	//}
//	//catch(exception& e)
//	//{
//	//	cout<<e.what()<<endl;
//	//}
//
//	return 0;
//}

//#include <iostream>
//using namespace std;
//
//// 智能指针
//// RAII != 智能指针是RAII的一种应用,智能管理对象的释放问题,能够像指针一样使用
//// RAII一种规范，一种解决问题的思想，利用构造函数初始化，析构函数释放资源
//
//template<class T>
//class AutoPtr
//{
//public:
//	AutoPtr(T* ptr = NULL)
//		:_ptr(ptr)
//	{}
//
//	~AutoPtr()
//	{
//		cout<<_ptr<<endl;
//		delete _ptr;
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//
//protected:
//	T* _ptr;
//};
//
//void F1()
//{
//	int* p1 = new int;
//	AutoPtr<int> ap1(p1);
//	*p1 = 10;
//	cout<<*p1<<endl;
//
//	*ap1 = 20;
//	cout<<*ap1<<endl;
//
//	char* p2 = new char[0x7fffffff];
//	AutoPtr<char> ap2(p2);
//}
//
//int main()
//{
//	try
//	{
//		F1();
//	}
//	catch(exception& e)
//	{
//		cout<<e.what()<<endl;
//	}
//
//	return 0;
//}
//
////void F1()
////{
////	string* p1 = new string[10];
////	char* p2 = NULL;
////	try
////	{
////		p2 = new char[0x7fffffff];
////		delete[] p1;
////		throw; //异常的重新抛出
////	}
////
////	// ...
////
////	delete[] p1;
////	delete[] p2;
////}


#include <iostream>
using namespace std;

// 智能指针
// RAII != 智能指针是RAII的一种应用,智能管理对象的释放问题,能够像指针一样使用
// RAII一种规范，一种解决问题的思想，利用构造函数初始化，析构函数释放资源

template<class T>
class AutoPtr // auto_ptr std
{
public:
	// RAII
	AutoPtr(T* ptr = NULL)
		:_ptr(ptr)
	{}

	// ap2(ap1)
	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}

	// ap2 = ap3;
	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		if (this != &ap)
		{
			// 释放之前管理的对象
			delete this->_ptr;
			_ptr = ap._ptr;

			// 转移管理权
			ap._ptr = NULL;
		}

		return *this;
	}

	~AutoPtr()
	{
		if(_ptr)
		{
			cout<<_ptr<<endl;
			delete _ptr;
			_ptr = NULL;
		}
	}

	// 像指针一样使用
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

protected:
	T* _ptr;
};

template<class T>
class ScopedPtr
{
public:
	// RAII
	ScopedPtr(T* ptr = NULL)
		:_ptr(ptr)
	{}

	~ScopedPtr()
	{
		if (_ptr)
		{
			delete _ptr;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	// 1.只声明不定义
	// 2.声明成私有
private:
	ScopedPtr(const ScopedPtr<T>& sp);
	ScopedPtr<T>& operator=(const ScopedPtr<T>&);

protected:
	T* _ptr;
};

//template<class T>
//ScopedPtr<T>::ScopedPtr(const ScopedPtr<T>& sp)
//	:_ptr(sp._ptr)
//{}

//int main()
//{
//	AutoPtr<int> ap1(new int(10));
//	AutoPtr<int> ap2 = ap1; // ap2(ap1);
//
//	AutoPtr<int> ap3(new int(20));
//	ap2 = ap3;
//
//	ScopedPtr<int> sp4(new int(30));
////	ScopedPtr<int> sp5(sp4);
//
//	return 0;
//}

template<class T>
struct Delete
{
	void operator()(T* ptr)
	{
		delete ptr;
	}
};

template<class T>
struct DeleteArray
{
	void operator()(T* ptr)
	{
		delete[] ptr;
	}
};

template<class T, class D = Delete<T>>
class SharedPtr
{
public:
	SharedPtr(T* ptr)
		:_ptr(ptr)
		,_countRef(new int(1))
	{}

	SharedPtr(const SharedPtr<T, D>& sp)
		:_ptr(sp._ptr)
		,_countRef(sp._countRef)
	{	
		++(*_countRef);
	}

	// sp1 = sp4
	SharedPtr<T, D>& operator=(const SharedPtr<T, D>& sp)
	{
		// 
		//this->Release();
		if(_ptr != sp._ptr)
		{
			Release();
			_ptr = sp._ptr;
			_countRef = sp._countRef;
			++(*_countRef);
		}

		return *this;
	}

	inline void Release()
	{
		if (--(*_countRef) == 0)
		{
			cout<<_ptr<<endl;
			//delete _ptr;
			_del(_ptr);
			delete _countRef;
		}
	}

	~SharedPtr()
	{
		Release();
	}

	//operator*()
	//operator->()

	int UseCount()
	{
		return *_countRef;
	}

protected:
	T* _ptr;		// 
	int* _countRef; // 引用计数

	D _del; // 定制的仿函数删除器
};

// 循环引用
// 定制删除器

int main()
{
	//SharedPtr<int> sp1(new int(10));
	//SharedPtr<int> sp2(sp1);
	//SharedPtr<int> sp3(sp2);

	//SharedPtr<int> sp4(new int(20));
	//sp1 = sp1;
	//sp1 = sp2;

	//sp1 = sp4;
	//sp2 = sp4;
	//sp3 = sp4;

	SharedPtr<string> sp1(new string);
	SharedPtr<string, DeleteArray<string>> sp2(new string[10]);

	return 0;
}

//struct AA
//{
//	int _a1;
//	int _a2;
//};

//int main()
//{
//	AutoPtr<int> ap1(new int(10));
//	*ap1 = 20;
//
//	// ap2像原生指针一样使用
//	AutoPtr<AA> ap2(new AA);
//	(*ap2)._a1 = 10;
//	(*ap2)._a2 = 20;
//
//	ap2->_a1 = 30;
//	ap2.operator->()->_a1 = 50;
//
//	ap2->_a2 = 40;
//
//	AA* p2 = new AA;
//	(*p2)._a1 = 10;
//	(*p2)._a2 = 20;
//	p2->_a1 = 30;
//	p2->_a2 = 40;
//
//	return 0;
//}

//#include <memory>
//#include <boost/scoped_ptr.hpp>
//#include <boost/shared_ptr.hpp>
//
//int main()
//{
//	auto_ptr<int> ap1(new int(10));
//	*ap1 = 20;
//	auto_ptr<int> ap2(ap1);
//	//*ap1 = 30;
//
//	boost::scoped_ptr<int> sp3(new int(20));
//	//boost::scoped_ptr<int> sp4(sp3);
//
//	boost::shared_ptr<int> sp5(new int(30));
//	boost::shared_ptr<int> sp6(sp5);
//	cout<<sp5.use_count()<<endl;
//
//	return 0;
//}
