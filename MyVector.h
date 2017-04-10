#pragma once

#include "Construct.h"
#include "Allocator.h"

template<class T, class Alloc = alloc>
class Vector
{
	typedef SimpleAlloc<T, Alloc> DataAllactor;
public:
	typedef T* Iterator;

	Vector()
		:_start(NULL)
		,_finish(NULL)
		,_endOfStorage(NULL)
	{}

	~Vector()
	{
		Destroy(Begin(), End());
		DataAllactor::Deallocate(_start, Size());
	}

	Iterator Begin()
	{
		return _start;
	}

	Iterator End()
	{
		return _finish;
	}

	void PushBack(const T& x)
	{
		if(Size() == Capacity())
			_Expand(Size()*2 + 3);

		//*_finish = x;
		Construct(_finish, x); // new定位
		++_finish;
	}

	void Reserve(size_t n)
	{
		_Expand(n);
	}

	void Resize(size_t n)
	{
		if (n < Size())
		{
			_finish = _start + n; 
		}
		else if (n < Capacity())
		{
			// 
		}
		else
		{
			_Expand(n);
			// 
		}
	}

	size_t Capacity()
	{
		return _endOfStorage - _start;
	}

	size_t Size()
	{
		return _finish - _start;
	}

protected:
	void _Expand(size_t n)
	{
		if (n > Capacity())
		{
			// 开辟空间
			T* tmp = DataAllactor::Allocate(n);

			// 
			for (size_t i = 0; i < Size(); ++i)
			{
				// 显示调构造
				Construct(tmp+i, _start[i]);
			}

			size_t n = Size();

			// 显示调析构
			// 释放空间
			// T*
			Destroy(_start, _finish);
			DataAllactor::Deallocate(_start, n);

			_start = tmp;
			_finish = _start + n;
			_endOfStorage = _start + n;
		}
	}

protected:
	Iterator _start;
	Iterator _finish;
	Iterator _endOfStorage;
};

void TestVector()
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);

	Vector<string> v1;
	v1.PushBack("5");
	v1.PushBack("6");

	cout<<"Vector:"<<Distance(v.Begin(), v.End())<<endl;

	//Vector<int>::Iterator it = v.Begin();
	//while(it != v.End())
	//{
	//	cout<<*it<<" ";
	//	++it;
	//}
	//cout<<endl;
}