#include<iostream>
#include<math.h>
using namespace std;
void display(float x)
{
	int X = *(int*)&x, y = -2147483648, sum;
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
void multiply(float a, float b)
{
	int x = *(int*)&a, y = *(int*)&b, k = -2147483648, symbol, pow_a = 0, pow_b = 0, pow_sum, pow_tem;
	long long int tail_sum, tail_tem, tail_a = pow(2, 23), tail_b = pow(2, 23);
	for (int i = 0; i < 32; i++)
	{
		if (i == 0)
		{
			if (((x << i & k) != 0) && ((y << i & k) != 0) || ((x << i & k) == 0) && ((y << i & k) == 0))symbol = 0;
			else symbol = 1;
		}
		else if (i <= 8)
		{
			if (x << i & k)pow_a += pow(2, 8 - i);
			if (y << i & k)pow_b += pow(2, 8 - i);
		}
		else
		{
			if (x << i & k)tail_a += pow(2, 31 - i);
			if (y << i & k)tail_b += pow(2, 31 - i);
		}
	}
	pow_sum = pow_a + pow_b - 127;
	tail_tem = tail_a * tail_b;
	if (tail_tem >= pow(2, 47))
	{
		pow_sum++;
		tail_sum = tail_tem >> 24;
		pow_tem = pow_sum - 24;
	}
	else
	{
		tail_sum = tail_tem >> 23;
		pow_tem = pow_sum - 23;
	}
	if (symbol)cout << 0 << ' ';
	else cout << 1 << ' ';
	cout << pow_tem << ' ' << tail_tem << endl;
	if (symbol)cout << 0 << ' ';
	else cout << 1 << ' ';
	cout << pow_sum << ' ' << tail_sum << endl;
	int S1 = symbol << 31, S2 = pow_sum << 23;
	tail_sum -= pow(2, 23);
	int S3 = S1 | S2 | tail_sum;
	float output = *(float*)&S3;
	cout << output << endl;
}
void divide(float a, float b)
{
	int x = *(int*)&a, y = *(int*)&b, k = -2147483648, symbol, pow_a = 0, pow_b = 0, pow_sum, pow_tem;
	long long int tail_sum, tail_tem, tail_a = pow(2, 23), tail_b = pow(2, 23);
	for (int i = 0; i < 32; i++)
	{
		if (i == 0)
		{
			if (((x << i & k) != 0) && ((y << i & k) != 0) || ((x << i & k) == 0) && ((y << i & k) == 0))symbol = 0;
			else symbol = 1;
		}
		else if (i <= 8)
		{
			if(x << i & k)pow_a += pow(2, 8 - i);
			if (y << i & k)pow_b += pow(2, 8 - i);
		}
		else
		{
			if (x << i & k)tail_a += pow(2, 31 - i);
			if (y << i & k)tail_b += pow(2, 31 - i);
		}
	}
	pow_tem = pow_a - pow_b + 88;
	tail_tem = ( tail_a<<39 ) / tail_b;
	int judge;
	for (judge = 62; judge >= 23; judge--)
	{
		if (tail_tem / pow(2, judge) >= 1)break;
	}
	pow_tem += (62 - judge);
	pow_sum = pow_tem + judge - 23;
	tail_sum = tail_tem>>(judge - 23);
	if (symbol)cout << 0 << ' ';
	else cout << 1 << ' ';
	cout << pow_tem << ' ' << tail_tem << endl;
	if (symbol)cout << 0 << ' ';
	else cout << 1 << ' ';
	cout << pow_sum << ' ' << tail_sum << endl;
	int S1 = symbol << 31, S2 = pow_sum << 23;
	tail_sum -= pow(2, 23);
	int S3 = S1 | S2 | tail_sum;
	float output = *(float*)&S3;
	cout << output << endl;
}
int main()
{
	float a, b;
	char c;
	cin >> a >> b >> c;
	display(a);
	display(b);
	
	if (c == '*')
	{
		display(a * b);
		multiply(a, b);
	}
	else if (c == '/')
	{
		display(a / b);
		divide(a, b);
	}
	else cout << "error";
}