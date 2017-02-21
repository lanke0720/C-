
#include <iostream>
#include <string>
using namespace std;

class Exception
{
public:
	Exception(int errmsg = 0 ,string str = "")
		:_ErrMsg(errmsg)
		,_Msgifo(str)
	{}
	virtual const char* what()const throw()
	{
		cout<<"Exception"<<endl;
		return NULL;
	}
private:
	int _ErrMsg;                //������
	string _Msgifo;             //����������
};

class NetErr:public Exception
{
public:
	virtual const char* what()const throw()
	{
		cout<<"�������"<<endl;
		return NULL;
	}
};

class DataErr:public Exception
{
public:
	virtual const char* what()const throw()
	{
		cout<<"���ݿ����"<<endl;
		return NULL;
	}
};

void funtest()
{
	NetErr net;
	throw net;
}

int main ()
{
	try
	{
		funtest();
	}
	catch(Exception& e) //΢���ṩ��һЩ MSDN
	{
		e.what();
	}
	catch(exception& e)
	{
		e.what();
	}
	catch(...)
	{
		cout<<"δ֪����"<<endl;
	}
	return 0;
}



