#pragma once 

#include <assert.h>
#include <queue>
#include <stack>
using namespace std;

template <class T>
struct BinaryTreeNode               //�������Ľ��
{
	T _data;                       //�ȶ�����Ҫ����������  ���ݣ���������������
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const T& x)      //���캯��
		:_data(x) 
		,_left(NULL)
		,_right(NULL)
	{}
};

template <class T>
class BinaryTree                    //����������           
{
	typedef BinaryTreeNode<T> Node;
public:

	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(int* a, size_t size, const T& invalid = T())  //���ǵ���T���͵�Ĭ�Ϲ��캯��������˵��������0 �ַ������ǿ��ַ���
	{
		assert(a);
		size_t index = 0;
		_root = CreatTree(a, size, invalid, index);
	}

	BinaryTree(BinaryTree<T>& t)                              //��������
	{
		_root = _Copy(t._root);                               //ע��˴��Ŀ������ǿ���Root 
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

	BinaryTree<T> operator=(BinaryTree<T> t)  //��������������βεĽ���
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

	Node* _Copy(Node* root)             //�ݹ���� ����
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
	//����
	void _Size(Node* root, size_t& count)
	{
		if(root == NULL)
			return ;

		count++;
		_Size(root->_left, count);
		_Size(root->_right,count);
	}
	*/
	
	//������
	size_t _Size(Node* root)
	{
		if(root == NULL)
			return 0;

		return _Size(root->_left) + _Size(root->_right) +1;  //+1 ��Ϊ�и�
	}

	//�ǵݹ鷨
	void _PrecOrderNoR(Node* root)
	{
		stack<Node*> s;
		Node* cur = root;
		while(!s.empty() || cur)
		{
			//ǰ�� ���������ڵ�ֱ�ӷ��ʲ�ѹ��ջ  ������
			while(cur)
			{
				cout<<cur->_data<<" ";
				s.push(cur);                    
				cur = cur ->_left;
			}
			//��ջ��ȡ��һ���ڵ㣬��ʾ����ڵ���������Ѿ����ʹ���
			Node* top = s.top();
			s.pop(); 
			//�����ⷽʽ����
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

	void _PosOrderNoR(Node* root)  //������Ļ����ϸ���Ϊ�ȷ��������� ���Ҳ�pop
	{
		stack<Node*> s;
		Node* cur = root;
		Node* prev = NULL;   //������һ��pre�ı�־
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
				prev = top;   //ָ��һ���ոշ��ʹ��Ľڵ�
				s.pop();
			}
			else          //����շ��ʹ��Ľ����������������������Ϊ��
			{             //�򲻷�������������ǰջ�������Է��ʲ���POP
				cur = top->_right;  //�����ȷ������������ٷ��ʵ�ǰ���
			}
		}
	}


	//�ݹ鷨
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

	void _LevelOrder(Node* root) //�������
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
