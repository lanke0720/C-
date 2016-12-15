#pragma once 

#include <assert.h>
#include <queue>
using namespace std;

template <class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}
};

template <class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree(int* a, size_t size, const T& invalid = T())
	{
		assert(a);
		size_t index = 0;
		_root = CreatTree(a, size, invalid, index);
	}

	/*BinaryTree(Binary<T>& t);
	BinaryTree<T>& operator=(BinaryTree<T>& t);
	~BinaryTree();*/
	
	void PrecOrder()
	{
		_PrecOrder(_root);
		cout<<endl;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void PosOrder()
	{
		_PosOrder(_root);
		cout<<endl;
	}
	void LevelOrder()
	{
		_LevelOrder(_root);
		cout<<endl;
	}

	void Size()
	{
		_Size(_root);
		cout<<_Size(_root)<<endl;
	}
	void Depth()
	{
		_Depth(_root);
		cout<<endl;
	}
	size_t GetLeafSize();
	size_t GetKLeaveSize(size_t);

protected:

	size_t _Depth(Node* root)
	{
		if(root == NULL)
			return 0;

		int leftdepth = _Depth(root->_left) + 1;
		int rightdepth = _Depth(root->_right) + 1;

		return leftdepth > right ? leftdepth : right ;
	}

	size_t _Size(Node* root)
	{
		if(root == NULL)
			return 0;

		return _Size(root->_left) + _Size(root->_right) +1;
	}

	void _PrecOrder(Node* root)
	{
		if(root == NULL)
			return ; 

		cout<<root->_data<<" ";
		_PrecOrder(root->_left);
		_PrecOrder(root->_right);
	}
	void _InOrder(Node* root)  //left root right 
	{
		if(NULL == root)
			return ;
		
		_InOrder(root->_left);
		cout<<root->_data<< " ";
		_InOrder(root->_right);
	}

	void _PosOrder(Node* root)
	{
		if(NULL == root)
			return ;

		_PosOrder(root->_left);
		_PosOrder(root->_right);
		cout<<root->_data<<" ";
	}
	void _LevelOrder(Node* root)
	{
		queue<Node*> q;
		if(NULL != root)
		{
			q.push(root);
		}

		while(!q.empty())
		{
			Node* front = q.front();
			cout<<front->_data<<" ";
			q.pop();

			if(front->_left)
			{
				q.push(front->_left);
			}
			if(front->_right)
			{
				q.push(front->_right);
			}
		}
	}

	Node* CreatTree(int* a, size_t size, T invalid, size_t& index)
	{
		Node* root = NULL;

		if(index < size && invalid != a[index])
		{
			root = new Node(a[index]);
			root->_left = CreatTree(a, size, invalid, ++index);
			root->_right = CreatTree(a, size, invalid, ++index);
		}
		return root;
	}


protected:
	Node* _root;
};


void Test()
{
	int a[10] = {1, 2, 3,'#','#', 4 ,'#','#',5 ,6};
	BinaryTree<int> t1(a, sizeof(a)/sizeof(a[0]), '#');

	t1.Size();
	t1.PrecOrder();
	t1.PosOrder();
	t1.InOrder();
	t1.LevelOrder();
}
