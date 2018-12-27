/*
 * Sequences.h
 */
#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace BNum;

namespace Sqn
{
	/*
	 * ����������� �����, ����������� ������������������.
	 */
	class Sequenses {

		/*
		 * �������� ������������������.
		 */
		string name;

	public:
		/*
		 * �������� ���������� ������, ������ �������� ������������������.
		 */
		Sequenses(string name) : name(name) {}

		/*
		 * ���������� ���� ����������������� � ������� n.
		 */
		virtual BigInteger GetSqNum(size_t n) = 0;

	};

	/*
	 * �����, ����������� ������������������ ���������.
	 */
	class FibonacciSeq : public Sequenses {

		/*
		 * ������, � ������� ����� ��������� ����� ���������.
		 */
		vector <BigInteger> FibSq;

	public:

		/*
		 * �����������, �������� ��� �����������������.
		 */
		FibonacciSeq() : Sequenses("Fibonacci sequense") {}

		/*
		 * ���������� ���� ������������������ � ������� n.
		 *
		 * @param num ����� ����� ������������������.
		 * @returns ���� ������������������.
		 */
		BigInteger GetSqNum(size_t num) {
			size_t Size = FibSq.size();
			if (Size == 0) {
				BigInteger f1;
				BigInteger f2("1");
				FibSq.push_back(f1);
				FibSq.push_back(f2);
				Size = FibSq.size();
			}
			if (Size - 1 >= num) {
				return FibSq.at(num);
			}
			else {
				BigInteger f1(FibSq.at(Size - 2));
				BigInteger f2(FibSq.at(Size - 1));
				BigInteger fn;
				for (size_t i = Size - 1; i < num; i++) {
					fn = (BigInteger)(f1 + f2);
					FibSq.push_back(fn);
					f1 = f2;
					f2 = fn;
				}
				return FibSq.at(num);
			}
		}

		/*
		 * ������� ������ n ������ �����������������.
		 *
		 * @param num ����� ����� ������������������.
		 */
		void FibDisplay(size_t n) {
			if (n > FibSq.size()) {
				GetSqNum(n);
			}
			for (size_t i = 0; i < n + 1; i++) {
				cout << FibSq.at(i) << endl;
			}
		}
	};
}
