#pragma once

template<class K, class V, size_t M = 3>
struct BTreeNode
{
	//pair<K, V> _kvs[M-1];	   // 值得数组
	//BTreeNode<K, V>* _subs[M]; // 子树的数组
	pair<K, V> _kvs[M];			 // 值得数组
	BTreeNode<K, V>* _subs[M+1]; // 子树的数组
	BTreeNode<K, V>* _parent;

	size_t _size;			   // kv的个数

	BTreeNode()
	{
		_parent = NULL;
		_size = 0;
		for (size_t i = 0; i < M+1; ++i)
		{
			_subs[i] = NULL;
		}
	}
};

template<class K, class V, size_t M = 3>
class BTree
{
	typedef BTreeNode<K, V, M> Node;
public:
	BTree()
		:_root(NULL)
	{}

	pair<Node*,int> Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			size_t i = 0;
			for (; i < cur->_size; )
			{
				if (cur->_kvs[i].first > key)
				{
					break;
				}
				else if (cur->_kvs[i].first == key)
				{
					return make_pair(cur, i);
				}
				else
				{
					++i;
				}
			}

			parent = cur;
			cur = cur->_subs[i];
		}

		return make_pair(parent, -1);
	}

	bool Insert(const pair<K, V>& kv)
	{
		if (_root == NULL)
		{
			_root = new Node;
			_root->_kvs[0] = kv;
			_root->_size = 1;

			return true;
		}

		pair<Node*, int> ret = Find(kv.first);
		if (ret.second != -1)
		{
			return false;
		}

		
		Node* cur = ret.first;
		pair<K, V> newKV = kv;
		Node* sub = NULL;

		while(1)
		{
			// 在cur节点插入newKV和sub
			_InsertKV(cur, newKV, sub);

			// 1.如果cur没满，则已经插入成功
			// 2.否则需要进行分裂
			if (cur->_size < M)
			{
				return true;
			}
			
			// 分裂
			size_t mid = M/2;
			Node* tmp = new Node;
			size_t j = 0;
			size_t i = mid+1;
			for (; i < cur->_size; ++i)
			{
				tmp->_kvs[j] = cur->_kvs[i];
				cur->_kvs[i] = pair<K, V>();

				tmp->_subs[j] = cur->_subs[i];
				if(cur->_subs[i])
					cur->_subs[i]->_parent = tmp;

				tmp->_size++;
				++j;
			}

			// 拷走最后一个右孩子
			tmp->_subs[j] = cur->_subs[i];
			if(cur->_subs[i])
				cur->_subs[i]->_parent = tmp;

			cur->_size = cur->_size - tmp->_size - 1;

			// 将分裂kv和tmp往父节点插入
			if (cur->_parent == NULL) //cur == _root
			{
				_root = new Node;
				_root->_kvs[0] = cur->_kvs[mid];
				cur->_kvs[mid] = pair<K, V>();

				_root->_size = 1;

				_root->_subs[0] = cur;
				_root->_subs[1] = tmp;
				cur->_parent = _root;
				tmp->_parent = _root;

				return true;
			}
			else
			{
				newKV = cur->_kvs[mid];
				sub = tmp;
				cur->_kvs[mid] = pair<K, V>();

				cur = cur->_parent;
			}

		}

		return true;
	}

	void _InsertKV(Node* cur, const pair<K, V>& kv, Node* sub)
	{
		int index = cur->_size-1;
		while (index >= 0)
		{
			if (cur->_kvs[index].first > kv.first)
			{
				cur->_kvs[index+1] = cur->_kvs[index];
				cur->_subs[index+2] = cur->_subs[index+1];
			}
			else
			{
				break;
			}

			--index;
		}

		cur->_kvs[index+1] = kv;
		cur->_subs[index+2] = sub;
		if(sub)
			sub->_parent = cur;

		cur->_size++;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;

		size_t i = 0;
		for (; i < root->_size; ++i)
		{
			_InOrder(root->_subs[i]);
			cout<<root->_kvs[i].first<<" ";
		}

		_InOrder(root->_subs[i]);
	}

protected:
	Node* _root;
};

void TestBtree()
{
	BTree<int, int> t;
	int a[] = {53, 75, 139, 49, 145, 36, 101};
	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
	{
		t.Insert(make_pair(a[i], i));
	}

	t.InOrder();

	BTree<string, string> dict;
}


template<class K, class V, size_t M = 3>
struct BPTreeNonLeafNode
{
	K _keys[M];
	void* _subs[M];
	BPTreeNonLeafNode<K, V, M>* _parent;
	size_t _size;
};

template<class K, class V, size_t M = 3>
struct BPTreeLeafNode
{
	pair<K, V> kvs[M];	
	BPTreeNonLeafNode<K, V, M>* _parent;
	BPTreeNonLeafNode<K, V, M>* _next;
	size_t _size;
};

template<class K, class V, size_t M = 3>
class BPTree
{
protected:
	BPTreeNonLeafNode<K, V, M>* _root;
	BPTreeLeafNode<K, V, M>* _firstLeaf;
};