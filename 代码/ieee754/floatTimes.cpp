
#include <iostream>


struct IEEEfloat754
{
	float f;

	unsigned sign;
	unsigned exponent;
	unsigned long long  fraction;		//防止溢出直接用long long 

	IEEEfloat754(float);
	void display()
	{
		std::cout << 1 - sign << ' ' << exponent << ' ' << fraction << '\n';
	}
};

int main()
{
	float f1, f2;
	char op;
	std::cin >> f1 >> f2 >> op;
	IEEEfloat754 fa(f1), fb(f2);

	int bias = 127;	//偏移量
	int csign = 0;
	int  cexpoent = 0;
	long long  cfraction = 0;


	fa.display();
	fb.display();



	if (op == '*')
	{
		csign = fa.sign ^ fb.sign;
		std::cout << 1 - csign << ' ';

		cexpoent = fa.exponent + fb.exponent - bias - 23;
		std::cout << cexpoent << ' ';

		cfraction = fa.fraction * fb.fraction;
		std::cout << cfraction << '\n';

		//规范化
		while (cfraction > 0xFFFFFF)	//大于0xFFFFFF需要向左移动浮点保证有效24位(包含位于小数点左边的隐藏1)
		{
			cfraction >>= 1;
			cexpoent++;					//移动浮点指数相应改变
		}
		while (cfraction < 0x800000)	//小于0x800000需要向右移动浮点保证有效24位(含隐藏1)
		{
			cfraction <<= 1;
			cexpoent--;
		}

		int tempt = (csign << 31) | ((cexpoent & 0xFF) << 23) | (cfraction & 0x7FFFFF);		//拼接
		int* temp = &tempt;
		float* tempf = reinterpret_cast<float*>(temp);
		IEEEfloat754 fc(*tempf);
		fc.display();
		std::cout << *tempf;
	}
	else
	{
		csign = fa.sign ^ fb.sign;
		std::cout << 1 - csign << ' ';

		cexpoent = fa.exponent - fb.exponent + bias-16; // 39 - 23
		std::cout << cexpoent<< ' ';

		long long up = (fa.fraction)<<39;	//63-24=39，这是为了将有效24位的尾数对齐到64位(第一位用于表示符号，实际存储63位)
		long long down =(fb.fraction);		

		cfraction = up / down;
		std::cout << cfraction << '\n';

		//规范化
		while (cfraction > 0xFFFFFF)	
		{
			cfraction >>= 1;
			cexpoent++;					
		}
		while (cfraction < 0x800000)	
		{
			cfraction <<= 1;
			cexpoent--;
		}

		int tempt = (csign << 31) | ((cexpoent & 0xFF) << 23) | (cfraction & 0x7FFFFF);
		int* temp = &tempt;
		float* tempf = reinterpret_cast<float*>(temp);
		IEEEfloat754 fc(*tempf);
		fc.display();
		std::cout << *tempf;
	}



	return 0;
}

IEEEfloat754::IEEEfloat754(float f)
{
	this->f = f;
	//用int指针重新解释浮点数
	float* ptrf = &f;
	int* ptri = reinterpret_cast<int*>(ptrf);
	int i_f = *ptri;

	sign = (i_f >> 31) & 1;
	exponent = (i_f >> 23) & 0xFF;
	fraction = (i_f & 0x7FFFFF) | 1 << 23;
}
