#define _CRT_SECURE_NO_WARNINGS 1

#include"BigData.h"

void Test1()
{
	BigData n1(123456);

	BigData b2("12346678");
	BigData b3("+12346678");
	BigData b4("-123466");
	BigData b5("+");
	BigData b6("    ");
	BigData b7("12346aaaa");
	BigData b8("+asd12346678");
	BigData b9("000012346678");

	cout << "n1:" << n1 << endl;
	cout << "b2:" << b2 << endl;
	cout << "b3:" << b3 << endl;
	cout << "b4:" << b4 << endl;
	cout << "b5:" << b5 << endl;
	cout << "b6:" << b6 << endl;
	cout << "b7:" << b7 << endl;
	cout << "b8:" << b8 << endl;
	cout << "b9:" << b9 << endl;
}
void testAdd()
{
	BigData b1("-45353");
	BigData b2("37353753");
	BigData b3("-   9223372036854775808");
	BigData b4("     9223372036854775800");
	BigData b5("    -9223372036854775810");
	BigData b6("9223372036854775900");

	//1、都在INT64范围内<运算后在范围内，运算后不在范围内>（再进行构造可以解决）
	cout << (b1 + b1) << endl;
	cout << (b2 + b2) << endl;
	cout << (b1 + b2) << endl;
	cout << "b4:" << b4 << endl;
	cout << (b1 + b4) << endl;

	cout << b3 << endl;
	cout << (b1 + b3) << endl;
	cout << (b2 + b4) << endl;

	//2、都不在INT64范围内<运算后在范围内，运算后不在范围内>
	cout << (b2 + b5) << endl;
	cout << (b1 + b6) << endl;
	cout << (b6 + b1) << endl;

	//3、一个在一个不在<运算后在范围内，运算后不在范围内>
}

void testSub()
{
	BigData b1("-45353");
	BigData b2("37353753");
	BigData b3("-9223372036854775808");
	BigData b4("9223372036854775800");
	BigData b5("-9223372036854775810");
	BigData b6("9223372036854775900");
	//1、都在INT64范围内<运算后在范围内，运算后不在范围内>（再进行构造可以解决）
	cout << (b1 - b2) << endl;
	cout << (b2 - b1) << endl;
	cout << (b3 - b1) << endl;
	cout << (b1 - b4) << endl;
	cout << (b3 - b2) << endl;
	cout << (b4 - b1) << endl;
	cout << (b1 - b3) << endl;
	cout << (b2 - b4) << endl;
	cout << endl;

	//2、一个在一个不在<运算后在范围内，运算后不在范围内>


	cout << (b5 - b1) << endl;
	cout << (b1 - b5) << endl;
	cout << endl;
	cout << (b6 - b2) << endl;
	cout << (b2 - b6) << endl;
	cout << endl;
	cout << (b6 - b5) << endl;
	cout << (b5 - b6) << endl;
	cout << (b2 - b5) << endl;
	cout << (b1 - b6) << endl;
	cout << (b6 - b1) << endl;
}


void testMul()
{
	BigData b1("-45353");
	BigData b2("37353753");
	BigData b3("-9223372036854775808");
	BigData b4(" 9223372036854775800");
	BigData b5("-9223372036854775810");
	BigData b6(" 9223372036854775900");
	//1、都在INT64范围内<运算后在范围内，运算后不在范围内>（再进行构造可以解决）
	cout << (BigData("999") * BigData("22222222222222222222222222222")) << endl;

	cout << (b2 * b1) << endl;
	cout << (b1 * b2) << endl;
	cout << (b1 * BigData("0")) << endl;
	cout << (BigData("0") * b2) << endl;
	cout << endl;
	cout << (b3 * b1) << endl;
	cout << (b1 * b3) << endl;
	cout << (b1 * b4) << endl;
	cout << (b4 * b1) << endl;
	cout << (b3 * b2) << endl;
	cout << (b2 * b4) << endl;
	cout << endl;

	//2、一个在一个不在<运算后在范围内，运算后不在范围内>

	cout << (BigData("0") * b6) << endl;
	cout << (b5 * BigData("0")) << endl;
	cout << (b5 * b1) << endl;
	cout << (b1* b5) << endl;
	cout << endl;
	cout << (b6 * b2) << endl;
	cout << (b2 * b6) << endl;
	cout << endl;
	cout << (b6 * b5) << endl;
	cout << (b5 * b6) << endl;
	cout << (b2 * b5) << endl;
	cout << endl;
	cout << (b1 * b6) << endl;
	cout << (b6 * b1) << endl;
}
void testDiv()
{
	BigData b1("-45353");
	BigData b2("37353753");
	BigData b3("-9223372036854775808");
	BigData b4(" 9223372036854775800");
	BigData b5("-9223372036854775810");
	BigData b6(" 9223372036854775900");
	BigData b7("-1231123203367738338252");


	//1、排除除数为0
	//cout << (b1 / BigData(0)) << endl;

	//2、在范围内

	cout << (b1 / b2) << endl;
	cout << (b2 / b1) << endl;


	//3、不在范围内<左（被除数）比右（除数）小为0，左比右大>
	cout << (b2 / b5) << endl;
	cout << (b2 / b6) << endl;

	cout << (b5 / b2) << endl;
	cout << (b6 / b2) << endl;
	cout << (b6 / b1) << endl;
	cout << (b5 / b1) << endl;

	cout << b7 / b1 << endl;
}

void testMod()
{
	BigData b1("-45353");
	BigData b2("37353753");
	BigData b3("-9223372036854775808");
	BigData b4(" 9223372036854775800");
	BigData b5("-9223372036854775810");
	BigData b6(" 9223372036854775900");
	BigData b7("-1231123203367738338252");

	//1、排除除数为0
	//cout << (b1 / BigData(0)) << endl;

	//2、在范围内

	cout << (b1 % b2) << endl;
	cout << (b2 % b1) << endl;


	//3、不在范围内<左（被除数）比右（除数）小为0，左比右大>
	cout << (b2 % b5) << endl;
	cout << (b2 % b6) << endl;

	cout << (b5 % b2) << endl;

	cout << (b6 % b2) << endl;
	cout << (b6 % b1) << endl;
	cout << (b5 % b1) << endl;

	cout << b7 % b1 << endl;
}

// RSA 

int main()
{
	//testAdd();
	//testSub();
	//testMul();
	//testDiv();
	testMod();

	system("pause");
	return 0;
}