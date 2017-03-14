#pragma once
#include<vector>
#include<string>
#include <assert.h>

template<class V, class W>
class GraphMatrix
{
public:
	GraphMatrix(V* vertexs, size_t n, const W& invalid = W(), bool isDirected = false)
		:_vertexs(vertexs, vertexs + n)
		,_isDirected(isDirected)
	{
		_martix  = new W*[_vertexs.size()];
		for (size_t i = 0; i < _vertexs.size(); ++i)
		{
			_martix[i] = new W[_vertexs.size()];
			//_indexMap[_vertexs[i]] = i;
			//memset
			for (size_t j = 0; j < _vertexs.size(); ++j)
			{
				_martix[i][j] = invalid;
			}
		}
	}

	~GraphMatrix()
	{}

	// O(N)
	// O(lgN)
	// O(1)
	size_t GetVertexIndex(const V& v)
	{
		for (size_t i = 0; i < _vertexs.size(); ++i)
		{
			if (_vertexs[i] == v)
			{
				return i;
			}
		}

		assert(false);
		return 0;
	}

	void AddEdge(const V& v1, const V& v2, const W& w)
	{
		size_t src = GetVertexIndex(v1);
		size_t dst = GetVertexIndex(v2);
		_martix[src][dst] = w;

		if (_isDirected == false)
		{
			_martix[dst][src] = w;
		}
	}

protected:
	// <V, E>
	vector<V> _vertexs; // ���㼯��
	//V*	_vertexs; // ���㼯��
	W** _martix;  // �ڽӾ��� �ߵļ���
	//size_t _N;	  // ����ĸ���

	bool _isDirected;


	// map<V, size_t> _indexMap;
	// unorderd_map<V, size_t> _indexMap;
};

void TestGraphMatrix()
{
	string city[] = {"����", "����", "�Ӱ�", "μ��", "����"};
	GraphMatrix<string, double> g1(city, sizeof(city)/sizeof(city[0]));
	g1.AddEdge("����", "����", 100.5);
	g1.AddEdge("����", "μ��", 19.5);
	g1.AddEdge("����", "�Ӱ�", 50.5);
	g1.AddEdge("����", "����", 5.5);
}

template<class W>
struct LinKEdge
{
	W _weight;
	LinKEdge<W>* _next;
	size_t _src;
	size_t _dst;

	LinKEdge(size_t src = 0, size_t dst = 0, const W& w = W())
		:_src(src)
		,_dst(dst)
		,_weight(w)
		,_next(NULL)
	{}
};

template<class V, class W>
class GraphLink
{
	typedef LinKEdge<W> Edge;
public:
	GraphLink(V* vertexs, size_t n, const W& invalid = W(), bool isDirected = false)
		:_isDirected(isDirected)
	{
		_vertexs.resize(n);
		_vertexs.assign(vertexs, vertexs+n);

		_linkTables.resize(n, NULL);
	}

	// O(N)
	// O(lgN)
	// O(1)
	size_t GetVertexIndex(const V& v)
	{
		for (size_t i = 0; i < _vertexs.size(); ++i)
		{
			if (_vertexs[i] == v)
			{
				return i;
			}
		}

		assert(false);
		return 0;
	}

	void _AddEdge(size_t src, size_t dst, const W& w)
	{
		// ͷ��
		LinKEdge<W>* edge = new Edge(src, dst, w);
		edge->_next = _linkTables[src];
		_linkTables[src] = edge;
	}

	void AddEdge(const V& v1, const V& v2, const W& w)
	{
		size_t src = GetVertexIndex(v1);
		size_t dst = GetVertexIndex(v2);

		_AddEdge(src, dst, w);
		if (_isDirected == false)
		{
			_AddEdge(dst, src, w);
		}
	}

	void DFS(const V& src) // �ݹ� 
	{
	}

	void GFS(const V& src) // ���

protected:
	vector<V> _vertexs;  // ���㼯��
	vector<Edge*> _linkTables; // �ڽӱ�
	bool _isDirected;
};

void TestGraphLink()
{
	string city[] = {"����", "����", "�Ӱ�", "μ��", "����"};
	GraphLink<string, double> g1(city, sizeof(city)/sizeof(city[0]));
	g1.AddEdge("����", "����", 100.5);
	g1.AddEdge("����", "μ��", 19.5);
	g1.AddEdge("����", "�Ӱ�", 50.5);
	g1.AddEdge("����", "����", 5.5);
}