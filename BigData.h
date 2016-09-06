/*
*
*  项目名称：大数据运算
*  接口名称：BigData.h
*  作        者 :  邹明
*  完成时间：2016.04.12
*
*/

#ifndef __BIG_DATA_H__
#define __BIG_DATA_H__

#include<iostream>
using namespace std;
#include<string.h>
#include<assert.h>

#define MAX_INT64 0x7FFFFFFFFFFFFFFF  //小数据能表示的最大值
#define MIN_INT64 0x8000000000000000   //小数据能表示的最小值

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
	std::string Mod(std::string left, std::string right);  //求模


	bool IsINT64OverFlow() const;  //判断是否越界
	void INT64ToString();  //数据转化为字符串
	bool IsLeftStrBig(const char *pLeft, int LSise, const char *pRight, int RSise);  //比较左操作数是否大于有操作数
	char SubLoop(char *pLeft, int LSise, const char *pRight, int RSise);   //除法时每次求商运算

	friend std::ostream&operator<<(std::ostream & cout, const BigData& bigdata);   //输出运算符重载

private:
	INT64 _value;  //整形数据
	string _strData;  //字符串数据
};

#endif
