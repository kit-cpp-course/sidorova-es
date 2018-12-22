#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace BNum;

namespace Sqs
{
	/*
	 * Абстрактный класс, описывающий последовательности.
	 */
	class Sequenses {

		/*
		 * Название последовательности.
		 */
		string name;

	public:
		/*
		 * Основной констуктор класса, задает название последовательности.
		 */
		Sequenses(string name) : name(name) {}

		/*
		 * Возвращает член последовательноти с номером n.
		 */
		virtual BigInt GetSqNum(size_t n) = 0;

	};
	
	/*
	 * Класс, описывающий последовательность Фибоначчи.
	 */
	class FibonacciSeq : public Sequenses{
		
		/*
		 * Вектор, в котором будут храниться числа Фибоначчи.
		 */
		vector <BigInt> FibSq;

	public :

		/*
		 * Конструктор, задающий имя последовательноси.
		 */
		FibonacciSeq() : Sequenses("Fibonacci sequense") {}

		/*
		 * Возвращает член последовательности с номером n.
		 *
		 * @param num номер члена последовательности.
		 * @returns член последовательности.
		 */
		BigInt GetSqNum(size_t num) {
			size_t Size = FibSq.size();
			if (Size == 0){
				BigInt f1;
				BigInt f2("1");
				FibSq.push_back(f1);
				FibSq.push_back(f2);
				Size = FibSq.size();
			}
			if (Size - 1 >= num) {
				return FibSq.at(num);
			}
			else { 
				BigInt f1(FibSq.at(Size - 2));
				BigInt f2(FibSq.at(Size - 1));
				BigInt fn;
				for (size_t i = Size - 1; i < num; i++) {
					fn = f1 + f2;
					FibSq.push_back(fn);
					f1 = f2;
					f2 = fn;
				}
				return FibSq.at(num);
			}
		}
		
		/*
		 * Выводит первые n членов последовательноти.
		 *
		 * @param num номер члена последовательности.
		 */
		void FibDisplay(size_t n) {
			if (n > FibSq.size()) {
				GetSqNum(n);
			}
			for (size_t i = 0; i < n+1; i++) { 
				cout << FibSq.at(i) << endl;
			}
		}
	};
}
