#pragma once
#include <iostream>
using namespace std;

template<class K, class V>
struct SearchBinaryTreeNode                  //�������Ľ��
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
class SearchBinaryTree                   //������������
{
	typedef SearchBinaryTreeNode<K, V> Node;     //д�������
public:

	SearchBinaryTree()  //���캯��
		:_root(NULL)
	{}

	~SearchBinaryTree() //����
	{
		_Destroy(_root);
		_root = NULL;
	}

	bool RemoveR(const K& key)   //ɾ��  �ݹ�R
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
			{                       //˼·��������Ϊ�յ�������ǵ���Ϊ�ջ�����Ϊ������
				Node* del = cur;
				if (cur->_left == NULL)     //1��������Ƚ���������Ϊ��
				{
					if (parent == NULL)         //1.1:��Top�������
					{
						_root = cur->_right;
					}
					else                        //1.2 ����Top���
					{
						if (parent->_left == cur)    //1.2.1  ��ǰ���Ϊ������������
						{
							parent->_left = cur->_right;      //������Ϊ�գ�����ֻ��������
						}
						else                         //1.2.2  ��ǰ���Ϊ������������
						{
							parent->_right = cur->_right;
						}
					}
				}
				else if (cur->_right == NULL)  // 2 �����ǰ����������Ϊ��
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
				else                          // 3.���Ҷ���Ϊ�յ����
				{
					//�滻��ɾ��
					parent = cur;
					Node* subLeft = cur->_right;  //�ҵ�ǰ���������� �ұߵ�������
					while (subLeft->_left)        //������subLeft��������������
					{
						parent = subLeft;
						subLeft = subLeft->_left;
					}

					del = subLeft;                //�ȵ�ǰ�������������±����������㡣��del���

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
			if (root->_left == NULL)    //ͬ �ǵݹ����һ��˼·
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