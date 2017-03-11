#pragma once

template<class K, class V>
struct SearchBinaryTreeNode
{
	SearchBinaryTreeNode<K, V>* _left;
	SearchBinaryTreeNode<K, V>* _right;

	const K _key; 
	V _value;

	SearchBinaryTreeNode(const K& k, const V& v)
		:_left(NULL)
		,_right(NULL)
		,_key(k)
		,_value(v)
	{}
};

// BSTree
template<class K, class V>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<K, V> Node;
public:
	SearchBinaryTree()
		:_root(NULL)
	{}

	~SearchBinaryTree()
	{
		Destory(_root);
		//_root = NULL;
	}
	
	void Destory(Node*& root)
	{
		if(root == NULL)
			return;

		Destory(root->_left);
		Destory(root->_right);

		delete root;
		root = NULL;
	}

	bool InsertR(const K& key, const V& value)
	{
		return _InsertR(_root, key, value);
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

	bool RemoveR(const K& key)
	{
		return _RemoveR(_root, key);
	}
	
	bool _RemoveR(Node*& root, const K& key)
	{
		if (root == NULL)
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
			if (root->_left == NULL)
			{
				root = root->_right;
			}
			else if (root->_right == NULL)
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

	
	Node* FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	Node* _FindR(Node* root, const K& key)
	{
		if (root == NULL)
		{
			return NULL;
		}
			
		if (key > root->_key)
		{
			return  _FindR(root->_right, key);
		}
		else if(key < root->_key)
		{
			return _FindR(root->_left, key);
		}
		else
		{
			return root;
		}
	}

	/*bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node(key);
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
			{
				return false;
			}
		}

		if (parent->_key < key)
		{
			parent->_right = new Node(key);
		}
		else
		{
			parent->_left = new Node(key);
		}

		return true;
	}*/

	bool Remove(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;
		while(cur)
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
				Node* del = cur;
				if (cur->_left == NULL)
				{
					if(parent == NULL)
					{
						_root = cur->_right;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
					}
					
				}
				else if (cur->_right == NULL)
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
				else
				{
					// 替换法删除
					parent = cur;
					Node* subLeft = cur->_right;
					while (subLeft->_left)
					{
						parent = subLeft;
						subLeft = subLeft->_left;
					}

					del = subLeft;
					
					cur->_key = subLeft->_key;
					if(parent->_left == subLeft)
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

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur= cur->_left;
			}
			else
			{
				return cur;
			}
		}

		return NULL;
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
			return;
		}

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}

protected:
	Node* _root;
};

//void TestBSTree()
//{
//	int a[] = {5,3,4,1,7,8,2,6,0,9};
//	SearchBinaryTree<int> t1;
//	
//	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
//	{
//		t1.InsertR(a[i]);
//	}
//
//	t1.InOrder();
//
//	// 白盒 黑盒
//	// UT
//	t1.RemoveR(2);
//	t1.RemoveR(1);
//	t1.RemoveR(8);
//	t1.RemoveR(5);
//
//	t1.InOrder();
//
//
//	// 崩溃了？why
//	t1.RemoveR(0);
//	t1.RemoveR(1);
//	t1.RemoveR(2);
//	t1.RemoveR(3);
//	t1.RemoveR(4);
//	t1.RemoveR(5);
//	t1.RemoveR(6);
//	t1.RemoveR(7);
//	t1.RemoveR(8);
//	t1.RemoveR(9);
//
//	t1.InOrder();
//}

#include<string>

void TestBSTreeAP()
{
	//SearchBinaryTree<string> dictSet;
	// dict
	//dictSet.Insert("string");
	//dictSet.Insert("move");
		
	SearchBinaryTree<string, string> dict;
	dict.InsertR("字符串", "string");
	dict.InsertR("左", "left");
	dict.InsertR("剩余", "left");

	string strs[] = {"苹果", "橘子", "西瓜", "苹果", "苹果"};
	SearchBinaryTree<string, size_t> countTree;
	for (size_t i = 0; i < sizeof(strs)/sizeof(string); ++i)
	{
		SearchBinaryTreeNode<string, size_t>* ret = countTree.Find(strs[i]);
		if (ret == NULL)
		{
			countTree.InsertR(strs[i], 1);
		}
		else
		{
			ret->_value++;
		}
	}
}

// K  key
// K/V key/value

// 1.怎么判断一个单词拼写是否正确 remove move mo
// 2.怎么实现一个中->英字典
// 3.cvte -- 统计水果出现出现次数
// 文本  苹果 西瓜 西瓜 西瓜 芒果 菠萝
// 香蕉 香蕉 香蕉 苹果 香蕉 香蕉 香蕉 香蕉 