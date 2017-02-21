#include <iostream>
using namespace std;

class CInt
{
	//friend ostream& operator<<(ostream& _cout, const CInt& I);
	//friend ostream& operator>>(ostream& _cout, CInt& I);
public:
	CInt& operator=(const CInt& I)
	{
		if(this != &I)
		{
			_value = I._value;
		}
		return *this;
	}
	CInt operator+(const CInt& I)
	{
		CInt data;
		data._value = _value + I._value;
		return data;
	}
	CInt operator-(const CInt& I)
	{
		CInt data;
		data._value = _value - I._value;
		return data;
	}
	CInt operator*(const CInt& I)
	{
		CInt data;
		data._value = _value * I._value;
		return data;
	}
	CInt operator/(const CInt& I)
	{
		CInt data;
		data._value = _value / I._value;
		return data;
	}

	bool operator==(const CInt& I)
	{
		if(*this == I)
		{
			return true;
		}
		return false;
	}
	bool operator!=(const CInt& I)
		if(*this != I)
		{
			return true;
		}
		return false;
	bool operator>(const CInt& I)
		if(*this > I)
		{
			return true;
		}
		return false;
	bool operator<(const CInt& I)
		if(*this < I)
		{
			return true;
		}
		return false;
	bool operator>=(const CInt& I)
		if(*this >= I)
		{
			return true;
		}
		return false;
	bool operator<=(const CInt& I)
		if(*this <= I)
		{
			return true;
		}
		return false;
	bool operator||(const CInt& I)
	{
		if(this)
		{
			return true; 
		}
		if(I._value)
		{
			return true;
		}
		return false;
	}
	bool operator&&(const CInt& I)
	{
		if(this&&I._value)
		{
			return true;
		}
		return false;
	}
	CInt& operator++()
	{
		++_value;
		return *this;
	}
	CInt operator++(int)
	{
		CInt temp(*this);
		_value++;
		return temp;
	}
	CInt& operator--()
	{
		--_value;
		return *this;
	}
	CInt operator--(int)
	{
		CInt temp(*this);
		_value--;
		return temp;
	}

private:
	int _value;
};
//void funtest()
//{
//	CInt data;
//}

int main()
{

	//funtest();
	return 0;
}
