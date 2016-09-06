#define _CRT_SECURE_NO_WARNINGS 1

#include"BigData.h"

BigData::BigData(INT64 value)
:_value(value)
{
	INT64ToString();
}

BigData::BigData(const char*ptrData)
{
	//123456   //+1223356  //122334qwer   //qwee123   //0000qwer
	assert(ptrData);

	char *pstr = (char*)ptrData;
	char cSymbol = '+';
	if (('+' == *pstr) || ('-' == *pstr))
	{
		cSymbol = *pstr;
		pstr++;
	}
	else if (('0' <= *pstr) && ('9' >= *pstr))
	{
		cSymbol = '+';
	}
	else if (*pstr == ' ')
	{
		while (*pstr == ' ')
		{
			pstr++;
		}
		if (('+' == *pstr) || ('-' == *pstr))
		{
			cSymbol = *pstr;
			pstr++;
		}
		else if (('0' <= *pstr) && ('9' >= *pstr))
		{
			cSymbol = '+';
		}
	}
	else
	{
		return;
	}

	while (' ' == *pstr)
		pstr++;
	while ('0' == *pstr)
		pstr++;
	_strData.resize(strlen(ptrData) + 1);
	_strData[0] = cSymbol;

	_value = 0;
	int iCount = 1;
	while ((*pstr >= '0') && (*pstr <= '9'))
	{
		_value = _value * 10 + (*pstr - '0');
		_strData[iCount] = *pstr;

		pstr++;
		iCount++;
	}
	_strData.resize(iCount);


	if (cSymbol == '-')
	{
		_value = 0 - _value;
	}

}

void BigData::INT64ToString()
{
	char cSymbl = '+';
	if (_value < 0)
	{
		cSymbl = '-';
	}
	//1234567
	//7654321
	_strData.append(1, cSymbl);
	INT64 temp = _value;
	if (temp < 0)
	{
		temp = 0 - temp;
	}
	while (temp)
	{
		_strData.append(1, temp % 10 + '0');
		temp /= 10;
	}
	char *pleft = (char*)_strData.c_str() + 1;
	char *pright = pleft + _strData.size() - 2;

	while (pleft < pright)
	{
		char tem = *pleft;
		*pleft = *pright;
		*pright = tem;
		pleft++;
		pright--;
	}

}

bool BigData::IsINT64OverFlow()const
{
	std::string temp("+9223372036854775807");
	if ('-' == _strData[0])
	{
		temp = "-9223372036854775808";
	}
	if (_strData.size() < temp.size())
	{
		return true;
	}
	else if ((_strData.size() == temp.size()) && (_strData <= temp))
	{
		return true;
	}
	return false;
}

char BigData::SubLoop(char *pLeft, int LSize, const char *pRight, int RSize)
{
	assert(pLeft);
	assert(pRight);
	char cRet = '0';
	while (true)
	{
		while ((*pLeft == '0') && LSize>0)
		{
			pLeft++;
			LSize--;
		}

		if (!IsLeftStrBig(pLeft, LSize, pRight, RSize))
		{
			break;
		}

		for (int i = 1; i <= LSize; i++)
		{
			if ((LSize > RSize) && (i == LSize))
			{
				break;
			}
			char ret = pLeft[LSize - i];
			ret -= pRight[RSize - i];
			if (ret < 0)
			{
				pLeft[LSize - i - 1] -= 1;
				ret += 10;
			}
			pLeft[LSize - i] = ret + '0';

		}
		cRet++;
	}
	return cRet;
}

bool BigData::IsLeftStrBig(const char *pLeft, int LSise, const char *pRight, int RSise)
{
	if (LSise > RSise ||
		((LSise == RSise) && (strcmp(pLeft, pRight) >= 0)))
	{
		return true;
	}
	return false;
}

std::ostream&operator<<(std::ostream & _cout, const BigData& bigdata)
{
	if (bigdata.IsINT64OverFlow())
	{
		_cout << bigdata._value;
	}
	else
	{
		char *pData = (char*)bigdata._strData.c_str();
		if ('+' == pData[0])
		{
			pData++;
		}
		_cout << pData;
	}
	return _cout;
}

