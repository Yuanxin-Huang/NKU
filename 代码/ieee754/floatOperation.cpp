/*
根据IEEE754的定义，float类型被定义为1个符号位，8位指数位，23位尾数位，其中，指数位按照移码编码，尾数位按照原码编码。

请按照IEEE754定义的float格式的数据，在仅支持整型计算的系统上实现两个float数据的加减法。

你需要将float的数据分解为符号位、指数位和尾数位，然后显式地对齐指数位并做尾数位的计算，请注意尾数位的隐含1。

输入：两个float数和一个计算符(+/-)

输出：第一行为第一个float数解码的三个值，

第二行为第二个float数解码的三个值，

第三行为计算结果的三个值（符号、指数和尾数，均为整型），

第四行，输出float的计算结果

样例输入输出
样例1
输入:
0.25 0.125 +
输出:
1 125 8388608
1 124 8388608
1 125 12582912
0.375

*/

#include <iostream>
#include <cstdio>

using namespace std;

struct IEEE754float
{
	float f;
	//符号位
	unsigned int sign;

	//指数位
	unsigned int exponent;

	//尾数位
	unsigned int fraction;

	
	IEEE754float(float f)
	{
		this->f = f;
		//用int指针重新解释浮点数
		float* ptrf = &f;
		int* ptri = reinterpret_cast<int*>(ptrf);
		int i_f = *ptri;

		sign =(i_f >> 31)&1;
		exponent = (i_f >> 23) & 0xFF;
		fraction = i_f & 0x7FFFFF;
		//隐含1
		fraction = (fraction | 1 << 23);

	}
	
	void display()
	{
		cout << 1-sign << ' ' << exponent << ' ' << fraction << '\n';
		
	}
	
};


int main()
{
	float f1,f2,f3;
	char op;
	cin >> f1>>f2>>op;
	IEEE754float fa(f1),fb(f2);
	fa.display();
	fb.display();

	if ('+' == op)
		f3 = f1 + f2;
	else
		f3 = f1 - f2;
	IEEE754float fc(f3);
	fc.display();
	cout << fc.f;
	
	return 0;
}