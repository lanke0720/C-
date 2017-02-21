#pragma once

//namespace THREAD
//{
//}
enum PointerTag {THREAD, LINK};

template<class T>
struct BinaryTreeNodeThd
{
	T _data;
	BinaryTreeNodeThd<T>* _left;
	BinaryTreeNodeThd<T>* _right;
	BinaryTreeNodeThd<T>* _parent;
	
	PointerTag _leftTag;
	PointerTag _rightTag;

	BinaryTreeNodeThd(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
};


template<class T, class Ref, class Ptr>
struct BinaryTreeIterator
{
	typedef BinaryTreeNodeThd<T> Node;
	typedef BinaryTreeIterator<T, Ref, Ptr> Self;

	Node* _node;

	BinaryTreeIterator(Node* node)
		:_node(node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &(operator*());
	}

	Self& operator++()
	{
		_node = _Next(_node);
		return *this;
	}

	Self operator++(int)
	{
		Self tmp(*this);
		_node = _Next(_node);
		return tmp;
	}

	bool operator != (const Self& s) const
	{
		return _node != s._node;
	}

protected:
	// _Inc
	Node* _Next(Node* node)
	{
		if (node->_rightTag == THREAD)
		{
			return node->_right;
		}
		else
		{
			Node* cur = node->_right;
			while (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}

			return cur;
		}
	}

	Node* _Prev(Node* node)
	{
		if (node->_leftTag == THREAD)
		{
			return node->_left;
		}
		else
		{
			Node* cur = node;
			while (cur->_rightTag == LINK)
			{
				cur = cur->_right;
			}

			return cur;
		}
	}
};

template<class T>
class BinaryTreeThd
{
	typedef BinaryTreeNodeThd<T> Node;
public:
	typedef BinaryTreeIterator<T, T&, T*> Iterator;
	typedef BinaryTreeIterator<T, const T&, const T*> ConstIterator;

	Iterator Begin()
	{
		Node* cur = _root;
		while (cur->_leftTag == LINK)
		{
			cur = cur->_left;
		}
		return Iterator(cur);
	}

	Iterator End()
	{
		return NULL;
	}

	BinaryTreeThd(T* a, size_t n, const T& invalid)
	{
		assert(a);
		size_t index = 0;
		_root = _CreateTree(a, n, index, invalid);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root, prev);
		if (prev && prev->_right == NULL)
			prev->_rightTag = THREAD;
	}

	void PrevOrderThreading()
	{
		Node* prev = NULL;
		_PrevOrderThreading(_root, prev);
	}

	void PrevOrderThd()
	{
		Node* cur = _root;
		while (cur)
		{
			while(cur->_leftTag == LINK)
			{
				cout<<cur->_data<<" ";
				cur = cur->_left;
			}
			cout<<cur->_data<<" ";

			cur = cur->_right;

		/*	while(cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout<<cur->_data<<" ";
			}
			
			if (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}*/
		}
		cout<<endl;
	}

	//void InOrderThd()
	//{
	//	Node* cur = _root;
	//	while (cur)
	//	{
	//		// 找最左节点
	//		while (cur->_leftTag == LINK)
	//		{
	//			cur = cur->_left;
	//		}
	//		cout<<cur->_data<<" ";
	//		
	//		// 后继则直接访问
	//		while (cur && cur->_rightTag == THREAD)
	//		{
	//			cur = cur->_right;
	//			if(cur)
	//				cout<<cur->_data<<" ";
	//		}

	//		// 子问题 右是子树，子问题处理
	//		// cur->_rightTag == LINK
	//		if(cur)
	//			cur = cur->_right;
	//	}
	//	cout<<endl;
	//}

	void InOrderThd()
	{
		Node* cur = _root;
		while (cur && cur->_leftTag == LINK)
		{
			cur = cur->_left;
		}

		while (cur)
		{
			cout<<cur->_data<<" ";
			cur = InOrderNext(cur);
		}
		cout<<endl;
	}

	Node* InOrderNext(Node* node)
	{
		if (node->_rightTag == THREAD)
		{
			return node->_right;
		}
		else
		{
			Node* cur = node->_right;
			while (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}

			return cur;
		}
	}

protected:
	void _PrevOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
			return ;
		
		if (cur->_left == NULL)
		{
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}

		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}

		prev = cur;

		if (cur->_leftTag == LINK)
			_PrevOrderThreading(cur->_left, prev);

		if (cur->_rightTag == LINK)
			_PrevOrderThreading(cur->_right, prev);
	}
	
	void _InOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
			return;

		_InOrderThreading(cur->_left, prev);

		if (cur->_left == NULL)
		{
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}

		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}

		prev = cur;


		_InOrderThreading(cur->_right, prev);
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		if(root->_leftTag == LINK)
			_InOrder(root->_left);

		cout<<root->_data<<" ";

		if (root->_rightTag == LINK)
			_InOrder(root->_right);
	}

	Node* _CreateTree(T* a, size_t n, size_t& index, const T& invalid)
	{
		Node* root = NULL;
		if (index < n && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreateTree(a, n, ++index, invalid);
			if (root->_left)
				root->_left->_parent = root;

			root->_right = _CreateTree(a, n, ++index, invalid);
			if (root->_right)
				root->_right->_parent = root;
		}

		return root;
	}
protected:
	Node* _root;
};

void TestBinaryTreeThd()
{
	int a[10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	BinaryTreeThd<int> t1(a, sizeof(a)/sizeof(a[0]), '#');
	t1.InOrderThreading();
	t1.InOrder();
	t1.InOrderThd();
	BinaryTreeThd<int>::Iterator it = t1.Begin();
	while (it != t1.End())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

	BinaryTreeThd<int> t2(a, sizeof(a)/sizeof(a[0]), '#');
	t2.PrevOrderThreading();
	t2.PrevOrderThd();

	int a1[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8}; 
	BinaryTreeThd<int> t3(a1, sizeof(a1)/sizeof(a1[0]), '#');
	//t3.InOrderThreading();
	//t3.InOrderThd();
	t3.PrevOrderThreading();
	t3.PrevOrderThd();
}