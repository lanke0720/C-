
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
	int _ErrMsg;                //´íÎóÂë
	string _Msgifo;             //´íÎóÂëÃèÊö
};

class NetErr:public Exception
{
public:
	virtual const char* what()const throw()
	{
		cout<<"ÍøÂç´íÎó"<<endl;
		return NULL;
	}
};

class DataErr:public Exception
{
public:
	virtual const char* what()const throw()
	{
		cout<<"Êý¾Ý¿â´íÎó"<<endl;
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
	catch(Exception& e) //Î¢ÈíÌá¹©ÁËÒ»Ð© MSDN
	{
		e.what();
	}
	catch(exception& e)
	{
		e.what();
	}
	catch(...)
	{
		cout<<"Î´Öª´íÎó"<<endl;
	}
	return 0;
}



