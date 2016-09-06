/*
*
*  ��Ŀ���ƣ�����������
*  �ӿ����ƣ�BigData.h
*  ��        �� :  ����
*  ���ʱ�䣺2016.04.12
*
*/

#ifndef __BIG_DATA_H__
#define __BIG_DATA_H__

#include<iostream>
using namespace std;
#include<string.h>
#include<assert.h>

#define MAX_INT64 0x7FFFFFFFFFFFFFFF  //С�����ܱ�ʾ�����ֵ
#define MIN_INT64 0x8000000000000000   //С�����ܱ�ʾ����Сֵ

#define INIT 0xcccccccccccccccc

typedef long long INT64;
class BigData
{
public:
	BigData(INT64 value = INIT);
	BigData(const char*ptrData);

	BigData operator+(const BigData& bigdata);
	BigData operator-(const BigData& bigdata);
	BigData operator*(const BigData& bigdata);
	BigData operator/(const BigData& bigdata);
	BigData operator%(const BigData& bigdata);


private:
	std::string Add(std::string left, std::string right);
	std::string Sub(std::string left, std::string right);
	std::string Mul(std::string left, std::string right);
	std::string Div(std::string left, std::string right);
	std::string Mod(std::string left, std::string right);  //��ģ


	bool IsINT64OverFlow() const;  //�ж��Ƿ�Խ��
	void INT64ToString();  //����ת��Ϊ�ַ���
	bool IsLeftStrBig(const char *pLeft, int LSise, const char *pRight, int RSise);  //�Ƚ���������Ƿ�����в�����
	char SubLoop(char *pLeft, int LSise, const char *pRight, int RSise);   //����ʱÿ����������

	friend std::ostream&operator<<(std::ostream & cout, const BigData& bigdata);   //������������

private:
	INT64 _value;  //��������
	string _strData;  //�ַ�������
};

#endif
