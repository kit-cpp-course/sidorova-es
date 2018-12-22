#include "stdafx.h"
#include "BigNumbers.h"
#include "Sequenсes.h"
#include <iostream>
using namespace BNum;
using namespace Sqs;

/*
 * Выводит первое число Фибоначчи с заданным количеством цифр в числе.
 *
 * @param count количество цифр в числе.
 * @returns число Фибоначчи.
 */
BigInt Fib(int count);

int main() {
	BigInt a("1234567891");
	BigInt b("123456789");
	cout << a + b << endl;
	cout << a - b << endl;
	cout << a * b << endl;

	BigDecimal c("12345.9000");
	BigDecimal d("12345.1");
	cout << c + d << endl;
	cout << c - d << endl;

	FibonacciSeq s;
	BigInt res= s.GetSqNum(5);
	s.FibDisplay(10);
	BigInt f;
	f = s.GetSqNum(199);
	cout << f << endl;
	BigInt r;
	r = Fib(1000);
	cout << r << endl;
}

BigInt Fib(int count)
{
	FibonacciSeq s;
	BigInt res;
	int i = 1;
	while ( res.Count() !=count) {
		res = s.GetSqNum(i);
		i++;
	}
	return res;
}