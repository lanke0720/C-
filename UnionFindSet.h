#pragma once

class UnionFindSet
{
public:
	UnionFindSet(int n)
		:_n(n)
	{
		_a = new int[n];
		//memset(_a, -1, sizeof(int)*n);
		for (size_t i = 0; i < n; ++i)
		{
			_a[i] = -1;
		}
	}

	int FindRoot(int x)
	{
		int root = x;
		while (_a[root] >= 0)
		{
			root = _a[root];
		}

		return root;
	}

	bool IsIn(int x1, int x2)
	{
		return FindRoot(x1) == FindRoot(x2);
	}

	void Union(int x1, int x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		
		if (root1 != root2)
		{
			_a[root1] += _a[root2];
			_a[root2] = root1;
		}
	}

	int Count()
	{
		size_t count = 0;
		for (size_t i = 0; i < _n; ++i)
		{
			if (_a[i] < 0)
			{
				count++;
			}
		}

		return count;
	}
public:
	int* _a;
	size_t _n;
};

int Friends(int n, int m, int r[][2])
{
	UnionFindSet ufs(n+1);
	for (size_t i = 0; i < m; ++i)
	{
		ufs.Union(r[i][0], r[i][1]);
	}

	return ufs.Count() - 1;
}

void TestFriends()
{
	const int n = 5;
	const int m = 4;
	int r[m][2] = {{1,2},{2,3},{4,5},{1,3}};

	cout<<"ÅóÓÑÈ¦µÄ¸öÊý?"<<Friends(n, m, r)<<endl;
}