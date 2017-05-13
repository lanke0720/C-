#pragma once
#include <vector>
#include <string>
#include <assert.h>
#include <iostream>
using namespace std;

enum Status
{
	EXIST,
	DELETE,
	EMPTY,
};

template<class K, class V>
struct HashNode
{
	K _key;
	V _value;
	Status _status;

	HashNode(const K& key = K(), const V& value = V())
		:_key(key)
		,_value(value)
		,_status(EMPTY)
	{}
};

template<class K> 
struct __HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct __HashFunc<string>  //为了方便简洁，我们实现特化来解决 string 问题
{
	size_t BKDRHash(const char* str)
	{
		register size_t hash = 0;
		while (*str)
		{
			hash = hash * 131 + *str;
			++str;
		}
		return hash;
	}

	size_t operator()(const string& s)
	{
		return BKDRHash(s.c_str());
	}
};

template<class K, class V, class _HashFunc = __HashFunc<K>>
class HashTable
{
	typedef HashNode<K, V> Node;
public:
	HashTable(size_t size)
		:_size(0)
	{
		assert(size > 0);
		_tables.resize(_GetNextCapacity(size));
	}

	pair<Node*, bool> Insert(const K& key, const V& value)  //闭散列方法-开放定址法 线性探测法
	{
		CheckCapcity();
		size_t index = 0;
		index = HashFunc(key);
		if (Find(key))
		{
			//if(Find(key)->_key == key)
			return make_pair(&_tables[index], false);
		}
		while(_tables[index]._status == EXIST) //不用 != EMPTY  因为可能是删除后再插入成为DELETE
		{
			if (_tables[index]._key == key)
			{
				return make_pair(&_tables[index], true);
			}
				++index;

			if (index == _tables.size())
			{
				index = 0;
			}
		}
		_tables[index]._key = key;
		_tables[index]._value = value;
		_tables[index]._status = EXIST;
		++_size;
		return make_pair(&_tables[index], true);
	}

	bool Remove(const K& key)
	{
		Node* ret = Find(key);
		if(ret)
		{
			ret->_status = DELETE;
			--_size;
			return true;
		}
		return false;
	}

	Node* Find(const K& key)
	{
		size_t index = HashFunc(key);
		while (_tables[index]._status != EMPTY)
		{
			if (_tables[index]._key == key)
			{
				if(_tables[index]._status != DELETE)
					return &_tables[index];
			}
				++index;
			if (index == _tables.size())
				index = 0;
		}
		//cout<<"not find"<<endl;
		return (Node*)NULL;
	}
	size_t HashFunc(const K& key)
	{
		_HashFunc hf;
		size_t hash = hf(key);
		return hash % _tables.size();
	}

	void CheckCapcity() //检查α因子
	{
		//if (_tables.empty())
		//{
		//	//_tables.resize(7);
		//	
		//	return _GetNextCapacity(_tables.size());
		//}
		if ((_size * 10)/_tables.size() > 7)
		{
			size_t newsize = _GetNextCapacity(_tables.size());//_tables.size() * 2;
			HashTable<K, V, _HashFunc> temp(newsize);
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i]._status == EXIST)
				{
					temp.Insert(_tables[i]._key, _tables[i]._value);
				}
			}
			this->Swap(temp);
		}
	}

	void Swap(HashTable<K, V>& temp)
	{
		_tables.swap(temp._tables);
		swap(_size, temp._size);
	}
protected:
	size_t _GetNextCapacity(size_t size)
	{
		const int _PrimeSize= 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul,
			786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul,
			25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul,
			805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		for (size_t i = 0; i < 28; ++i)
		{
			if (size <  _PrimeList[i])
			{
				return _PrimeList[i];
			}
		}
		return _PrimeList[27];
	}

protected:
	vector<Node> _tables;
	size_t _size;
};

void testhash()
{
	HashTable<int, int> h1(7);
	h1.Insert(5,0);
	h1.Insert(8,0);
	h1.Insert(7,0);
	h1.Insert(6,0);
	h1.Insert(9,0);
	h1.Insert(1,0);
	h1.Insert(2,0);

	h1.Find(5);
	h1.Remove(5);
	h1.Find(10);
	h1.Find(11);
	h1.Find(8);
	
	

	HashTable<string, string> h2(20);
	h2.Insert("ab","cd");
	h2.Find("ab");
	h2.Find("cd");
}