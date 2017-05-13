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
	vector<V> _vertexs; // 顶点集合
	//V*	_vertexs; // 顶点集合
	W** _martix;  // 邻接矩阵 边的集合
	//size_t _N;	  // 顶点的个数

	bool _isDirected;


	// map<V, size_t> _indexMap;
	// unorderd_map<V, size_t> _indexMap;
};

void TestGraphMatrix()
{
	string city[] = {"西安", "安康", "延安", "渭南", "咸阳"};
	GraphMatrix<string, double> g1(city, sizeof(city)/sizeof(city[0]));
	g1.AddEdge("西安", "安康", 100.5);
	g1.AddEdge("西安", "渭南", 19.5);
	g1.AddEdge("西安", "延安", 50.5);
	g1.AddEdge("西安", "咸阳", 5.5);
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
		// 头插
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

	void DFS(const V& src) // 递归 
	{
	}

	void GFS(const V& src) // 广度

protected:
	vector<V> _vertexs;  // 顶点集合
	vector<Edge*> _linkTables; // 邻接表
	bool _isDirected;
};

void TestGraphLink()
{
	string city[] = {"西安", "安康", "延安", "渭南", "咸阳"};
	GraphLink<string, double> g1(city, sizeof(city)/sizeof(city[0]));
	g1.AddEdge("西安", "安康", 100.5);
	g1.AddEdge("西安", "渭南", 19.5);
	g1.AddEdge("西安", "延安", 50.5);
	g1.AddEdge("西安", "咸阳", 5.5);
}