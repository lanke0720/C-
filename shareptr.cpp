
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
			if(NULL == _p)    //this ��û�й���ռ�
			{
				_p = sp._p;
				_pcount = sp._pcount;
			}
			else if(1 == sp._pcount) // �Լ�����һ��ռ�
			{
				delete _p;
				delete _pcount;
				_p = sp._p;
				_pcount = sp._pcount;
			}
			else //������һ��ռ�
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