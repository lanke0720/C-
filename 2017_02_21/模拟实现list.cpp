#pragma once

#include <iostream>
using namespace std;
#include <assert.h>

template <class T>
struct __ListNode
{
	__ListNode<T>* _next;
	__ListNode<T>* _prev;

	T _data;

	__ListNode(const T& x)
		:_data(x)
		,_next(NULL)
		,_prev(NULL)
	{}
};

template<class T, class Ref, class Ptr>
struct __ListIterator
{
	typedef __ListNode<T> Node;
	typedef __ListIterator<T, Ref, Ptr> Self;

	Node* _node;

	__ListIterator(){}

	__ListIterator(Node* node)
		:_node(node)
	{}

	bool operator != (const Self& s)
	{
		return _node != s._node;
	}

	bool operator == (const Self& s)
	{
		return _node == s._node;
	}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	Self& operator++() //front
	{
		_node = _node->_next;
		return *this;
	}

	Self operator++(int) //later
	{
		Self temp(*this);

		_node = _node->_next;
		return temp;
	}

	Self& operator--() //front
	{
		_node = _node->prev;
		return *this;
	}

	Self operator--(int) //later
	{
		Self temp(*this);

		_node = _node->prev;
		return temp;
	}


};

template<class T>
class List
{
	typedef __ListNode<T> Node;

public:

	typedef __ListIterator<T, T&, T*> Iterator;
	typedef __ListIterator<T,const T&, const T*> ConstIterator;

	Node* BuyNode(const T& x)
	{
		return new Node(x);
	}

	List()
		:_head(BuyNode(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	void PushBack(const T& x)
	{
		Insert(End(),x);
	}

	void PopBack()
	{
		Erase(--End(),x);
	}

	void PushFront(const T& x)
	{
		Insert(Begin(), x);
	}

	void PopFront()
	{
		Erase(Begin());
	}

	template <class InputIterator>
	void Insert(Iterator pos, InputIterator first, InputIterator last)
	{
		while (first != last)
		{
			Insert(pos, *first);
			++first;
		}
	}

	void Insert(Iterator pos, const T& x)
	{
		assert(pos._node);

		Node* cur = pos._node;
		Node* prev = cur->_prev;

		Node* temp = new Node(x);

		prev->_next = temp;
		temp->_prev = prev;

		temp->_next = cur;
		cur ->_prev = temp;

		//return temp;
	}

	Iterator Erase(Iterator pos)
	{
		assert(pos._node && pos._node != _head);

		Node* prev = pos._node->_prev;
		Node* next = pos._node->_next;

		prev->_next = next;
		next->_perv = prev;

		delete pos._node;

		return Iterator(next);
	}

	Iterator Begin()
	{
		return _head->_next;
	}

	Iterator End()
	{
		return _head;
	}

	ConstIterator Begin() const
	{
		return _head->_next; 
	}

	ConstIterator End() const
	{
		return _head;
	}

protected:

	Node* _head;
};

void PrintList(const List<int>& l)
{
	List<int>::ConstIterator it = l.Begin();

	while (it != l.End())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

