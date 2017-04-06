#pragma once

#include <stdarg.h>

//#define __DEBUG__

bool enable = false;

/// trace
static string GetFileName(const string& path)
{
	char ch='/';

#ifdef _WIN32
	ch = '\\';
#endif

	size_t pos = path.rfind(ch);
	if(pos==string::npos)
		return path;
	else
		return path.substr(pos+ 1);
}

//用于调试追溯的trace log
inline static void __trace_debug(const char* function,
								 const char* filename,int line,char* format, ...)
{
#ifdef __DEBUG__
	//输出调用函数的信息
	fprintf(stdout,"【%s:%d】%s->",GetFileName(filename).c_str(), line, function);

	//输出用户打的trace信息
	va_list args;
	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);
#endif
}

#define __TRACE_DEBUG(...)  \
__trace_debug(__FUNCTION__,__FILE__,__LINE__,__VA_ARGS__);


////////////////////////////////////////
// 一级空间配置器

typedef void(*HANDLE_FUNC)();
template <int inst>
class __MallocAllocTemplate
{

	static HANDLE_FUNC __mallocAllocOomHandler;

	static void* OOM_Malloc(size_t n)
	{
		while (1)
		{
			if (__mallocAllocOomHandler == 0)
			{
				throw bad_alloc();
			}

			//__mallocAllocOomHandler();
			(*__mallocAllocOomHandler)();
			void* ret = malloc(n);
			if (ret)
				return ret;
		}
	}

public:
	HANDLE_FUNC SetMallocHandler(HANDLE_FUNC f)
	{
		HANDLE_FUNC old = __mallocAllocOomHandler;
		__mallocAllocOomHandler = f;
		return old;

	}

	static void* Allocate(size_t n)
	{
		__TRACE_DEBUG("一级空间配置申请：%u\n", n);
		void *result = malloc(n);
		if (0 == result)
			result = OOM_Malloc(n);

		return result;
	}

	static void Deallocate(void *p, size_t /* n */)
	{
		__TRACE_DEBUG("一级空间配置释放：%x\n", p);
		free(p);
	}
};

template<int inst>
HANDLE_FUNC __MallocAllocTemplate<inst>::__mallocAllocOomHandler = 0;


// 二级空间配置器
template <bool threads, int inst>
class __DefaultAllocTemplate 
{
public:
	static size_t ROUND_UP(size_t bytes)
	{
		return (((bytes) + __ALIGN-1) & ~(__ALIGN - 1));
	}

	static size_t FREELIST_INDEX(size_t n)
	{
		return (n+__ALIGN-1)/__ALIGN - 1;
	}

	// 去内存池进行分配
	static char* ChunkAlloc(size_t size, size_t& nobjs)
	{
		char * result;
		size_t totalBytes = size * nobjs;
		size_t bytesLeft = _endFree - _startFree;

		if (totalBytes <= bytesLeft)
		{
			__TRACE_DEBUG("内存池取%u个对象\n", nobjs);

			result = _startFree;
			_startFree += totalBytes;
			return result;
		}
		else if (bytesLeft >= size)
		{
			nobjs = bytesLeft/size;
			totalBytes = nobjs*size;
			__TRACE_DEBUG("内存池取%u个对象\n", nobjs);

			result = _startFree;
			_startFree += totalBytes;
			return result;
		}
		else
		{
			__TRACE_DEBUG("内存池没有足够内存\n");

			// 将内存池剩余的小块内存挂到自由链表
			if (bytesLeft > 0)
			{
				__TRACE_DEBUG("处理内存剩余的小块内存:%u\n", bytesLeft);

				size_t index = FREELIST_INDEX(totalBytes);
				Obj* obj = (Obj*)_startFree;
				obj->_freeListLink = _freeList[index];
				_freeList[index] = obj;
			}
			
			size_t bytesToGet = totalBytes*2 + ROUND_UP(_heapSize >> 4);
			_startFree = (char*)malloc(bytesToGet);
			__TRACE_DEBUG("malloc:%u内存\n", bytesToGet);

			if (_startFree == NULL) // 申请失败
			{
				// 到更大的自由链表中去找
				size_t index = FREELIST_INDEX(size);
				for (; index < __NFREELISTS; ++index)
				{
					__TRACE_DEBUG("到更大的自由链表[%u]去取\n", index);

					if (_freeList[index])
					{
						_startFree = (char*)_freeList[index];
						_freeList[index] = ((Obj*)_startFree)->_freeListLink;
						_endFree = _startFree + (index+1)*__ALIGN;
						return ChunkAlloc(size, nobjs);
					}
				}
				
				_endFree = NULL;

				// 山穷水尽
				_startFree = (char*)__MallocAllocTemplate<0>::Allocate(bytesToGet);
			}

			_endFree = _startFree+bytesToGet;
			_heapSize += bytesToGet;
			return ChunkAlloc(size, nobjs);
		}
	}

