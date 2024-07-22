#include<iostream>
#include<math.h>
using namespace std;
void display(float x)
{
	int X = *(int*)&x,y = -2147483648, sum;

	/*if (X & y)cout << 1 << ' ';
	else cout << 0 << ' ';*/
	if (X & y)cout << 0 << ' ';
	else cout << 1 << ' ';

	sum = 0;
	for (int i = 1; i < 9; i++)
	{
		if ((X << i) & y)sum += pow(2, 8 - i);
	}
	cout << sum << ' ';
	sum = pow(2, 23);
	for (int i = 9; i < 32; i++)
	{
		if ((X << i) & y)sum += pow(2, 23 - (i - 8));
	}
	cout << sum << endl;
}
void add(float a, float b)
{
	int x = *(int*)&a, y = *(int*)&b,sum[3][34],k= -2147483648;
	for (int i = 0; i < 32; i++)
	{
		if (x<<i & k)sum[0][i] = 1;
		else sum[0][i] = 0;
		if (y<<i & k)sum[1][i] = 1;
		else sum[1][i] = 0;
	}
	sum[0][32] = 0;
	sum[0][33] = 0;
	sum[1][32] = 0;
	sum[1][33] = 0;

	//for (int j = 0; j < 2; j++)
	//{
	//	cout << "sum " << j << ':';
	//	for (int i = 0; i < 34; i++)
	//	{
	//		cout << sum[j][i];
	//		if (i == 0 || i == 8)cout << ' ';
	//	}
	//	cout << endl;
	//}

	int pow_a = 0, pow_b = 0,pow_sum;
	for (int i = 1; i < 9; i++)
	{
		if (sum[0][i])pow_a += pow(2, 8 - i);
		if (sum[1][i])pow_b += pow(2, 8 - i);
	}

	if (pow_a >= pow_b)
	{
		for (int i = 33; i > 8; i--)
		{
			if (i - (pow_a - pow_b)-2 > 8)sum[1][i] = sum[1][i - (pow_a - pow_b)-2];
			else if (i - (pow_a - pow_b)-2 == 8)sum[1][i] = 1;
			else sum[1][i] = 0;
		}
		for (int i = 33; i > 10; i--)
		{
			sum[0][i] = sum[0][i - 2];
		}
		sum[0][10] = 1;
		sum[0][9] = 0;
		pow_sum = pow_a;
	}
	else if(pow_a < pow_b)
	{
		for (int i = 33; i > 8; i--)
		{
			if (i - (pow_b - pow_a)-2 > 8)sum[0][i] = sum[0][i - (pow_b - pow_a)-2];
			else if (i - (pow_b - pow_a)-2 == 8)sum[0][i] = 1;
			else sum[0][i] = 0;
		}
		for (int i = 33; i > 10; i--)
		{
			sum[1][i] = sum[1][i - 2];
		}
		sum[1][10] = 1;
		sum[1][9] = 0;
		pow_sum = pow_b;
	}

	if (sum[0][0] == sum[1][0])
	{
		sum[2][0] = sum[0][0];
		int judge = 0;
		for (int i = 33; i > 8; i--)
		{
			sum[2][i] = sum[0][i] + sum[1][i] + judge;
			if (judge)judge = 0;
			if (sum[2][i] >= 2)
			{
				sum[2][i] -= 2;
				judge = 1;
			}
		}
	}
	else
	{
		if (abs(a) >= abs(b))
		{
			sum[2][0] = sum[0][0];
			int judge = 0;
			for (int i = 33; i > 8; i--)
			{
				sum[2][i] = sum[0][i] - sum[1][i] - judge;
				if (judge)judge = 0;
				if (sum[2][i] <0 )
				{
					sum[2][i] += 2;
					judge = 1;
				}
			}
		}
		else
		{
			sum[2][0] = sum[1][0];
			int judge = 0;
			for (int i = 33; i > 8; i--)
			{
				sum[2][i] = sum[1][i] - sum[0][i] - judge;
				if (judge)judge = 0;
				if (sum[2][i] < 0)
				{
					sum[2][i] += 2;
					judge = 1;
				}
			}
		}
	}

	/*for (int j = 0; j < 3; j++)
	{
		cout << "sum " << j << ':';
		for (int i = 0; i < 34; i++)
		{
			cout << sum[j][i];
			if (i == 0 || i == 8)cout << ' ';
		}
		cout << endl;
	}*/

	int i,tail= pow(2, 23);
	for (i = 9; i < 34; i++)
	{
		if (sum[2][i])break;
	}
	pow_sum -= (i - 10);
	for (int j = 1;i+j <= 33; j++)
	{
		if (sum[2][i + j])tail += pow(2, 23 - j);
	}

	//cout << sum[2][0] << ' ' << pow_sum << ' ' << tail << endl;
	if (sum[2][0])cout << 0;
	else cout << 1;
	cout << ' ' << pow_sum << ' ' << tail << endl;

	int S1 = sum[2][0] << 31,S2=pow_sum<<23;
	tail -= pow(2, 23);
	int S3 = S1 | S2 | tail;
	float output = *(float*)&S3;
	cout << output;
}
void subtract(float a, float b)
{
	add(a, b * -1);
}
int main()
{
	float a, b;
	char c;
	cin >> a >> b >> c;
	display(a);
	display(b);
	if (c == '+')add(a, b);
	else if (c == '-')subtract(a, b);
	else cout << "error";
}