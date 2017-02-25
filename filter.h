#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "BitMap.h"

/// @brief BKDR Hash Function  
/// @detail �� �㷨������Brian Kernighan��Dennis Ritchie�ġ�The C Programming Language��һ�鱻չʾ���� ������һ�ּ򵥿�ݵ�hash�㷨��Ҳ��JavaĿǰ���õ��ַ�����Hash�㷨���۳�����Ϊ31����  
template<class T>  
struct __HashFun1
{
	size_t _001(const char *str)  
	{  
	   register size_t hash = 0;  
	   while (size_t ch = (size_t)*str++)  
	   {         
	      hash = hash * 131 + ch;   // Ҳ���Գ���31��131��1313��13131��131313..  
        // ����˵���˷��ֽ�Ϊλ���㼰�Ӽ����������Ч�ʣ��罫��ʽ���Ϊ��hash = hash << 7 + hash << 1 + hash + ch;  
        // ����ʵ��Intelƽ̨�ϣ�CPU�ڲ��Զ��ߵĴ���Ч�ʶ��ǲ��ģ�  
        // �ҷֱ������100�ڴε������������㣬���ֶ���ʱ�������Ϊ0�������Debug�棬�ֽ��λ�����ĺ�ʱ��Ҫ��1/3����  
        // ��ARM����RISCϵͳ��û�в��Թ�������ARM�ڲ�ʹ��Booth's Algorithm��ģ��32λ�����˷����㣬����Ч��������йأ�  
        // ������8-31λ��Ϊ1��0ʱ����Ҫ1��ʱ������  
        // ������16-31λ��Ϊ1��0ʱ����Ҫ2��ʱ������  
        // ������24-31λ��Ϊ1��0ʱ����Ҫ3��ʱ������  
        // ������Ҫ4��ʱ������  
        // ��ˣ���Ȼ��û��ʵ�ʲ��ԣ���������Ȼ��Ϊ����Ч���ϲ�𲻴�          
	  }  
	  return hash;  
	}
	size_t operator()(const T& str)
	{
		return _001(str.c_str());
	}

};

/// @brief SDBM Hash Function  
/// @detail ���㷨�������ڿ�Դ��ĿSDBM��һ�ּ򵥵����ݿ����棩�б�Ӧ�ö�����������BKDRHash˼��һ�£�ֻ�����Ӳ�ͬ���ѡ�  
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
	/// @detail ��Robert Sedgwicks���䡶Algorithms in C��һ����չʾ��������  
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
	/// @detail ��Arash Partow������һ��hash�㷨��  
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
/// ��Justin Sobel������һ��hash�㷨��  
template<class T>  
struct __HashFun5
{
	size_t _005(const char *str)  
	{  
		if(!*str)        // �����ɱ�����ӣ��Ա�֤���ַ������ع�ϣֵ0  
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
		:_size(num*5*2)  //һ���ַ���5��λȥȷ�����ٳ�2Ϊ�˷�ֹ��ͻ
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