#pragma once
#include <iostream>
using namespace std;

template<class K, class V>
struct SearchBinaryTreeNode                  //搜索树的结点
{
	SearchBinaryTreeNode<K, V>* _left;
	SearchBinaryTreeNode<K, V>* _right;

	K _key;
	V _value;

	SearchBinaryTreeNode(const K& k, const V& v)
		:_left(NULL)
		,_right(NULL)
		,_key(k)
		,_value(v)
	{}
};


//SBTree
template<class K, class V>
class SearchBinaryTree                   //搜索二叉树类
{
	typedef SearchBinaryTreeNode<K, V> Node;     //写起来简便
public:

	SearchBinaryTree()  //构造函数
		:_root(NULL)
	{}

	~SearchBinaryTree() //析构
	{
		_Destroy(_root);
		_root = NULL;
	}

	bool RemoveR(const K& key)   //删除  递归R
	{
		return _RemoveR(_root, key);
	}

	bool Remove(const K& key)
	{
		if(NULL == _root)
			return false;

		Node* cur = _root;
		Node* parent = NULL;
		while(cur)
		{
			if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{                       //思路：让左右为空的情况考虑到又为空或者右为空里面
				Node* del = cur;
				if (cur->_left == NULL)     //1：如果当先结点的左子树为空
				{
					if (parent == NULL)         //1.1:在Top结点的情况
					{
						_root = cur->_right;
					}
					else                        //1.2 不在Top结点
					{
						if (parent->_left == cur)    //1.2.1  当前结点为父结点的左子树
						{
							parent->_left = cur->_right;      //左子树为空，所以只能连接右
						}
						else                         //1.2.2  当前结点为父结点的右子树
						{
							parent->_right = cur->_right;
						}
					}
				}
				else if (cur->_right == NULL)  // 2 如果当前结点的右子树为空
				{
					if (parent == NULL)        
					{
						_root = cur->_left;
					}
					else                    
					{
						if (parent->_left == cur)   
						{
							parent->_left = cur->_left;
						}
						else                       
						{
							parent->_right = cur->_left;
						}
					}
				}
				else                          // 3.左右都不为空的情况
				{
					//替换法删除
					parent = cur;
					Node* subLeft = cur->_right;  //找当前结点的右子树 右边的子树大
					while (subLeft->_left)        //遍历到subLeft的子树的最左结点
					{
						parent = subLeft;
						subLeft = subLeft->_left;
					}

					del = subLeft;                //既当前结点的右子树向下遍历的最左结点。有del替代

					cur->_key = subLeft->_key;
					if (parent->_left == subLeft)   
					{
						parent->_left = subLeft->_right;
					}
					else 
					{
						parent->_right = subLeft->_right;
					}
				}

				delete del;

				return true;
			}
		}
		return false;

	}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key,value);
			return true;
		}

		Node* cur = _root;
		Node* parent = NULL;
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
				return false;
		}

		if (parent->_key < key)
		{
			parent->_right = new Node(key,value);
		}
		else
		{
			parent->_left = new Node(key,value);
		}

		return true;
	}



	bool InsertR(const K& key, const V& value)
	{
		return _InsertR(_root, key, value);
	}
	bool Find (const K& key)
	{
		if(NULL == _root)
			return false;
		Node* cur = _root;
		while (cur)
		{
			if(cur->_key < key)
				cur = cur->_right;

			else if(cur->_key > key)
				cur = cur->_right;

			else 
				return true;
		}
		return false;
	}

	bool FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

protected:

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return ;

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}

	bool _RemoveR(Node*& root,const K& key)
	{
		if (NULL == root)
			return false;

		if (root->_key < key)
		{
			return _RemoveR(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _RemoveR(root->_left, key);
		}
		else 
		{
			Node* del = root;
			if (root->_left == NULL)    //同 非递归遍历一样思路
			{
				root = root->_right;
			}
			else if(root->_right == NULL)
			{
				root = root->_left;
			}
			else
			{
				Node* parent = root;
				Node* subLeft = root->_right;
				while (subLeft->_left)
				{
					parent = subLeft;
					subLeft = subLeft->_left;
				}

				root->_key = subLeft->_key;
				del = subLeft;

				if (parent->_left == subLeft)
					parent->_left = subLeft->_right;
				else
					parent->_right = subLeft->_right;
			}

			delete del;
			return true;
		}

	}

	bool _FindR(Node* _root , const K& key)
	{
		if(NULL == root)
			return false;

		if(root->_key == key)
			return true;
		else if (root->_key < key)
			_FindR(_root->_right ,key);
		else if (root->_key > key)
			_FindR(_root->_left,key);
	}

	bool _InsertR(Node*& root, const K& key, const V& value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}
		
		if (root->_key < key)
		{
			return _InsertR(root->_right, key, value);
		}
		else if (root->_key > key)
		{
			return _InsertR(root->_left, key, value);
		}
		else
		{
			return false;
		}
	}

	void _Destroy(Node*& root)
	{
		if(root)
		{
			_Destroy(root->_left);
			_Destroy(root->_right);
			delete root;
		}
		else
			return;
	}
protected:
	Node* _root;
};

void TestSearch()
{
	int a[] = {5,3,4,1,7,8,2,6,0,9};
	SearchBinaryTree<int, size_t> t1;

	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
	{
		t1.InsertR(a[i], 1);
	}

	t1.InOrder();

    t1.Remove(9);
	t1.RemoveR(9);

	t1.InOrder();
}