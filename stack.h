
#pragma once
#include<iostream>
using namespace std;

template<class T>
class Stack
{
public:
	Stack()
		:_a(NULL)
		,_size(0)
		,_capacity(0)
	{}
	~Stack()
	{
		delete _a;
		_a = NULL;
		_size = _capacity = 0;
	}

public:
	bool empty()
	{
		return _size == 0;
	}
	size_t size()
	{
		return _size;
	}
	size_t Top()
	{
		return _a[0];
	}
	void Push(const T& x)
	{
		checkcapacity();
		_a[_size++] = x;
	}
	void Pop()
	{
		--_size;
	}

	void checkcapacity()
	{
		if(_size >= _capacity)
		{
			T* _a1 = new T[2*sizeof(T)*_capacity+2];
			for(size_t idx = 0;idx < _capacity; ++idx)
			{
				_a1[idx] = _a[idx];		
			}
			delete[] _a;
			_a = _a1;
			_capacity=2*_capacity+2;
		}
	}

protected:
	T* _a;
	size_t _size;
	size_t _capacity;

};


