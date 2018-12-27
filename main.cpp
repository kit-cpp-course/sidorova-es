/*
 * main.сpp
 */
#include "BigNumbers.h"
#include "Sequences.h"
#include <iostream>
using namespace BNum;
using namespace Sqn;
/*
 * Выводит первое число Фибоначчи с заданным количеством цифр в числе.
 *
 * @param count количество цифр в числе.
 * @returns число Фибоначчи.
 */
BigInteger Fib(int count);

int main() {
	BigInteger a("1234567891");
	BigInteger b("123456789");
	cout << a + b << endl;
	cout << a - b << endl;
	cout << a * b << endl;

	BNum::BigDecimal dec(0);
	BNum::BigDecimal c(13123.2);
	BNum::BigDecimal d("12345.1");
	cout << c + d << endl;
	cout << c - d << endl;

	FibonacciSeq s;
	BigInteger res = s.GetSqNum(5);
	s.FibDisplay(10);
	BigInteger f;
	f = s.GetSqNum(199);
	cout << f << endl;
	BigInteger r;
	r = Fib(1000);
	cout << r << endl;
}

BigInteger Fib(int count)
{
	FibonacciSeq s;
	BigInteger res;
	int i = 1;
	while (res.Count() != count) {
		res = s.GetSqNum(i);
		i++;
	}
	return res;
}