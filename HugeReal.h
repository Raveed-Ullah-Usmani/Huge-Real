#pragma once
#include <fstream>
#include <iostream>
using namespace std;

class HugeReal
{
public:
	bool isNeg;
	int Size;
	int* Nums;
	int decimal_pos;


	HugeReal QuantityWiseSub(const HugeReal& I2)const;
	HugeReal QuantityWiseAdd(const HugeReal& I2)const;
	bool QuantityWiseLesser(const HugeReal& I2)const;
	bool QuantityWiseGreater(const HugeReal& I2)const;
	bool QuantityWiseEqual(const HugeReal& I2)const;
	//void shrink();
	HugeReal identity()const;
	HugeReal NULLHI()const;
	
	void shiftLeft();
	void addZeros(int _dpi);
	void deepCopy(const HugeReal& h);


	void shrinkad();
	void shrinkbd();
public:
	void shrink();





	HugeReal(ifstream& rdr);
	HugeReal(int Size, int _decimal_point);
	HugeReal(int Size);
	HugeReal(const HugeReal& I1);
	HugeReal();
	int operator[](int i)const;
	//int& operator[](int i);
	friend ostream& operator << (ostream&, const HugeReal I);
	friend istream& operator >> (istream&, HugeReal& I);
	bool operator <(const HugeReal& I2)const;
	bool operator <=(const HugeReal& I2)const;
	bool operator >(const HugeReal& I2)const;
	bool operator >=(const HugeReal& I2)const;
	bool operator ==(const HugeReal& I2)const;
	void operator =(const HugeReal& I2);
	HugeReal operator +(const HugeReal& I2)const;
	const HugeReal& operator +=(const HugeReal& I2);
	HugeReal operator -()const;
	HugeReal operator -(const HugeReal& I2)const;
	const HugeReal& operator -=(const HugeReal& I2);
	void operator --();
	void operator ++();
	HugeReal operator *(const HugeReal& I2)const;
	const HugeReal& operator *=(const HugeReal& I2);
	HugeReal operator /(const HugeReal& I2)const;
	const HugeReal& operator /=(const HugeReal& I2);
	HugeReal operator %(const HugeReal& I2)const;
	const HugeReal& operator %=(const HugeReal& I2);

	~HugeReal();
};




