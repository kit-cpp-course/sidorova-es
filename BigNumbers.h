/*
 * BigNumbers.h
 */
#pragma once
#include <vector>
#include <string>
using namespace std;

namespace BNum
{
	// ��������������� ���������� ������ BigInteger.
	class BigInteger;

	// ��������������� ���������� ������ BigDecimal.
	class BigDecimal;

	class BigNumber {
	public:
		/*
		 * �������� ������ �������������� ������ �������� ����� � BigDecimal.
		 */
		virtual explicit operator BigDecimal () const = 0;

		/*
		 * �������� ������ �������������� ������ �������� ����� � BigInteger.
		 */
		virtual explicit operator BigInteger () const = 0;

		/*
		 * �������� �������� ����� � BigInteger.
		 */
		virtual BigDecimal operator + (const BigInteger &) const = 0;

		/*
		 * �������� �������� ����� � BigDecimal.
		 */
		virtual BigDecimal operator + (const BigDecimal &) const = 0;

		/*
		 * ��������� �������� ����� � BigInteger.
		 */
		virtual BigDecimal operator - (const BigInteger &) const = 0;

		/*
		 * ��������� �������� ����� � BigDecimal.
		 */
		virtual BigDecimal operator - (const BigDecimal &) const = 0;

	};

	/*
	 * �����, ����������� ������� ����� �����.
	 */
	class BigInteger : public BigNumber {
		/*
		 * ��������� �������
		 */
		static const int base = 1000000;

		/*
		 * ���������� ����, ������� ����� ��������� � ����� ������.
		 */
		static const int num = 6;

		/*
		 * ������, � ������� ����� ��������� ������� �����.
		 */
		vector<int> value;

		/*
		 * ������� �������������� ���� �� ������� ��������.
		 */
		void RemZeros();

	public:
		 /*
		  * ����������� �� ���������. ������� ������� �����.
		  */
		BigInteger();

		/*
		 * �������� BigInteger �� ������ �����.
		 */
		BigInteger(int x);

		/*
		 * �����������, ��������� ������� �����, ���������� �� ������.
		 *
		 * @param str ������, �� ������� ���������� ������� �����
		 */
		BigInteger(string str);

		/*
		 * ���������� BigInteger � BigDecimal.
		 *
		 * @param right ������ �������.
		 * @returns ����� ���� ������� �����.
		 */
		BigDecimal operator + (const BigInteger & right) const;

		/*
		 * ���������� BigInteger � BigDecimal.
		 *
		 * @param right ������ �������.
		 * @returns ����� ���� ������� �����.
		 */
		BigDecimal operator + (const BigDecimal & right) const;

		/*
		 * �������� �� BigInteger BigInteger.
		 *
		 * @param right ������ �������.
		 * @returns �������� ���� ������� �����.
		 */
		BigDecimal operator - (const BigInteger & right) const;

		/*
		 * �������� �� BigInteger BigDecimal.
		 *
		 * @param right ������ �������.
		 * @returns �������� ���� ������� �����.
		 */
		BigDecimal operator - (const BigDecimal & right) const;

		/*
		 * �������� BigInteger � BigInteger.
		 *
		 * @param right ������ �������.
		 * @returns ������������ ���� ������� �����.
		 */
		BigDecimal operator * (const BigInteger & right) const;

		/*
		 * ���������, ������ �� ����� �����.
		 *
		 * @param right ������ �������.
		 * @returns frue ��� false.
		 */
		bool operator > (const BigInteger & right);

		/*
		 * ���������, ����� �� ���������.
		 *
		 * @param right ������ �������.
		 * @returns frue ��� false.
		 */
		bool operator == (const BigInteger& right);

		/*
		 * �������� ������ �������������� �������� ����� � BigDecimal.
		 */
		explicit operator BigDecimal () const;

		/*
		 * �������� ������ �������������� �������� ����� � BigInteger.
		 */
		explicit operator BigInteger () const;

		/*
		 * ���������� ���������� ������ � ������� �����.
		 */
		int Count();

		friend ostream& operator <<(std::ostream& os, const BigInteger& bi);

	};

	/*
	 * ������� BigInteger �� �����.
	 *
	 * @param os �������� �����.
	 * @param bi �����, ������� ������� ������� �� �����.
	 * @returns �������� �����.
	 */
	ostream& operator <<(std::ostream& os, const BigInteger& bd);


	/*
	 * �����, ����������� ������� ����� � ������� ������.
	 */
	class BigDecimal : public BigNumber {
		/*
		 * ������� �����, � ������� ����� ��������� ����� ����� �����.
		 */
		BigInteger IntPart;

		/*
		 * ������� �����, � ������� ����� ��������� ������� ����� �����.
		 */
		BigInteger Fract; 

		/*
		 * ���������� ������, �������� � ������� �����.
		 */
		static const int prec = 18;

	public:
		 /*
		  * ����������� �� ���������. ������� ������� �����.
		  */
		 BigDecimal();

		 /*
		  * �����������, ��������� ������� ����� �� ����� � ������� �����.
		  *
		  * @param intPart ����� ����� �����
		  * @param fractPart ������� ����� �����
		  */
		 BigDecimal(int intPart, int fractPart=0);

		 /*
		  * �����������, ��������� ������� �����, ���������� �� ������.
		  *
		  * @param str ������, �� ������� ���������� ������� �����
		  */
	  	 BigDecimal(string str);

		 /*
		  * ���������� BigDecimal � BigInteger.
		  *
		  * @param right ������ �������.
		  * @returns ����� ���� ������� �����.
		  */
		 BigDecimal operator + (const BigInteger & right) const;

		 /*
		  * ���������� BigDecimal � BigDecimal.
		  *
		  * @param right ������ �������.
		  * @returns ����� ���� ������� �����.
		  */
		 BigDecimal operator + (const BigDecimal & right) const;

		 /*
		  * �������� �� BigDecimal BigInteger.
		  *
		  * @param right ������ �������.
		  * @returns �������� ���� ������� �����.
		  */
		 BigDecimal operator - (const BigInteger & right) const;

		 /*
		  * �������� �� BigDecimal BigDecimal.
		  *
		  * @param right ������ �������.
		  * @returns �������� ���� ������� �����.
		  */
		 BigDecimal operator - (const BigDecimal & right) const;

		/*
		 * �������� ������ �������������� �������� ����� � BigDecimal.
		 */
		explicit operator BigDecimal () const;

		/*
		 * �������� ������ �������������� �������� ����� � BigInteger.
		 */
		explicit operator BigInteger () const;

		friend ostream& operator <<(std::ostream& os, const BigDecimal& bd);

		friend class BigInteger;

	};
	/*
	 * ������� BigDecimal �� �����.
	 *
	 * @param os �������� �����.
	 * @param bd �����, ������� ������� ������� �� �����.
	 * @returns �������� �����.
	 */
	ostream& operator <<(std::ostream& os, const BigDecimal& bd);
}

