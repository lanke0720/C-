#include<iostream>
using namespace std;
namespace NewSpace
{
	int iValue = 10;
}

int iValue = 20;

class CTest
{
public:
	void FunTest(int iValue1)
	{
		iValue = iValue;
	}

	void Print()
	{
		cout<<iValue<<endl;
	}
private:
	int _iValue;
};


int main()
{
	CTest test;
	test.FunTest(30);
	cout<<iValue<<endl;
	cout<<NewSpace::iValue<<endl;
	test.Print();
	system( "pause");
	return 0;
}
