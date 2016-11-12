#include <iostream>
using namespace std;

template<typename T>
struct ElemType;

template<>
struct ElemType<int>
{
	typedef long Type;
};

template<typename T>
typename ElemType<T>::Type Add (int left,int right)
{
	typename ElemType<T>::Type a;
	cout<<typeid(a).name();
	return left+right;
}