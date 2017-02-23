#pragma once

#include <vector>

//template <class T>
class BitMap
{
public:

	BitMap(size_t N = 1024)
	{
		_array.resize((N>>5) + 1);
	}

	void Set(const size_t value)
	{
		size_t index = value>>5;
		size_t num = value %  32;
		_array[index] |= (1<<num);
	}

	void ReSet(const size_t value)
	{
		size_t index = value>>5;
		size_t num = value % 32;
		_array[index] &= ~(1<<num);
	}

	bool Test(size_t value)
	{
		size_t index = value>>5;
		size_t num = value % 32;
		return _array[index] & (1<<num);
	}

protected:
	vector<size_t> _array;
	size_t _size;
};