BigData BigData::operator+(const  BigData& bigdata)  //+ 加法运算符重载
{
	if (IsINT64OverFlow() && bigdata.IsINT64OverFlow())
	{
		if (_strData[0] != bigdata._strData[0])
		{
			return BigData(_value + bigdata._value);
		}
		else
		{
			INT64 temp_max = MAX_INT64 - _value;
			INT64 temp_min = MIN_INT64 - _value;

			//10 -3 =7  5
			//(-10)-(-3)=-7  -5
			if (((_value >= 0) && (temp_max >= bigdata._value)) ||
				((_value < 0) && (temp_min <= bigdata._value)))
			{
				return BigData(_value + bigdata._value);
			}
		}
	}

	if (_strData[0] == bigdata._strData[0])
	{
		return BigData(Add(_strData, bigdata._strData).c_str());
	}
	else
	{
		if (_strData[0] == '+')
		{
			string ptr(bigdata._strData);
			ptr[0] = '+';
			return Sub(_strData, ptr).c_str();
		}
		else
		{
			string ptr(_strData);
			ptr[0] = '+';
			return Sub(bigdata._strData, ptr).c_str();
		}
	}
}

std::string BigData::Add(std::string left, std::string right)
{
	int iLsize = left.size();
	int iRsize = right.size();
	char cSymbol = left[0]; //取得符号位
	if (iLsize < iRsize)
	{
		std::swap(left, right);
		std::swap(iLsize, iRsize);
	}

	std::string sRet;
	sRet.resize(iLsize + 1);

	char Step = 0;
	for (int i = 1; i < iLsize; i++)
	{
		char cRet = left[iLsize - i] - '0' + Step;
		if (i < iRsize)
		{
			cRet += (right[iRsize - i] - '0');
		}
		sRet[iLsize - i + 1] = cRet % 10 + '0';
		Step = cRet / 10;
	}
	sRet[1] = Step + '0';
	sRet[0] = cSymbol;
	return sRet;
}

BigData BigData::operator-(const BigData& bigdata)  //- 减法运算符重载
{
	if (IsINT64OverFlow() && bigdata.IsINT64OverFlow())
	{
		if (_strData[0] == bigdata._strData[0])
		{
			return BigData(_value - bigdata._value);
		}
		else
		{
			INT64 temp_max = _value - MAX_INT64;
			INT64 temp_min = _value - MIN_INT64;

			//10 -3 =7  5
			//(-10)-(-3)=-7  -5
			if (((_value >= 0) && (temp_max <= bigdata._value)) ||
				((_value < 0) && (temp_min >= bigdata._value)))
			{
				return BigData(_value - bigdata._value);
			}
		}
	}
	if (_strData[0] == bigdata._strData[0])
	{
		return BigData(Sub(_strData, bigdata._strData).c_str());
	}
	else
	{
		string ptr(bigdata._strData);
		ptr[0] = _strData[0];
		return Add(_strData, ptr).c_str();
	}

}

std::string BigData::Sub(std::string left, std::string right)
{
	int iLsize = left.size();
	int iRsize = right.size();
	int Max_size = iLsize;
	std::string sRet;
	char cSymbol = left[0];   //取符号位

	if (iLsize <= iRsize)
	{
		if ((iLsize == iRsize) && (strcmp(left.c_str(), right.c_str())<0) && (left[0] == right[0]))
		{
			if ('+' == right[0])
			{
				cSymbol = '-';
			}
			else
			{
				cSymbol = '+';
			}
			Max_size = iRsize;
			std::swap(left, right);
			std::swap(iLsize, iRsize);
		}
	}
	else
	{
		cSymbol = left[0];
		Max_size = iLsize;
	}


	char Step = 0;
	sRet.assign(Max_size, 48);
	for (int i = 1; i < Max_size; i++)
	{
		char cRet = 0;
		if (0<(iLsize - i))
		{
			cRet = left[iLsize - i] - '0' + Step;
		}
		if (i < iRsize)
		{
			if (cRet < right[iRsize - i] - '0')
			{
				cRet += 10;
			}
			Step = 0 - (cRet - Step) / 10;
			cRet -= (right[iRsize - i] - '0');
		}

		sRet[Max_size - i] = cRet + '0';
	}

	sRet[0] = cSymbol;
	return sRet;
}

BigData BigData::operator*(const BigData& bigdata)
{
	if ((0 == _value) || (0 == bigdata._value))
	{
		return BigData(INT64(0));
	}
	if (IsINT64OverFlow() && bigdata.IsINT64OverFlow())
	{
		if (_strData[0] == bigdata._strData[0])
		{
			if (((_value > 0) && ((long long)MAX_INT64 / _value >= bigdata._value)) ||
				((_value < 0) && ((long long)MAX_INT64 / _value <= bigdata._value)))   //同号相乘 结果为正
			{
				return BigData(_value*bigdata._value);
			}
		}
		else
		{
			if (((_value > 0) && ((long long)MIN_INT64 / _value <= bigdata._value)) ||
				((_value < 0) && ((long long)MIN_INT64 / _value >= bigdata._value)))      //异号相乘 结果为负
			{
				return BigData(_value*bigdata._value);
			}
		}
	}

	return BigData(Mul(_strData, bigdata._strData).c_str());
}

