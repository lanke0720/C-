
template <typename T>
class SharedPtr
{
public:
	SharedPtr(T* p = NULL)
		:_p(p)
		,_pcount(NULL)
	{
		if(NULL != _p)
		{
			_pcount = new int(1);
		}
	}

	SharedPtr(SharedPtr<T>& sp)
		:_p(sp._p)
		,_pcount(sp._pcount)
	{
		if(NULL != _p)
		{
			++(*_pcount);
		}
	}

	SharedPtr<T>& operator=(SharedPtr<T>& sp)
	{
		if(_p != sp._p)
		{
			if(NULL == _p)    //this 下没有管理空间
			{
				_p = sp._p;
				_pcount = sp._pcount;
			}
			else if(1 == sp._pcount) // 自己独有一块空间
			{
				delete _p;
				delete _pcount;
				_p = sp._p;
				_pcount = sp._pcount;
			}
			else //共享了一块空间
			{
				--(*_pcount);
				_p = sp._p;
				_pcount = sp._pcount;
			}
		}
	}

	~SharedPtr()
	{
		if(_pcount&& 0 == --(*_pcount))
		{
			delete _p;
			delete _pcount;
			_p = NULL;
			_pcount = NULL;
		}
	}
private:
	T* _p;
	int* _pcount;
};