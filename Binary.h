#pragma once 

#include <assert.h>
#include <queue>
#include <stack>
using namespace std;

template <class T>
struct BinaryTreeNode               //二叉树的结点
{
	T _data;                       //先定义重要的三个隐身  数据，左子树，右子树
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const T& x)      //构造函数
		:_data(x) 
		,_left(NULL)
		,_right(NULL)
	{}
};

template <class T>
class BinaryTree                    //建立二叉树           
{
	typedef BinaryTreeNode<T> Node;
public:

	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(int* a, size_t size, const T& invalid = T())  //就是调用T类型的默认构造函数，比如说整数就是0 字符串就是空字符串
	{
		assert(a);
		size_t index = 0;
		_root = CreatTree(a, size, invalid, index);
	}

	BinaryTree(BinaryTree<T>& t)                              //拷贝构造
	{
		_root = _Copy(t._root);                               //注意此处的拷贝，是拷贝Root 
	}
	//BinaryTree<T>& operator=(BinaryTree<T>& t)
	//{
	//	if(*this = &t)
	//	{
	//		Node* temp = _Copy(t._root);
	//		_Destroy(_root);
	//		_root = temp;
	//	}
	//	return *this;
	//}

	BinaryTree<T> operator=(BinaryTree<T> t)  //简便做法，两个形参的交换
	{
		swap(t._root,_root);
		return *this;
	}

	~BinaryTree()
	{
		_Destroy(_root);
	}
	
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

	void PrecOrderNoR()
	{
		_PrecOrderNoR(_root);
		cout<<endl;
	}
	void InOrderNoR()
	{
		_InOrderNoR(_root);
		cout<<endl;
	}
	void PosOrderNoR()
	{
		_PosOrderNoR(_root);
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
	void GetLeafSize()      
	{
		_GetLeafSize(_root);
		cout<<endl;
	}
	void GetKLeaveSize(size_t k)
	{
		cout<<_GetKLeaveSize(_root,k);
		cout<<endl;
	}

protected:
	size_t _GetKLeaveSize(Node* root, size_t k)
	{
		if (root == NULL)
			return 0;

		if (k == 1)
			return 1;
		else if (root->_left != NULL || root->_right != NULL)
		{
			return _GetKLeaveSize(root->_left, k-1) + _GetKLeaveSize(root->_right, k-1);
		}
		return 0;
	}

	size_t _GetLeafSize(Node* root)
	{
		if(root == NULL)
			return 0;

		if(root->_left == NULL && root->_right == NULL)
			return 1;

		return _GetLeafSize(root->_left) + _GetLeafSize(root->_right);
	}

	void _Destroy(Node* root)
	{
		if(root != NULL)
		{
			if(root->_left != NULL)
			{
				_Destroy(root->_left);
			}
			if(root->_right != NULL)
			{
				_Destroy(root->_right);
			}
			delete root;
			root = NULL;
		}
	}

	Node* _Copy(Node* root)             //递归逐层 拷贝
	{
		if(NULL == root)
		{
			return NULL;
		}
		
		Node* temp = new Node(root->_data); 
		
		temp->_left = _Copy(root->_left);
		temp->_right = _Copy(root->_right);

		return temp;
	}

	size_t _Depth(Node* root)
	{
		if(root == NULL)
			return 0;

		int leftdepth = _Depth(root->_left) + 1;
		int rightdepth = _Depth(root->_right) + 1;

		return leftdepth > right ? leftdepth : right ;
	}
	/*
	//遍历
	void _Size(Node* root, size_t& count)
	{
		if(root == NULL)
			return ;

		count++;
		_Size(root->_left, count);
		_Size(root->_right,count);
	}
	*/
	
	//子问题
	size_t _Size(Node* root)
	{
		if(root == NULL)
			return 0;

		return _Size(root->_left) + _Size(root->_right) +1;  //+1 因为有根
	}

	//非递归法
	void _PrecOrderNoR(Node* root)
	{
		stack<Node*> s;
		Node* cur = root;
		while(!s.empty() || cur)
		{
			//前序： 遇到树根节点直接访问并压入栈  向左走
			while(cur)
			{
				cout<<cur->_data<<" ";
				s.push(cur);                    
				cur = cur ->_left;
			}
			//从栈里取出一个节点，表示这个节点和左子树已经访问过了
			Node* top = s.top();
			s.pop(); 
			//子问题方式访问
			cur = top->_right; 
		}
	}

	void _InOrderNoR(Node* root)
	{
		stack<Node*> s;
		Node* cur = root;
		while (!s.empty() || cur)
		{
			while(cur)
			{
				s.push(cur);
				cur = cur ->_left;
			}
			Node* top = s.top();
			cout<< top->_data <<" ";
			s.pop();
			cur = top->_right;
		}
	}

	void _PosOrderNoR(Node* root)  //在中序的基础上更改为先访问右子树 并且不pop
	{
		stack<Node*> s;
		Node* cur = root;
		Node* prev = NULL;   //再增加一个pre的标志
		while(!s.empty() || cur)
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			if(top->_right == NULL || top->_right == prev)
			{
				cout<<top->_data<<" ";
				prev = top;   //指向一个刚刚访问过的节点
				s.pop();
			}
			else          //如果刚访问过的结点是右子树，或者右子树为空
			{             //则不访问右子树，当前栈顶结点可以访问并且POP
				cur = top->_right;  //否则先访问右子树，再访问当前结点
			}
		}
	}


	//递归法
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

	void _LevelOrder(Node* root) //层序遍历
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

	Node* CreatTree(int* a, size_t size, T invalid, size_t& index)  //index "&"
	{
		Node* root = NULL;

		if (index < size && invalid != a[index])
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


void TestBinary()
{
	int a[10] = {1, 2, 3,'#','#', 4 ,'#','#',5 ,6};
	BinaryTree<int> t1(a, sizeof(a)/sizeof(a[0]), '#');


	BinaryTree<int> t2(t1);

	BinaryTree<int> t3;
	t3 = t2;

	t1.Size();
	t1.PrecOrder();
	t1.PosOrder();
	t1.InOrder();
	t1.LevelOrder();


	t3.Size();
	t3.PrecOrderNoR();
	t3.PosOrderNoR();
	t3.InOrderNoR();
	t3.LevelOrder();

	t3.GetKLeaveSize(3);
}
