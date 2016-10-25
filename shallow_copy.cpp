#include <iostream>
using namespace std;
/*
class String
{
public:
	String(const char* pstr = "")
		:_pcount(new int)
	{
		if(NULL == pstr)
		{
			_pstr = new char[1];
			*_pstr = '\0';
		}
		else
		{
			_pstr = new char[strlen(pstr)+1];
			strcpy(_pstr,pstr);
		}
		*_pcount = 1;
	}
	String(const String& t)
		:_pstr(t._pstr)
		,_pcount(t._pcount)
	{
		++(*_pcount);
	}
	String& operator=(const String& t)
	{
		if(this != &t)
		{
			if( 0 == --(*_pcount))
			{
				delete[] _pstr;
				delete _pcount;
			}
			_pstr = t._pstr;
			_pcount = t._pcount;
			++(*_pcount);
		}
		return *this;
	}

	~String()
	{
		if(0 == --(*_pcount))
		{
			delete[]_pstr;
			delete _pcount;
			_pstr = NULL;
			_pcount = NULL;
		}
	}

private:
	char* _pstr;
	int* _pcount;
};
void Funtest()
{
	String s1("hello");
	String s2(s1);
	String s3;
	s3 = s2;
}
int main ()
{
	Funtest();
	return 0;
}
*/

class String
{
public:
	String(const char* pstr = "")
		//:_pstr(new char[strlen(pstr)+4+1])
	{
		/*if(NULL == pstr)
		{
			_pstr = new char[5];
			*_pstr = '\0';
		}
		else
		{*/
			_pstr = new char[strlen(pstr)+4+1];
			*((int*)(_pstr)) = 1; 
			_pstr = _pstr + 4;
			strcpy(_pstr,pstr);   //切记指针的位置
		//}
		//*_pcount = 1;
	}
	String(const String& t)
		:_pstr(t._pstr)
		//,_pcount(t._pcount)
	{
		
		++(*((int*)(_pstr-4)));
		//++(*_pcount);
	}
	String& operator=(const String& t)
	{
		if(this != &t)
		{
			if( 0 == --(*((int*)(_pstr-4))))
			{
				_pstr = _pstr - 4;
				delete[] _pstr;
				//delete _pcount;
			}
			_pstr = t._pstr;
			//_pcount = t._pcount;
			
			++(*((int*)(_pstr-4)));
		}
		return *this;
	}

	~String()
	{
		if(0 == --(*((int*)(_pstr-4))))
		{
			_pstr = _pstr -4;
			delete[]_pstr;
			//delete _pcount;
			_pstr = NULL;
			//_pcount = NULL;
		}
	}

private:
	char* _pstr;
	//int* _pcount;
};
void Funtest()
{
	String s1("hello");
	String s2(s1);
	String s3;
	s3 = s2;
}
int main ()
{
	Funtest();
	return 0;
}