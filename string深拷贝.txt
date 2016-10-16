class String
{
public:
	String(const char* pstr = "")
	{
		if(NULL == pstr)
		{
			_pstr = new char[1];
			*_pstr = '\0'; 
		}
		else
		{
			_pstr = new char[strlen(pstr)+1];
			strcpy(_pstr , pstr);
		}
	}
	String(const String& t)
	{
		_pstr = new char[strlen(t._pstr)+1];
		strcpy(_pstr , t._pstr);
	}
	String& operator=(const String& t )                     //
	{
		if(this != &t)
		{
			char *ptemp = new char[strlen(t._pstr)+1];
			strcpy(ptemp,t._pstr);
			delete[] _pstr;
			_pstr = ptemp;
		}
		return *this;
	}
	~String()
	{
		if(NULL != _pstr)
		{
			delete[] _pstr;
			_pstr = NULL;
		}

	}

private:
	char* _pstr;
};
int main()
{
	String s1("hello");
	String s2(s1);
	String s3 = s2;
	return 0;
}
