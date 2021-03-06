#pragma once

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K,V>* _left;
	AVLTreeNode<K,V>* _right;
	AVLTreeNode<K,V>* _parent;

	K _key;
	V _value;

	int _bf;		// 平衡因子

	AVLTreeNode(const K& key, const V& value)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_key(key)
		,_value(value)
		,_bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
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

		//更新平衡因子
		while(parent)
		{
			if (parent->_left == cur)
				parent->_bf -= 1;
			else
				parent->_bf += 1;

			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1 
				|| parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;
				//continue;
			}
			else if (parent->_bf == 2 
				|| parent->_bf == -2)
			{
				// 旋转平衡处理
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						RotateL(parent);
					}
					else // -1
					{
						RotateRL(parent);
					}
				}
				else // -2
				{
					if (cur->_bf == -1)
					{
						RotateR(parent);
					}
					else // 1
					{
						RotateLR(parent);
					}
				}

				break;
			}
			else
			{
				cout<<"平衡因子异常"<<endl;
				assert(false);
			}
		}

		return true;
	}

	// 1.时间复杂度是多少？ O(N) O(N*lgN) O(N*N)优化 
	// 2.AVLTree
	bool IsBalance()
	{
		return _IsBalance(_root);
	}

	size_t _Depth(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		size_t leftHeight = _Depth(root->_left);
		size_t rightHeight = _Depth(root->_right);

		return leftHeight > rightHeight ? leftHeight+1 : rightHeight+1;
	}

	bool _IsBalance(Node* root)
	{
		if (root == NULL)
			return true;

		size_t leftD = _Depth(root->_left);
		size_t rightD = _Depth(root->_right);

		if((rightD-leftD) != root->_bf)
		{
			cout<<"平衡因子异常："<<root->_key<<endl;
			//return false;
		}

		return abs(rightD-leftD) <= 1
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
	}

	bool IsBalanceOP()
	{
		size_t depth = 0;
		return _IsBalanceOP(_root, depth);
	}

	bool _IsBalanceOP(Node* root, size_t& depth)
	{
		if (root == NULL)
		{
			depth = 0;
			return true;
		}

		size_t leftDepth, rightDepth;
		if(_IsBalanceOP(root->_left, leftDepth)
			&& _IsBalanceOP(root->_right, rightDepth))
		{
			depth = leftDepth > rightDepth ? leftDepth+1:rightDepth+1;
			return abs(leftDepth-rightDepth) < 2;
		}
		else
		{
			return false;
		}
	}


	Node* Find(const K& key);
	bool Remove(const K& key);

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
			if (parent == ppNode->_left)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}

		subR->_bf = parent->_bf = 0;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;
		Node* ppNode = parent->_parent;
		//subL->_parent = parent->_parent;
		parent->_parent = subL;
		
		if (parent == _root)
		{
			_root = subL;
			_root->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}

		parent->_bf = subL->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		if (bf == 1)
		{
			subL->_bf = -1;
			parent->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
		}
		else
		{
			parent->_bf = subL->_bf = 0;
		}

		subLR->_bf = 0;
	}

	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		// 更新平衡因子
		if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if(bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else //0
		{
			subR->_bf = parent->_bf = 0;
		}

		subRL->_bf = 0;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return ;
		}

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);

	}

private:
	Node* _root;
};


void TestAVLTree1()
{
	AVLTree<int, int> t1;
	int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
	{
		t1.Insert(a[i], i);
	}
	t1.InOrder();

	cout<<"IsBalance:"<<t1.IsBalance()<<endl;

	// ???
	AVLTree<int, int> t2;
	int a1[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	for (size_t i = 0; i < sizeof(a1)/sizeof(a1[0]); ++i)
	{
		t2.Insert(a1[i], i);
		cout<<a1[i]<<" IsBalance:"<<t2.IsBalance()<<endl;
	}
	t2.InOrder();

	cout<<"IsBalance:"<<t2.IsBalance()<<endl;
}