std::string BigData::Mul(std::string left, std::string right)
{
	char cSymbol = '+'; //设置符号位
	int iLsize = left.size();
	int iRsize = right.size();
	if (left[0] == right[0])
		cSymbol = '+';
	else
		cSymbol = '-';
	if (iLsize > iRsize)
	{
		std::swap(left, right);
		std::swap(iLsize, iRsize);
	}
	std::string sRet;
	int t = 1;
	if (((left[1] - '0')*(right[1] - '0') + (left[1] - '0')*(right[1] - '0') % 10)<10)
	{
		t = 2;
	}
	else
		t = 1;
	//sRet.resize(iLsize + iRsize - t);
	sRet.assign(iLsize + iRsize - t, '0');
	int sizeRet = iLsize + iRsize - 1;
	sRet[0] = cSymbol;

	int i = 1, j = 1;
	for (i = 1, j = 1; i < iLsize; i++)
	{
		char step = 0;
		char cleft = left[iLsize - i] - '0';
		for (int j = 1; j < iRsize; j++)
		{
			char cRet = cleft*(right[iRsize - j] - '0') + step + (sRet[sizeRet - i - j + 1] - '0');
			step = cRet / 10;
			sRet[sizeRet - i - j + 1] = cRet % 10 + '0';
			if ((j + 1) == iRsize)
				sRet[sizeRet - i - j] = step + '0';
		}

	}
	return sRet;
}

BigData BigData::operator/(const BigData& bigdata)
{
	if (bigdata._strData[1] == '0')
	{
		cout << "除数为 0 " << endl;
		assert(0);
	}
	if (_strData[1] == 0)
		return INT64(0);
	if ((IsINT64OverFlow()) && bigdata.IsINT64OverFlow())
	{
		return _value / bigdata._value;
	}
	if (_strData.size() < bigdata._strData.size())
	{
		return INT64(0);
	}
	else if (_strData.size() == bigdata._strData.size())
	{
		if (strcmp(_strData.c_str() + 1, bigdata._strData.c_str() + 1) < 0)
			return INT64(0);
		if (strcmp(_strData.c_str() + 1, bigdata._strData.c_str() + 1) == 0)
		{
			if (_strData[0] == bigdata._strData[0])
				return INT64(1);
			else
				return INT64(-1);
		}
	}
	return BigData(Div(_strData, bigdata._strData).c_str());
}

std::string BigData::Div(std::string left, std::string right)
{
	string sRet;
	sRet.append(1, '+');
	if (left[0] != right[0])
	{
		sRet[0] = '-';
	}

	char *pLeft = (char *)(left.c_str() + 1);
	char *pRight = (char *)(right.c_str() + 1);
	int DataLen = right.size() - 1;
	int Lsize = left.size() - 1;
	for (int i = 0; i < Lsize; i++)
	{
		if (!IsLeftStrBig(pLeft, DataLen, pRight, right.size() - 1))
		{
			sRet.append(1, '0');
			DataLen++;
		}
		else
		{
			sRet.append(1, SubLoop(pLeft, DataLen, pRight, right.size() - 1));
		}

		if (DataLen + i>Lsize)
		{
			break;
		}

		if (*pLeft == '0')
		{
			pLeft++;
		}
		else
		{
			DataLen = right.size();
		}

	}
	return sRet;
}

BigData BigData:: operator%(const BigData& bigdata)
{
	if (bigdata._strData[1] == '0')
	{
		cout << "除数为 0 或对0求模" << endl;
		assert(0);
	}
	if (_strData[1] == 0)
		return INT64(0);
	if ((IsINT64OverFlow()) && bigdata.IsINT64OverFlow())
	{
		return _value % bigdata._value;
	}
	if (_strData.size() < bigdata._strData.size())
	{
		return BigData(_strData.c_str());
	}
	else if (_strData.size() == bigdata._strData.size())
	{
		if (strcmp(_strData.c_str() + 1, bigdata._strData.c_str() + 1) < 0)
			return INT64(0);
		if (strcmp(_strData.c_str() + 1, bigdata._strData.c_str() + 1) == 0)
		{
			return INT64(0);
		}
	}
	return BigData(Mod(_strData, bigdata._strData).c_str());
}

std::string BigData::Mod(std::string left, std::string right)
{

	char cSymbol = left[0];
	BigData n1(left.c_str() + 1);
	BigData n2(right.c_str() + 1);
	BigData n3 = n1 / n2;
	BigData n4 = n3*n2;
	BigData sRet(n1 - n4);
	sRet._strData[0] = cSymbol;
	return sRet._strData;
}