	// 填充自由链表
	static void* Refill(size_t size)
	{
		size_t nobjs = 20;
		char* chunk = ChunkAlloc(size, nobjs);
		if (nobjs == 1)
		{
			return chunk;
		}

		size_t index = FREELIST_INDEX(size);
		Obj* cur = (Obj*)(chunk+size);
		_freeList[index] = cur;

		for (size_t i = 2; i < nobjs; ++i)
		{
			Obj* next = (Obj*)(chunk+size*i);
			cur->_freeListLink = next;
			cur = next;
		}

		cur->_freeListLink = NULL;

		__TRACE_DEBUG("内存池取对象:0x%p, 挂了%u个对象到自由链表\n", chunk, nobjs-1);

		return chunk;
	}

	static void* Allocate(size_t n)
	{
		__TRACE_DEBUG("二级空间配置器申请对象: %u\n", n);

		if (n > __MAX_BYTES)
		{
			return __MallocAllocTemplate<0>::Allocate(n);
		}
		
		size_t index = FREELIST_INDEX(n);
		if (_freeList[index])
		{
			Obj* ret = _freeList[index];
			_freeList[index] = ret->_freeListLink;

			__TRACE_DEBUG("自由链表[%d]取对象:0x%p\n", index, ret);
			return ret;
		}
		else
		{
			void* p = Refill(ROUND_UP(n));
			return p;
		}
	};

	static void Deallocate(void *p, size_t n)
	{

		if (n > __MAX_BYTES)
		{
			__MallocAllocTemplate<0>::Deallocate(p, n);
		}
		else
		{
			__TRACE_DEBUG("释放对象到自由链表:0x%p\n",p);

			Obj* obj = (Obj*)p;
			size_t index = FREELIST_INDEX(n);
			obj->_freeListLink = _freeList[index];
			_freeList[index] = obj;
		}
	}

private:
	enum {__ALIGN = 8};
	enum {__MAX_BYTES = 128};
	enum {__NFREELISTS = __MAX_BYTES/__ALIGN};

	// 狭义内存池
	static char* _startFree; // 
	static char* _endFree;
	static size_t _heapSize;

	union Obj
	{
		union Obj* _freeListLink;
		char client_data[1];    /* The client sees this.        */
	};

	// 自由链表
	static Obj* _freeList[__NFREELISTS]; 
};

template <bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_startFree = NULL;

template <bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_endFree = NULL;

template <bool threads, int inst>
size_t __DefaultAllocTemplate<threads, inst>::_heapSize = 0;

template <bool threads, int inst>
typename __DefaultAllocTemplate<threads, inst>::Obj* __DefaultAllocTemplate<threads, inst>::_freeList[__NFREELISTS] = {0};


#if __MALLOC_ALLOC
typedef __MallocAllocTemplate<0> alloc;
#else
typedef __DefaultAllocTemplate<false, 0> alloc;
#endif //__MALLOC_ALLOC

template<class T, class Alloc>
class SimpleAlloc
{
public:
	static T* Allocate(size_t n)
	{ 
		return 0 == n? 0 : (T*) Alloc::Allocate(n * sizeof (T));
	}

	static T* Allocate(void)
	{ 
		return (T*) Alloc::Allocate(sizeof (T));
	}

	static void Deallocate(T *p, size_t n)
	{ 
		if (0 != n)
			Alloc::Deallocate(p, n * sizeof (T));
	}

	static void Deallocate(T *p)
	{ 
		Alloc::Deallocate(p, sizeof (T));
	}
};

#include <vector>

// Trace
// 1.提高效率 2.内存碎片(外碎片)
// 1.占用着内存不释放，继承结束时候才释放 2.引入内碎片

void TestAlloc()
{
	vector<int*> v;
	SimpleAlloc<int, alloc> sa;
	for(size_t i = 0; i < 20; ++i)
	{
		cout<<"【SimpleAlloc:】"<<i<<endl;
		v.push_back(sa.Allocate());
	}

	int* p1 = sa.Allocate();
	v.push_back(p1);

	while (!v.empty())
	{
		sa.Deallocate(v.back());
		v.pop_back();
	}

	for(size_t i = 0; i < 20; ++i)
	{
		cout<<"【SimpleAlloc:】"<<i<<endl;
		v.push_back(sa.Allocate());
	}
}