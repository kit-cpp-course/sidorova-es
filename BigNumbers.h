#pragma once
#include <vector>
#include <string>
using namespace std;

namespace BNum
{
	/*
	 * Абстрактный класс, описывающий большие числа.
	 */
	class BigNumbers {
	public:

		/*
		 * Возвращает количество знаков в большом числе.
		 */
		virtual int Count() = 0;
	};

	/*
	 * Класс, описывающий большое целое число.
	 */
	class BigInt : public BigNumbers {
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
		BigInt();

		/*
		 * Конструктор, создающий большое число, полученное из строки.
		 *
		 * @param str строка, из которой получается большое число
		 */
		BigInt(string str);

		/*
		 * Оператор присваивания.
		 *
		 * Присваивает большому числу значения из другого большого числа.
		 *
		 * @param bi второй операнд. Большое число, из которого следует взять
		 * значения для текущего большого числа.
		 * @returns ссылку на текущий экземпляр класса.
		 */
		BigInt& operator = (const BigInt &bi);

		/*
		 * Возвращает количество знаков в большом числе.
		 */
		int Count();

		/*
		 * Складывает два больших числа.
		 *
		 * @param right правый операнд.
		 * @returns сумму двух больших чисел.
		 */
		BigInt operator +(const BigInt& right) const;
		
		/*
		 * Вычитает два больших числа.
		 *
		 * @param right правый операнд.
		 * @returns сумму двух больших чисел.
		 */
		BigInt operator -(const BigInt& right) const;

		/*
		 * Умножает два больших числа.
		 *
		 * @param right правый операнд.
		 * @returns произведение двух больших чисел.
		 */
		BigInt operator *(const BigInt& right) const;

		/*
		 * Проверяет, больше ли левое число.
		 *
		 * @param right правый операнд.
		 * @returns frue или false.
		 */
		bool operator > (const BigInt& right);

		/*
	   	 * Проверяет, числа на равенство.
		 *
		 * @param right правый операнд.
		 * @returns frue или false.
		 */
		bool operator == (const BigInt& right);

		friend ostream& operator <<(std::ostream& os, const BigInt& bi);
	};


	/*
	 * Выводит большое число на экран.
	 *
	 * @param os выходной поток.
	 * @param bi число, которое следует вывести на экран.
	 * @returns выходной поток.
	 */
	ostream& operator <<(std::ostream& os, const BigInt& bi);


	/*
	 * Класс, описывающий большое число с дробной частью.
	 */
	class BigDecimal : public BigNumbers{

		/*
		 * Переменная, в которой будет храниться целая часть числа.
		 */
		BigInt IntPart;

		/*
		 * Переменная, в которой будет храниться дробная часть числа.
		 * Точность - 9 знаков после запятой.
		 */
		unsigned long fract; 

	public:
		/*
		 * Конструктор по умолчанию. Создает нулевое число.
		 */
		BigDecimal();

		/*
		 * Конструктор, создающий большое число, полученное из строки.
		 *
		 * @param str строка, из которой получается большое число
		 */
		BigDecimal(string str);

		/*
		 * Оператор присваивания.
		 *
		 * Присваивает большому числу значения из другого большого числа.
		 *
		 * @param bd второй операнд. Большое число, из которого следует взять
		 * значения для текущего большого числа.
		 * @returns ссылку на текущий экземпляр класса.
		 */
		BigDecimal& operator = (const BigDecimal &bd);

		/*
		 * Возвращает количество знаков в целой части большого числа.
		 */
		int Count();

		/*
		 * Складывает два больших числа.
		 *
		 * @param right правый операнд.
		 * @returns сумму двух больших чисел.
		 */
		BigDecimal operator +(const BigDecimal& right) const;

		/*
		 * Вычитает два больших числа.
		 *
		 * @param right правый операнд.
		 * @returns разность двух больших чисел.
		 */
		BigDecimal operator -(const BigDecimal& right) const;

		friend ostream& operator <<(std::ostream& os, const BigDecimal& bd);
	};

	/*
	 * Выводит большое число на экран.
	 *
	 * @param os выходной поток.
	 * @param bd число, которое следует вывести на экран.
	 * @returns выходной поток.
	 */
	ostream& operator <<(std::ostream& os, const BigDecimal& bd);
}