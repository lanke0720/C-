#pragma once
#include <vector>
//

template <class T>
class Heap
{
public:
	Heap()
	{}

	Heap(T* a, size_t n)
		:_a(a, a+n)
	{
		/*_a.reserve(n);
		for(size_t i = 0; i < n ; ++i)
		{
			_a.push_back(a[i]);
		}*/
		//堆的创建，将一个元素向上或者下调整，调成大堆或者小堆
		for(size_t i = (n - 2)/2; i >= 0; --i) //注意减2  ， 遍历从非子节点的上一层开始
		{
			_AdjustDown(i);
		}
	}

	void Push(const T& x) //在数组的最后插入一个新的元素，采用向上调整的算法进行调整
	{
		_a.push_back(x);
		_AdjustUp(_a.size() + 1);
	}

	void Pop() // 将最后一个元素和0号下表的元素交换，删除最后一个元素，然后采用向下调整的算法进行调整
	{
		swap(_a[0], _a[_a.size() - 1]);
		_a.pop_back();
		_AdjustDown(0);
	}

protected:  
	void _AdjustUp(int child)
	{
		assert(_a.size() > 0);
		size_t parent = 0;
		while(child > 0)
		{
			parent =(child -1)/2;
			if(_a[parent] < _a[child])
			{

				swap(_a[parent],_a[child]);
				child = parent;
			}
			else 
				break;
		}
	}

	void _AdjustDown(size_t root)
	{
		size_t parent = root;
		size_t child = 0;
		while(child)
		{
			child = parent*2 + 1;
			if(child+1 < _a.size()
				&& _a[child + 1] > _a[child])
					++child;

			if(_a[child] > _a[parent])
			{
				swap(_a[parent], _a[child]);
				parent = child;			
			}	
			else 
				break;
		}
	}

protected:
	vector<T> _a;
};

void TestHeap()
{
	int a[] = {10,11,13,12,16,18,15,17,14,19};
	Heap<int> hp1(a,sizeof(a)/sizeof(a[0]));
	hp1.Push(20);
	hp1.Pop();
}