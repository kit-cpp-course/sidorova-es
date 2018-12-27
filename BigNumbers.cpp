/*
 * BigNumbers.сpp
 */
#include "BigNumbers.h"

BNum::BigInteger :: operator BNum::BigDecimal()const {
	BigDecimal Dres(0,0);
	Dres.IntPart = *this;
	return Dres;
}

BNum::BigDecimal ::operator BNum::BigDecimal()const {
	return *this;
}

BNum::BigDecimal ::operator BNum::BigInteger() const {
	return BigInteger(this->IntPart);
}

BNum::BigInteger ::operator BNum::BigInteger()const {
	return *this;
}

void BNum::BigInteger::RemZeros() {
	while (this->value.size() > 1 && this->value.back() == 0) {
		this->value.pop_back();
	}
}

BNum::BigInteger::BigInteger() {
	value.push_back(0);
}

BNum::BigDecimal::BigDecimal() {}

BNum::BigInteger::BigInteger(int x) {
	if (x==0) value.push_back(0);
	while (x) {
		value.push_back(x % (BigInteger::base));
		x = x / (BigInteger::base);
	}
}

BNum::BigDecimal::BigDecimal(int intPart, int fractPart) {
	IntPart= intPart;
	if (fractPart == 0) {
		Fract = 0;
		return;
	}
	int n = log10(fractPart) + 1;
	Fract = fractPart;
	while (n < BigDecimal::prec){
		BigInteger ten("10");
		Fract = (BigInteger)(Fract * ten);
		n++;
	}
}

BNum::BigInteger::BigInteger(string str) {
	for (long long i = str.length(); i > 0; i -= num) {
		if (i < num)
			this->value.push_back(atoi(str.substr(0, i).c_str()));//atoi преобразует строку в int, с_str возвращает указатель на массив строк
		else
			this->value.push_back(atoi(str.substr(i - num, num).c_str()));
	}
}

BNum::BigDecimal::BigDecimal(string str) {
	size_t index = 0;
	while (index < str.length()) {
		if (str[index] == '.')
		{
			string s = str.substr(0, index);
			BigInteger f(s);
			IntPart = f;
			int CountLeadZeros = 0;
			while(str.substr(index+1,1)=="0"){
				str = str.erase(index+1,1);
				CountLeadZeros++;
			}
			Fract = str.substr(index + 1, BigDecimal::prec - CountLeadZeros);
			int n = Fract.Count();
			if (n< BigDecimal::prec) {//дополн€ем дробную часть справа нул€ми
				int k = BigDecimal::prec-CountLeadZeros;
				BigInteger ten("10");
				while (n < k) {
					Fract = (BigInteger)(Fract * ten);
					n++;
				}
			}
			break;
		}
		index++;
	}
}

BNum::BigDecimal BNum::BigInteger::operator+ (const BigInteger & right) const {
	int carry = 0; // флаг переноса из предыдущего разр€да
	BigInteger res = *this;
	int max = ((value.size() > right.value.size()) ? value.size() : right.value.size());
	for (size_t i = 0; i < max || carry != 0; i++) {
		if (i == res.value.size()) res.value.push_back(0);
		res.value[i] += carry + (i < right.value.size() ? right.value[i] : 0);
		carry = res.value[i] >= BigInteger::base;
		if (carry != 0) res.value[i] -= BigInteger::base;
	}
	return (BigDecimal)res;
}

BNum::BigDecimal BNum::BigInteger::operator- (const BigInteger & right) const {
	if (value.size() < right.value.size()) {
		BigInteger res(0);
		return (BigDecimal)res;
	}
	else if (value.size() == right.value.size()) {
		if (value.at(value.size() - 1) < right.value.at(right.value.size() - 1)) {
			BigInteger res(0);
			return (BigDecimal)res;
		}
	}
	BigInteger res = *this;
	int carry = 0;
	for (size_t i = 0; i < right.value.size() || carry != 0; i++) {
		res.value[i] -= carry + (i < right.value.size() ? right.value[i] : 0);
		carry = (res.value[i] < 0);
		if (carry != 0) res.value[i] += BigInteger::base;
	}
	res.RemZeros();
	return (BigDecimal)res;
}

BNum::BigDecimal BNum::BigInteger::operator* (const BigInteger & right) const {
	BigInteger res(0);
	res.value.resize(value.size() + right.value.size());
	for (size_t i = 0; i < value.size(); ++i) {
		int carry = 0;
		for (size_t j = 0; j < right.value.size() || carry != 0; j++) {
			long long cur = res.value[i + j] + value[i] * 1LL * (j < right.value.size() ? right.value[j] : 0) + carry;
			res.value[i + j] = (cur % BigInteger::base);
			carry = (int)(cur / BigInteger::base);
		}
	}
	res.RemZeros();
	return (BigDecimal)res;
}

