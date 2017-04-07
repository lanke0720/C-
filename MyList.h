#pragma once

#include "Allocator.h"
#include "Construct.h"
#include "Iterator.h"

template<class T>
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

	// 内嵌定义的五种型别
	typedef BidirectionalIteratorTag IteratorCategory;
	typedef T                  ValueType;
	typedef size_t			   DifferenceType;
	typedef Ptr                Pointer;
	typedef Ref                Reference;


	Node* _node;

	__ListIterator(Node* node = NULL)
		:_node(node)
	{}

	inline Ref operator*()
	{
		return _node->_data;
	}

	inline Ptr operator->()
	{
		//return &_node->_data;
		return &(operator*());
	}

	Self& operator++()
	{
		_node = _node->_next;
		return *this;
	}

	Self operator++(int);
	Self operator--();
	Self operator--(int);

	bool operator != (const Self& s) const
	{
		return _node != s._node;
	}

	bool operator == (const Self& s) const
	{
		return _node == s._node;
	}
};

// 扩展性
template<class T, class Alloc = alloc>
class List
{
	typedef __ListNode<T> Node;
	typedef SimpleAlloc<Node, Alloc> DataAllocator;
public:
	typedef __ListIterator<T, T&, T*> Iterator;
	typedef __ListIterator<T, const T&, const T*> ConstIterator;

	List()
	{
		_head = _BuyNode(T());
		_head->_next = _head;
		_head->_prev = _head;
	}

	~List()
	{
		Clear();

		DestoryNode(_head);
		_head = NULL;
	}

	void Clear()
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			Node* del = cur;
			cur = cur->_next;
			DestoryNode(del);
		}
	}

	void PushBack(const T& x)
	{
		Node* tmp = _BuyNode(x);
		Node* tail = _head->_prev;

		tail->_next = tmp;
		tmp->_prev = tail;

		_head->_prev = tmp;
		tmp->_next = _head;
	}

	void Insert(Iterator pos, const T& data);
	void Erase(Iterator pos);

	Iterator Begin()
	{
		//return Iterator(_head->_next);
		return _head->_next;
	}

	Iterator End()
	{
		//return Iterator(_head->_next);
		return _head;
	}


protected:
	Node* _BuyNode(const T& x)
	{
		Node* node = DataAllocator::Allocate();
		//new(node)Node(x);
		Construct(node, x);
		return node;
	}

	void DestoryNode(Node* p)
	{
		//p->~Node();
		Destroy(p);
		DataAllocator::Deallocate(p);
	}

protected:
	Node* _head;
};


void TestList()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);

	List<int>::Iterator it = l.Begin();
	while(it != l.End())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

	cout<<"List:"<<Distance(l.Begin(), l.End())<<endl;
}