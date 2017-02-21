

class string
{
public:
	
		/*string()
			:_pstr(new char[1])
		{
			*_pstr='\0';
		}*/
		string(const char* pstr = "")
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
		}
		string(const string& t)
			:_pstr(t._pstr)
		{}
		string& operator =(const string& t)
		{
			if(this !=  &t)
			{
				_pstr = t._pstr;
			}
			return *this;
		}
		~string()
		{
			if( NULL != _pstr)
			{
				delete[] _pstr;
				_pstr = NULL;
			}
		}
	

private:
	char* _pstr;
};
