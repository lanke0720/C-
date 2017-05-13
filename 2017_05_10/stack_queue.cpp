#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

//1,实现一个栈，要求实现Push(ru栈)，Pop(chu栈)，Min(返回最小值的操作)的时间复杂度为1
/*
template<class T>
class Stackmin
{
public:

	void Push(const T x)
	{
		_s1.push(x);
		if (mins.empty() || x <= mins.top()) //必须写等于号，防止删除过一次。
		{
			mins.push(x);
		}
	}

	void Pop()
	{
		if (mins.top() == _s1.top())
		{
			mins.pop();
		}
		_s1.pop();
	}

	T Min()
	{
		if (!mins.empty())
		{
			return mins.top();
		}
	}

private:
	stack<T> _s1;
	stack<T> mins;
};

int main ()
{
	Stackmin<int> s1; 
    s1.Push (5);  
    s1.Push (4);  
    s1.Push (3);  
    s1.Push (6);  
    s1.Push (0);  
	s1.Push(10);
	s1.Push(1);
	cout<<s1.Min()<<endl;
	return 0;
}
*/
/*
//2. 使用两个栈实现一个队列
template<class T>
class TS_Q
{
public:
	void Push(const T& x)
	{
		s1.push(x);
	}

	void Pop()
	{
		if (s1.empty() && s2.empty())
		{
			throw new exception("queue is empty!");	
		}
		
		if (s2.empty())
		{
			while (!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
		}
		s2.pop();
	}

private:
	stack<T> s1;
	stack<T> s2;
};

int main()
{
	TS_Q<int> q1;
	//q1.Pop();
	q1.Push(1);
	q1.Push(1);
	q1.Push(1);
	q1.Push(1);
	q1.Pop();
	q1.Push(1);
	q1.Push(1);
	return 0;
}
*/
/*
//3. 使用两个队列实现一个栈
template <class T>
class TQ_S
{
public:
	void Push(const T& x)
	{
		if (q1.empty() && q2.empty())
		{
			q1.push(x);
		}
		else if (!q1.empty())
		{
			q1.push(x);
		}
		else 
		{
			q2.push(x);
		}
	}

	void Pop()
	{
		if (q1.empty() && q2.empty())
		{
			throw new exception("stack is empty!");
		}

		if (!q1.empty())
		{
			while (q1.size() != 1)
			{
				q2.push(q1.front());
				q1.pop();
			}
			q1.pop();
		}
		else
		{
			while (q2.size() != 1)
			{
				q1.push(q2.front());
				q2.pop();
			}
			q2.pop();
		}
	}

private:
	queue<T> q1;
	queue<T> q2;
};

int main()
{
	TQ_S<int> s;
	s.Push(1);
	s.Pop();
	s.Pop();  //想要检测返回可以更改Pop的返回类型
	return 0;
}
*/


//4. 元素出栈、入栈顺序的合法性。如入栈的序列（1,2,3,4,5），出栈序列为（4,5,3,2,1）
bool IsPopOrder(vector<int> PushV, vector<int> PopV)
{
	if (PushV.size() != PopV.size() || PushV.size <= 0)
	{
		return false;
	}

	int len = PushV.size();
	int indexPop = 0;
	stack<int> s;
	for (int i = 0; i<len && indexPop < len; ++i)
	{
		s.push(PushV[i]);
		//1，入栈顶元素等于出栈顺序开始的元素，将入栈顶元素移除，
		//并且将出栈偏移到下一个元素
		//2，如果偏移后，栈顶的元素还等于出栈顺序中的元素，继续pop入栈表
		//3,入栈序列栈顶元素与当前出栈序列元素不相等，不合法
		while (!s.empty() && s.top() == PopV[indexPop])
		{
			s.pop();
			indexPop++;
		}
	}
	return (s.empty())?true:false;
}
