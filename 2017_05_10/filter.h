#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "BitMap.h"

/// @brief BKDR Hash Function  
/// @detail 本 算法由于在Brian Kernighan与Dennis Ritchie的《The C Programming Language》一书被展示而得 名，是一种简单快捷的hash算法，也是Java目前采用的字符串的Hash算法（累乘因子为31）。  
template<class T>  
struct __HashFun1
{
	size_t _001(const char *str)  
	{  
	   register size_t hash = 0;  
	   while (size_t ch = (size_t)*str++)  
	   {         
	      hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..  
        // 有人说将乘法分解为位运算及加减法可以提高效率，如将上式表达为：hash = hash << 7 + hash << 1 + hash + ch;  
        // 但其实在Intel平台上，CPU内部对二者的处理效率都是差不多的，  
        // 我分别进行了100亿次的上述两种运算，发现二者时间差距基本为0（如果是Debug版，分解成位运算后的耗时还要高1/3）；  
        // 在ARM这类RISC系统上没有测试过，由于ARM内部使用Booth's Algorithm来模拟32位整数乘法运算，它的效率与乘数有关：  
        // 当乘数8-31位都为1或0时，需要1个时钟周期  
        // 当乘数16-31位都为1或0时，需要2个时钟周期  
        // 当乘数24-31位都为1或0时，需要3个时钟周期  
        // 否则，需要4个时钟周期  
        // 因此，虽然我没有实际测试，但是我依然认为二者效率上差别不大          
	  }  
	  return hash;  
	}
	size_t operator()(const T& str)
	{
		return _001(str.c_str());
	}

};

/// @brief SDBM Hash Function  
/// @detail 本算法是由于在开源项目SDBM（一种简单的数据库引擎）中被应用而得名，它与BKDRHash思想一致，只是种子不同而已。  
template<class T>  
struct __HashFun2
{
	size_t _002(const char *str)  
	{  
		register size_t hash = 0;  
		while (size_t ch = (size_t)*str++)  
		{  
			hash = 65599 * hash + ch;         
			//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		}  
		return hash;  
	} 

		size_t operator()(const T& str)
		{
			return _002(str.c_str());
		}
	};
	/// @brief RS Hash Function  
	/// @detail 因Robert Sedgwicks在其《Algorithms in C》一书中展示而得名。  
template<class T> 
struct __HashFun3
{
	size_t _003(const char *str)  
	{  
		register size_t hash = 0;  
		size_t magic = 63689;     
		while (size_t ch = (size_t)*str++)  
		{  
			hash = hash * magic + ch;  
			magic *= 378551;  
		}  
		return hash;  
	} 
	size_t operator()(const T& str)
	{
		return _003(str.c_str());
	}
};
	/// @brief AP Hash Function  
	/// @detail 由Arash Partow发明的一种hash算法。  
template<class T> 
struct __HashFun4
{
	size_t _004(const char *str)  
	{  
		register size_t hash = 0;  
		size_t ch;  
		for (long i = 0; ch = (size_t)*str++; i++)  
		{  
			if ((i & 1) == 0)  
			{  
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));  
			}  
			else  
			{  
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));  
			}  
		}  
		return hash; 
	}
		size_t operator()(const T& str)
		{
			return _004(str.c_str());
		}
	
};
/// @brief JS Hash Function  
/// 由Justin Sobel发明的一种hash算法。  
template<class T>  
struct __HashFun5
{
	size_t _005(const char *str)  
	{  
		if(!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;  
		register size_t hash = 1315423911;  
		while (size_t ch = (size_t)*str++)  
		{  
			hash ^= ((hash << 5) + ch + (hash >> 2));  
		}  
		return hash;  
	} 
	size_t operator()(const T& str)
		{
			return _005(str.c_str());
		}
};

template <class T = string, class HashFun1 = __HashFun1<T>,
					class HashFun2 = __HashFun2<T>,
					class HashFun3 = __HashFun3<T>,
					class HashFun4 = __HashFun4<T>,
					class HashFun5 = __HashFun5<T> >
class BloomFilter
{
public:
	BloomFilter(size_t num = 1024)
		:_size(num*5*2)  //一个字符串5个位去确定，再乘2为了防止冲突
		,_bm(_size)  
	{}

	void Set(const T& str)
	{
		size_t hash1 = HashFun1()(str);
		cout<<hash1<<endl;
		size_t hash2 = HashFun2()(str);
		cout<<hash2<<endl;
		size_t hash3 = HashFun3()(str);
		cout<<hash3<<endl;
		size_t hash4 = HashFun4()(str);
		cout<<hash4<<endl;
		size_t hash5 = HashFun5()(str);
		cout<<hash5<<endl;

		_bm.Set(hash1 % _size);
		_bm.Set(hash2 % _size);
		_bm.Set(hash3 % _size);
		_bm.Set(hash4 % _size);
		_bm.Set(hash5 % _size);
	}

	bool TestFilter(const T& str)
	{
		size_t hash1 = HashFun1()(str);
		size_t hash2 = HashFun2()(str);
		size_t hash3 = HashFun3()(str);
		size_t hash4 = HashFun4()(str);
		size_t hash5 = HashFun5()(str);

		if(_bm.Test(hash1 % _size) &&
		_bm.Test(hash2 % _size)&&
		_bm.Test(hash3 % _size)&&
		_bm.Test(hash4 % _size)&&
		_bm.Test(hash5 % _size))
		{
			return true;
		}
		else
		{
			return false;
		}
		/*_bm.Test(hash1 % _size);
		_bm.Test(hash2 % _size);
		_bm.Test(hash3 % _size);
		_bm.Test(hash4 % _size);
		_bm.Test(hash5 % _size);*/

		
	}

protected:
	size_t _size;
	BitMap _bm;
	//size_t _size;

};

void testfilter()
{
	string str = "DESKTOP-5D3CJ27";
	BloomFilter<> test(53);
	test.Set(str);
	cout<<test.TestFilter(str)<<endl;
}