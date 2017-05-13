#ifndef __HEAP__
#define __HEAP__
#include<iostream>
#include<vector>
using namespace std;
template<class T>
struct Less
{
	bool operator()(const T& a,const T& b)
	{
		return a<b;
	}
};
template<class T>
struct Greater
{
	bool operator()(const T& a,const T& b)
	{
		return a>b;
	}
};

template<typename T,class com = Greater<int>>
class Heap
{
public:
	//���캯��
	Heap()
	{}
	//����
	Heap(T* a, size_t n)
		:_a(a,a+n)
	{
		/*_a.reserve(n);
		for(size_t i = 0; i<n; i++)
		{
			_a.push_back(a[i]);
		}*/
		for(int i = (_a.size()-2)/2; i>=0; i--)
		{
			_Adjustdown(i);
		}
	}
	//β��
	void Push(const T& x)
	{
		_a.push_back(x);
		_Adjustup(_a.size()-1);
	}
	//βɾ
	void Pop()
	{
		swap(_a[0],_a[_a.size()-1]);
		_a.pop_back();
		_Adjustdown(0);
	}
	//�����Ԫ�صĸ���
	size_t Size()
	{
		return _a.size();
	}
	//��Ѷ���Ԫ��
	T& Top()
	{
		return _a[0];
	}
	//�ж϶��Ƿ�Ϊ��
	bool Empty()
	{
		return _a.size()==0;
	}
	
protected:
	//���µ���
	void _Adjustdown(int root)
	{
		int parent = root;
		int child = parent*2+1;
		//�˴���������������
		//һ���ǵ����ӵ�ֵС�ڸ�ĸ��ֵʱ������Ѿ���break�������
		//�ڶ����������ǵ���Ҷ�ӽڵ��ʱ��
		while(child<_a.size())
		{
			//�����Һ�����ֵ����
			if(child+1<_a.size() && com()(_a[child+1],_a[child]))
			{
				++child;
			}
			//�����Ӻ͸�ĸ���Ƚ�
			if(com()(_a[child],_a[parent]))
			{
				swap(_a[child],_a[parent]);
				parent = child;
				child = parent*2+1;
			}
			else
			{
				break;
			}
		}
	}
	//���ϵ���
	void _Adjustup(int i)
	{
		//Compare com;
		int child = i;
		int parent = (i-1)/2;
		while(child >= 0)
		{
			if(com()(_a[child] , _a[parent]))
			{
				swap(_a[child],_a[parent]);
				child = parent;
				parent = (parent-1)/2;
			}
			else
			{
				break;
			}
		}
	}
protected:
	vector<T> _a;
};

#endif