BNum::BigDecimal BNum::BigInteger::operator+ (const BigDecimal & right) const {
	BigDecimal Dres=((BigDecimal)(*this));
	Dres = Dres + right;
	return Dres;
}

BNum::BigDecimal BNum::BigInteger::operator- (const BigDecimal & right) const {
	BigDecimal Dres = ((BigDecimal)(*this));
	Dres = Dres - right;
	return Dres;
}

bool BNum::BigInteger::operator> (const BigInteger &right) {
	if (value.size() > right.value.size()) {
		return true;
	}
	if (value.size() == right.value.size()) {
		for (int i = 0;i < value.size() - 1;i++) {
			if (value.at(i) < right.value.at(i)) return false;
		}
	}
	return false;
}

BNum::BigDecimal BNum::BigDecimal::operator+ (const BigDecimal & right) const {
	BigDecimal Dres(0,0);
	Dres.IntPart =(BigInteger) (this->IntPart + right.IntPart);
	Dres.Fract = (BigInteger)(this->Fract + right.Fract);
	BigInteger t("1000000000000000000");
	if (Dres.Fract>t) {
		Dres.Fract =(BigInteger)( Dres.Fract - t);
		BigInteger one(1);
		Dres.IntPart = (BigInteger)(Dres.IntPart + one);
	}
	return Dres;
}

BNum::BigDecimal BNum::BigDecimal::operator- (const BigDecimal & right) const {
	BigDecimal Dres;
	BigInteger Int = this->IntPart;
	BigInteger R = right.IntPart;
	BigInteger fInt = this->Fract;
	BigInteger fR = right.Fract;

	if (R > Int) return Dres;
	if (R == Int) {
		if (fR>fInt) return Dres;
		if (fR == fInt)return Dres;
		else {
			Dres.Fract =(BigInteger) (fInt - fR);
			return Dres;
		}
	}
	else {
		if (fR > fInt) {
			BigInteger one(1);
			Int = (BigInteger)(Int - one);
			Dres.IntPart = (BigInteger)(Int - R);
			BigInteger t("1000000000000000000");
			fInt = (BigInteger)(fInt + t);
			Dres.Fract = (BigInteger)(fInt - fR);
		}
		else {
			Dres.IntPart = (BigInteger)(Int - R);
			Dres.Fract = (BigInteger)(fInt - fR);
		}
	}
	return Dres;
}

BNum::BigDecimal BNum::BigDecimal::operator+ (const BigInteger & right) const {
	BigDecimal Dres = ((BigDecimal)(right));
	Dres = Dres + *this;
	return Dres;
}

bool BNum::BigInteger::operator== (const BigInteger &right) {
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

BNum::BigDecimal BNum::BigDecimal::operator- (const BigInteger & right) const {
	BigDecimal Dres;
	BigInteger Int = this->IntPart;
	BigInteger R=right;
	if (R > Int) return Dres;
	else if (R == Int)return Dres;
	else {
		Dres.IntPart = (BigInteger)(Dres.IntPart - right);
	}
	return Dres;
}

ostream& BNum ::operator<< (std::ostream& os, const BigInteger& bi) {
	if (bi.value.at(bi.value.size() - 1) == 0) {
		os << 0;
	}
	else {
		os << bi.value.at(bi.value.size() - 1);
		if (bi.value.size() >= 2) {
			long long i = bi.value.size() - 2;

			for (i; i >= 0; i--)
			{
				if (bi.value.at(i) == 0) {/////////////здесь добавл€ем впереди сто€щие нули в €чейке
					for (int k = 0;k < BigInteger::num;k++) {
						os << "0";
					}
				}
				else {
					int n = log10(bi.value.at(i)) + 1;

					if (n != BigInteger::num)
					{
						while (BigInteger::num - n) {
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

int BNum::BigInteger::Count() {
	if (value.at(value.size() - 1) == 0)
		return 1;
	int count = 0;
	count += log10(value[value.size() - 1]) + 1;
	count += (value.size() - 1)*num;
	return count;
}

ostream& BNum ::operator<< (std::ostream& os, const BigDecimal& bd) {
	os << bd.IntPart;
	os << ".";
	int k;
	BigInteger temp;
	temp = bd.Fract;
	k = temp.Count();
	int Zeros = BigDecimal::prec - k;
	while (Zeros) {
		os << "0";
		Zeros--;
	}
	os << bd.Fract;
	return os;
}
