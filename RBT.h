#pragma once

#include <iostream>
using namespace std;

enum Colour
{
	RED,
	BLACK,
};

template<class K, class V>
struct RBTNode
{
	K _key;
	V _value;
	Colour _col;

	RBTNode<K, V>* _left;
	RBTNode<K, V>* _right;
	RBTNode<K, V>* _parent;

	RBTNode(const K& key, const V& value)
		:_key(key)
		,_value(value)
		,_col(RED)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
};

template <class K, class V>
class RBTree
{
	typedef RBTNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_col = BLACK;
			return true;
		}

		Node* cur = _root;
		Node* parent = NULL;
		while(cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(key, value);
		if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//1.
				if (uncle && uncle->_col == RED)
				{
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else // ((uncle == NULL) || (uncle && uncle->_col == BLACK))
				{
					if(parent->_right == cur)
					{
						RotateL(parent);
						swap(parent, cur);
					}
					RotateR(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
					break;
				}
			}
			else //(grandfather->_right == parent)
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)
				{
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else // uncle == NULL || uncle->_col == BLACK;
				{
					if (cur == parent->_left) 
					{
						RotateR(parent);
						swap(cur, parent);
					}
					RotateL(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
					break;
				}
			}
		}
		_root->_col = BLACK;

		return true;
	}

	bool IsBalance()
	{
		return _IsBalance(_root);
	}

	bool _IsBalance(Node* root)
	{
		if (root == NULL)
			return true;

		if (root && root->_col == RED)
			return false;
		
		size_t k = 0;
		Node* cur = _root;
		while (cur)
		{
			if(cur && cur->_col == BLACK)
			{
				++k;
			}
			cur = cur->_left;
		}
		size_t num = 0;

		return _CheckColour(_root) && _CheckBlackNum(_root, k, num);
	}

	bool _CheckColour(Node* root)
	{
		if (root == NULL)
			return true;

		if (root->_col == RED && root->_parent->_col == RED)
			return false;

		return _CheckColour(root->_left) && _CheckColour(root->_right);
	}

	bool _CheckBlackNum(Node* root,const size_t k, size_t num)
	{
		
		if (root == NULL)
			return true;

		if (root->_col == BLACK)
			++num;
		
		if (root->_left == NULL && root->_right == NULL && k != num)
			return false;

		return _CheckBlackNum(root->_left, k, num) && _CheckBlackNum(root->_right, k, num);

	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;          //先连接 SUBLR & parent
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;           //再连接 SUBL & parent中间把原本父亲的父亲结点写出来
		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (parent == _root)   // 如果以前的parent 为根结点
		{
			_root = subL;
			_root->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)   //最后连接 ppNode & subL
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}
		//parent->_bf = subL->_bf = 0;
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;

		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else //(ppNode->_right == parent)
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}
	}

	void InOrder()  
    {  
        _InOrder(_root);  
        cout<<endl;  
    }

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return ;
		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}


private:
	Node* _root;

};

void testRBT()
{
	RBTree<int, int> t1;
	int a[] = {5,1,3,4,7,6,8,9,2};
	for(size_t i = 0; i < (sizeof(a)/sizeof(a[0])); ++i)
	{
		t1.Insert(a[i], i);
		cout<<t1.IsBalance()<<endl;
	}
	//cout<<t1.IsBalance();

	
}