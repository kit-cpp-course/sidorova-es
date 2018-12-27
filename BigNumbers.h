/*
 * BigNumbers.h
 */
#pragma once
#include <vector>
#include <string>
using namespace std;

namespace BNum
{
	// Предварительное объявление класса BigInteger.
	class BigInteger;

	// Предварительное объявление класса BigDecimal.
	class BigDecimal;

	class BigNumber {
	public:
		/*
		 * Оператор явного преобразования любого большого числа к BigDecimal.
		 */
		virtual explicit operator BigDecimal () const = 0;

		/*
		 * Оператор явного преобразования любого большого числа к BigInteger.
		 */
		virtual explicit operator BigInteger () const = 0;

		/*
		 * Сложение большого числа с BigInteger.
		 */
		virtual BigDecimal operator + (const BigInteger &) const = 0;

		/*
		 * Сложение большого числа с BigDecimal.
		 */
		virtual BigDecimal operator + (const BigDecimal &) const = 0;

		/*
		 * Вычитание большого числа с BigInteger.
		 */
		virtual BigDecimal operator - (const BigInteger &) const = 0;

		/*
		 * Вычитание большого числа с BigDecimal.
		 */
		virtual BigDecimal operator - (const BigDecimal &) const = 0;

	};

	/*
	 * Класс, описывающий большое целое число.
	 */
	class BigInteger : public BigNumber {
		/*
		 * Основание системы
		 */
		static const int base = 1000000;

		/*
		 * Количество цифр, которое будет храниться в одной ячейке.
		 */
		static const int num = 6;

		/*
		 * Вектор, в котором будет храниться большое число.
		 */
		vector<int> value;

		/*
		 * Удаляет предшествующие нули из вектора значений.
		 */
		void RemZeros();

	public:
		 /*
		  * Конструктор по умолчанию. Создает нулевое число.
		  */
		BigInteger();

		/*
		 * Создание BigInteger из целого числа.
		 */
		BigInteger(int x);

		/*
		 * Конструктор, создающий большое число, полученное из строки.
		 *
		 * @param str строка, из которой получается большое число
		 */
		BigInteger(string str);

		/*
		 * Складывает BigInteger и BigDecimal.
		 *
		 * @param right правый операнд.
		 * @returns сумму двух больших чисел.
		 */
		BigDecimal operator + (const BigInteger & right) const;

		/*
		 * Складывает BigInteger и BigDecimal.
		 *
		 * @param right правый операнд.
		 * @returns сумму двух больших чисел.
		 */
		BigDecimal operator + (const BigDecimal & right) const;

		/*
		 * Вычитает из BigInteger BigInteger.
		 *
		 * @param right правый операнд.
		 * @returns разность двух больших чисел.
		 */
		BigDecimal operator - (const BigInteger & right) const;

		/*
		 * Вычитает из BigInteger BigDecimal.
		 *
		 * @param right правый операнд.
		 * @returns разность двух больших чисел.
		 */
		BigDecimal operator - (const BigDecimal & right) const;

		/*
		 * Умножает BigInteger и BigInteger.
		 *
		 * @param right правый операнд.
		 * @returns произведение двух больших чисел.
		 */
		BigDecimal operator * (const BigInteger & right) const;

		/*
		 * Проверяет, больше ли левое число.
		 *
		 * @param right правый операнд.
		 * @returns frue или false.
		 */
		bool operator > (const BigInteger & right);

		/*
		 * Проверяет, числа на равенство.
		 *
		 * @param right правый операнд.
		 * @returns frue или false.
		 */
		bool operator == (const BigInteger& right);

		/*
		 * Оператор явного преобразования большого числа к BigDecimal.
		 */
		explicit operator BigDecimal () const;

		/*
		 * Оператор явного преобразования большого числа к BigInteger.
		 */
		explicit operator BigInteger () const;

		/*
		 * Возвращает количество знаков в большом числе.
		 */
		int Count();

		friend ostream& operator <<(std::ostream& os, const BigInteger& bi);

	};

	/*
	 * Выводит BigInteger на экран.
	 *
	 * @param os выходной поток.
	 * @param bi число, которое следует вывести на экран.
	 * @returns выходной поток.
	 */
	ostream& operator <<(std::ostream& os, const BigInteger& bd);


	/*
	 * Класс, описывающий большое число с дробной частью.
	 */
	class BigDecimal : public BigNumber {
		/*
		 * Большое число, в котором будет храниться целая часть числа.
		 */
		BigInteger IntPart;

		/*
		 * Большое число, в котором будет храниться дробная часть числа.
		 */
		BigInteger Fract; 

		/*
		 * Количество знаков, хранимое в дробной части.
		 */
		static const int prec = 18;

	public:
		 /*
		  * Конструктор по умолчанию. Создает нулевое число.
		  */
		 BigDecimal();

		 /*
		  * Конструктор, создающий большое число из целой и бробной части.
		  *
		  * @param intPart целая часть числа
		  * @param fractPart дробная часть числа
		  */
		 BigDecimal(int intPart, int fractPart=0);

		 /*
		  * Конструктор, создающий большое число, полученное из строки.
		  *
		  * @param str строка, из которой получается большое число
		  */
	  	 BigDecimal(string str);

		 /*
		  * Складывает BigDecimal и BigInteger.
		  *
		  * @param right правый операнд.
		  * @returns сумму двух больших чисел.
		  */
		 BigDecimal operator + (const BigInteger & right) const;

		 /*
		  * Складывает BigDecimal и BigDecimal.
		  *
		  * @param right правый операнд.
		  * @returns сумму двух больших чисел.
		  */
		 BigDecimal operator + (const BigDecimal & right) const;

		 /*
		  * Вычитает из BigDecimal BigInteger.
		  *
		  * @param right правый операнд.
		  * @returns разность двух больших чисел.
		  */
		 BigDecimal operator - (const BigInteger & right) const;

		 /*
		  * Вычитает из BigDecimal BigDecimal.
		  *
		  * @param right правый операнд.
		  * @returns разность двух больших чисел.
		  */
		 BigDecimal operator - (const BigDecimal & right) const;

		/*
		 * Оператор явного преобразования большого числа к BigDecimal.
		 */
		explicit operator BigDecimal () const;

		/*
		 * Оператор явного преобразования большого числа к BigInteger.
		 */
		explicit operator BigInteger () const;

		friend ostream& operator <<(std::ostream& os, const BigDecimal& bd);

		friend class BigInteger;

	};
	/*
	 * Выводит BigDecimal на экран.
	 *
	 * @param os выходной поток.
	 * @param bd число, которое следует вывести на экран.
	 * @returns выходной поток.
	 */
	ostream& operator <<(std::ostream& os, const BigDecimal& bd);
}

