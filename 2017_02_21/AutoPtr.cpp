template<typename T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = NULL)
		:_ptr(ptr)
	{}

	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}

	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		if(this != &ap)
		{
			if(NULL != _ptr)
			{
				delete _ptr;
			}
			_ptr = ap._ptr;
			ap._ptr = NULL;
		}
		return *this;
	}

	~AutoPtr()
	{
		if(NULL != _ptr)
		{
			delete _ptr;
			_ptr = NULL;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}


private:
	T* _ptr;
};

void Test1()  
{  
	AutoPtr<int> ap;
    int *p1 = new int(1);  
    int *p2 = new int(2);  
    AutoPtr<int> ap1(p1);  
    AutoPtr<int> ap2(ap1);  
    ap2 = ap1;  
}  
  
int main ()
{
	Test1();
	return 0;
}