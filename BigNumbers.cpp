#include "stdafx.h"
#include "BigNumbers.h"
#include <cmath>

BNum::BigInt::BigInt() {
	value.push_back(0);
}

BNum::BigInt::BigInt( string str){
	for (long long i = str.length(); i > 0; i -= num) {
		if (i < num)
			this->value.push_back(atoi(str.substr(0, i).c_str()));//atoi преобразует строку в int, с_str возвращает указатель на массив строк
		else
			this->value.push_back(atoi(str.substr(i - num, num).c_str()));
	}
}

void BNum::BigInt::RemZeros() {
	while (this->value.size() > 1 && this->value.back() == 0) {
		this->value.pop_back();
	}
}

int BNum:: BigInt ::Count() {
	if (value.at(value.size() - 1) == 0) 
		return 1;
	int count = 0;
	count += log10(value[value.size() - 1]) + 1;
	count += (value.size() - 1)*num;
	return count;
}

BNum::BigInt& BNum::BigInt::operator= (const BigInt &bi) {
	this->value = bi.value;
	return *this;
}

bool BNum::BigInt::operator> (const BigInt &right){
	if (value.size() > right.value.size()) {
		return true;
		}
	if (value.size() == right.value.size()) {
		for (int i = 0;i < value.size() - 1;i++) {
		if (value.at(i)<right.value.at(i) ) return false;
		}
	}
	return false;
}

bool BNum::BigInt::operator== (const BigInt &right) {
	if (value.size() != right.value.size()) {
		return false;
	}
	if (value.size() == right.value.size()) {
		if (value.size() == 1) {
			if (value.at(0) != right.value.at(0)) return false;
		}
		else {
			for (int i = 0; i < value.size() - 1;i++) {
				if (value.at(i) != right.value.at(i)) return false;
			}
			return true;
		}
	}
}
 
ostream& BNum ::operator<< (std::ostream& os, const BigInt& bi) {
	if  (bi.value.at(bi.value.size()-1) == 0) {
		os << 0;
	} 
	else {
		os << bi.value.at(bi.value.size() - 1);
		if (bi.value.size() >= 2) {
			long long i = bi.value.size() - 2;

			for (i; i >= 0; i--)
			{
				if (bi.value.at(i) == 0) {/////////////здесь добавляем впереди стоящие нули в ячейке
					for (int k = 0;k < BigInt::num;k++) {
						os << "0";
					}
				}
				else {
					int n = log10(bi.value.at(i)) + 1; 

					if (n != BigInt::num)
					{
						while (BigInt::num - n) {
							os << "0";
							n++;
						}
					}////////////////////////////////
					os << bi.value.at(i);
				}
			}
		}
	}
	return os;
}

BNum::BigInt  BNum::BigInt::operator+ ( const BigInt& right)const {
	int carry = 0; // флаг переноса из предыдущего разряда
	BigInt res = *this;
	int max = ((value.size() > right.value.size()) ? value.size() : right.value.size());
	for (size_t i = 0; i < max || carry != 0; i++) {
		if (i == res.value.size()) res.value.push_back(0);
		res.value[i] += carry + (i < right.value.size() ? right.value[i] : 0);
		carry = res.value[i] >= BigInt::base;
		if (carry != 0) res.value[i] -= BigInt::base;
	}
	return res;
}

BNum::BigInt BNum::BigInt :: operator- ( const BigInt& right) const {
	if (value.size() < right.value.size()) {
		BigInt res("0");
		return res;
	}
	else if (value.size() == right.value.size()) {
		if (value.at(value.size() - 1) < right.value.at(right.value.size() - 1)) {
			BigInt res("0");
			return res;
		}
	}
	BigInt res=*this;
	int carry = 0;
	for (size_t i = 0; i < right.value.size() || carry != 0; i++) {
		res.value[i] -= carry + (i < right.value.size() ? right.value[i] : 0);
		carry = value[i] < 0;
		if (carry != 0) res.value[i] += BigInt::base;
	}
	res.RemZeros();
	return res;
}

