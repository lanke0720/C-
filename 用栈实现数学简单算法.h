#include <iostream>
using namespace std;

#include <stack>
#include <assert.h>

enum Type
{
	OP_SYMBOL,
	OP_NUM,
	ADD,
	SUB,
	MUL,
	DIV,
};

struct Cell
{
	Type _type;
	int _value;
};

int CountPRN(Cell* rpn, size_t n)
{
	assert(rpn);
	stack<int> s;
	for(size_t i = 0 ;i < n ; ++i)
	{
		if(rpn[i]._type == OP_NUM)
		{
			s.push(rpn[i]._value);
		}
		else if(rpn[i]._type == OP_SYMBOL)
		{
			int right = s.top();
			s.pop();
			int left = s.top();
			s.pop();
			switch(rpn[i]._value)
			{
			case ADD:
				s.push(left + right);
				break;
			case SUB:
				s.push(left - right);
				break;
			case MUL:
				s.push(left * right);
				break;
			case DIV:
				s.push(left / right);
				break;
			default:
				assert(false);
			}
		}
	}
		return s.top();
}
void TestRPN()
{
	Cell RPN[] = {
		{OP_NUM,12},
		{OP_NUM,3},
		{OP_SYMBOL,DIV}
	};
	cout<<CountPRN(RPN,sizeof(RPN)/sizeof(RPN[0]));
}

int main ()
{
	TestRPN();
	return 0;
}