BNum::BigInt BNum::BigInt ::operator* ( const BigInt& right) const {
	BigInt res;
	res.value.resize(value.size() + right.value.size());
	for (size_t i = 0; i < value.size(); ++i) {
		int carry = 0;
		for (size_t j = 0; j < right.value.size() || carry != 0; j++) {
			long long cur = res.value[i + j] + value[i] * 1LL * (j < right.value.size() ? right.value[j] : 0) + carry;
			res.value[i + j] = (cur % BigInt::base);
			carry = (int)(cur / BigInt::base);
		}
	}
	res.RemZeros();
	return res;
}

BNum::BigDecimal::BigDecimal() {
	fract = 0.;
}

BNum::BigDecimal::BigDecimal(string str) {
	size_t index=0;
	while (index < str.length()) {
		if (str[index] == '.')  
		{
			string s = str.substr(0, index);
			BigInt f(s);
			IntPart = f;
			if(atoi(str.substr(index + 1, 9).c_str()) !=0) {//далее работаем с дробной частью
				int i = 1;
				int CountLeadZeros = 0;
				while (atoi(str.substr(index + 1, i).c_str()) == 0)
				{
					CountLeadZeros++;
					i++;
				}
				fract = atoi(str.substr(index + i, 9).c_str()); // может быть больше, чем unsigned long, так что надо ввести ограничегие
				if (fract <   pow(10, 9- CountLeadZeros)) {//дополняем дробную часть справа нулями
					int n = log10(fract) + 1;
					long long k =  9 - CountLeadZeros;
						while (n < k) {
							fract = fract * 10;
							n++;
						}
				}
			}
			else {
				fract = 0;
			}
			return;
		}
		index++; 
	}
}

BNum::BigDecimal& BNum::BigDecimal::operator= (const BigDecimal &bd) {
	this->IntPart = bd.IntPart;
	this->fract = bd.fract;
	return *this;
}

int BNum::BigDecimal::Count() {
	int count;
	count = this->IntPart.Count();
	return count;
}

ostream& BNum ::operator<< (std::ostream& os, const BigDecimal& bd) {
	os << bd.IntPart;
	os << ".";
	if (bd.fract == 0) {
		os << "0";
		return os;
	}
	int n = log10(bd.fract) + 1;
	if ( n < 9) { // 9-количество знаков после запятой
		while (9-n) {
			os << "0";
			n++;
		}
		os << bd.fract;
		return os;
	}
	else {
		os << bd.fract;
	}
	return os;
}

BNum::BigDecimal  BNum::BigDecimal::operator+ (const BigDecimal& right)const {
	BigDecimal res;
	BigInt IntRes = this->IntPart;
	unsigned long fractRes = this->fract;

	IntRes = IntRes + right.IntPart;
	fractRes = fractRes + right.fract;
	if (fractRes >= 1000000000) {
		BigInt one("1");
		IntRes = IntRes + one;
		fractRes = fractRes % 1000000000;
	}
	res.IntPart = IntRes;
	res.fract = fractRes;
	return res;
}

BNum::BigDecimal  BNum::BigDecimal::operator- (const BigDecimal& right)const {
	BigDecimal res;
	BigInt IntRes = this->IntPart;
	unsigned long fractRes = this->fract;

	BigInt rightPartInt=right.IntPart;
	if (rightPartInt > IntRes) {
		return res;
	}
	else if (rightPartInt == IntRes) {
		if (right.fract > fractRes) return res;
		else {
			BigInt zero("0");
			IntRes=zero;
			fractRes = fractRes - right.fract;
			res.IntPart = IntRes;
			res.fract = fractRes;
			return res;
		}
	}
	else {
		IntRes =IntRes-right.IntPart;
		if (right.fract > fractRes) {
			BigInt one("1");
			IntRes = IntRes - one;
			fractRes = fractRes * 10;
			fractRes = fractRes - right.fract;
		}
		else {
			fractRes = fractRes - right.fract;
		}
		res.IntPart = IntRes;
		res.fract = fractRes;
	}
	return res;
}