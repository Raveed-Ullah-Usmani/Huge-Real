#include <fstream>
#include <cstring>
#include "HugeReal.h"
using namespace std;
void HugeReal::shrinkbd()
{
	if (this->Size == 1 || this->decimal_pos == this->Size - 1)
	{
		return;
	}
	int count = 0;
	for (int i = this->Size - 1; i > this->decimal_pos; i--)
	{
		if ((*this)[i] != 0)
		{
			break;
		}
		count++;
	}
	if (count == 0)
	{
		return;
	}
	HugeReal R(this->Size - count, this->decimal_pos);
	R.isNeg = this->isNeg;
	for (int i = 0; i < R.Size; i++)
	{
		R.Nums[i] = (*this)[i];
	}
	(*this) = R;
}
void HugeReal::shrinkad()
{
	if (this->Size == 1 || this->decimal_pos == 0)
	{
		return;
	}
	int count = 0;
	for (int i = 0; i < this->decimal_pos; i++)
	{
		if ((*this)[i] != 0)
		{
			break;
		}
		count++;
	}
	if (count == 0)
	{
		return;
	}
	HugeReal R(this->Size - count, this->decimal_pos - count);
	R.isNeg = this->isNeg;
	for (int i = 0, j = count; i < R.Size; i++, j++)
	{
		R.Nums[i] = (*this)[j];
	}
	(*this) = R;
}
void HugeReal::shrink()
{
	this->shrinkad();
	this->shrinkbd();
}
int HugeReal::operator[](int i)const
{
	if (i < this->Size)
		return this->Nums[i];
	return 0;
}

void HugeReal::deepCopy(const HugeReal& h)
{
	//delete[]this->Nums;
	this->Size = h.Size;
	this->decimal_pos = h.decimal_pos;
	this->Nums = new int[this->Size]{};
	for (int i = 0; i < this->Size; i++)
	{
		this->Nums[i] = h.Nums[i];
	}
}
void HugeReal::addZeros(int _dpi)
{
	if (this->decimal_pos > _dpi)
	{
		return;
	}
	int diff = _dpi - this->decimal_pos;
	HugeReal temp(this->Size + diff, _dpi);
	for (int i = 0, j = 0; i < temp.Size; i++)
	{
		if (i < diff)
		{
			temp.Nums[i] = 0;
		}
		else
		{
			temp.Nums[i] = this->Nums[j];
			j++;
		}
	}
	this->deepCopy(temp);

}




HugeReal HugeReal::identity()const
{
	HugeReal I(1, 0);
	I.isNeg = false;
	I.Nums[0] = 1;
	return I;
}
HugeReal HugeReal::NULLHI()const
{
	HugeReal I(1, 0);
	I.isNeg = false;
	I.Nums[0] = 0;
	return I;
}
int maxof(int x, int y)
{
	if (x > y)
	{
		return x;
	}
	return y;
}
HugeReal::HugeReal(const HugeReal& I1)
{
	
	this->Size = I1.Size;
	this->isNeg = I1.isNeg;
	this->decimal_pos = I1.decimal_pos;
	this->Nums = new int[this->Size];
	for (int i = 0; i < this->Size; i++)
	{
		this->Nums[i] = I1.Nums[i];
	}
}
HugeReal::HugeReal(int size, int dpi)
{
	this->Size = size;
	this->decimal_pos = dpi;
	this->Nums = new int[this->Size]{};
	this->isNeg = false;
}
HugeReal::HugeReal(int size)
{
	this->Size = size;
	this->Nums = new int[this->Size]{};
	this->decimal_pos = 0;
	this->isNeg = false;
}
HugeReal::HugeReal(ifstream& rdr)
{
	string N;
	rdr >> N;
	bool sign = false;
	int i = 0;
	if (N[i] == '+' || N[i] == '-')
	{
		this->isNeg = ((N[i] == '-') ? true : false);
		sign = true;
		i++;
	}
	int dpi = -1;
	for (int j = i; j < N.length(); j++)
	{
		if (N[j] == '.')
		{
			dpi = j;
		}
	}
	if (sign && dpi != -1)
	{
		dpi--;
	}
	this->Size = ((dpi == -1) ? N.length() - i : N.length() - i - 1);
	Nums = new int[this->Size];
	for (int ni = 0; ni < this->Size; i++)
	{
		if (N[i] != '.')
		{
			Nums[this->Size - 1 - ni] = N[i] - 48;
			ni++;
		}

	}
	this->decimal_pos = (dpi == -1) ? 0 : this->Size - dpi;
	this->shrink();
}
HugeReal::HugeReal()
{
	this->Size = 0;
	this->isNeg = 0;
	this->decimal_pos = 0;
	this->Nums = NULL;
}
ostream& operator<< (ostream&, const HugeReal I)
{
	cout << (I.isNeg ? "-" : "+");
	for (int i = 0; i < I.Size; i++)
	{
		if (I.Size - i == I.decimal_pos)
		{
			cout << '.';
		}
		cout << I.Nums[I.Size - 1 - i];
	}
	return cout;
}
istream& operator >> (istream&, HugeReal& I)
{
	string N;
	cin >> N;
	bool sign = false;
	int i = 0;
	if (N[0] == '+' || N[0] == '-')
	{
		sign = true;
	}
	if (N[i] == '+' || N[i] == '-')
	{
		I.isNeg = ((N[i] == '-') ? true : false);
		i++;
	}
	int dpi = -1;
	for (int j = i; j < N.length(); j++)
	{
		if (N[j] == '.')
		{
			dpi = j;
		}
	}
	if (sign && dpi != -1)
	{
		dpi--;
	}



	I.Size = ((dpi == -1) ? N.length() - i : N.length() - i - 1);
	I.Nums = new int[I.Size];
	for (int ni = 0; ni < I.Size; i++)
	{
		if (N[i] != '.')
		{
			I.Nums[I.Size - 1 - ni] = N[i] - 48;
			ni++;
		}

	}
	I.decimal_pos = (dpi == -1) ? 0 : I.Size - dpi;
	I.shrink();
	return cin;
}
HugeReal HugeReal::QuantityWiseSub(const HugeReal& I2)const
{
	HugeReal A = *this;
	HugeReal B = I2;
	A.addZeros(I2.decimal_pos);
	B.addZeros(this->decimal_pos);
	HugeReal R(A.Size, A.decimal_pos);
	int c = 0;
	//if (this->Size > I2.Size)
	{
		for (int i = 0; i < R.Size; i++)
		{
			int S = A[i] - B[i] - c;
			if (S < 0)
			{
				S += 10;
				c = 1;

			}
			else
			{
				c = 0;
			}
			R.Nums[i] = S;
		}
	}
	return R;
}
HugeReal HugeReal::QuantityWiseAdd(const HugeReal& I2)const
{
	HugeReal A = *this;
	HugeReal B = I2;
	A.addZeros(I2.decimal_pos);
	B.addZeros(this->decimal_pos);
	HugeReal R(A.Size + 1, A.decimal_pos);
	int c = 0;
	//if (this->Size > I2.Size)
	{
		for (int i = 0; i < R.Size; i++)
		{
			int S = A[i] + B[i] + c;
			if (S >= 10)
			{
				S %= 10;
				c = 1;

			}
			else
			{
				c = 0;
			}
			R.Nums[i] = S;
		}
	}
	return R;
}
bool HugeReal::QuantityWiseLesser(const HugeReal& I2)const
{
	HugeReal A = *this;
	HugeReal B = I2;
	A.addZeros(I2.decimal_pos);
	B.addZeros(this->decimal_pos);
	if (A.Size - A.decimal_pos > B.Size - B.decimal_pos)
	{
		return false;
	}
	if (A.Size - A.decimal_pos < B.Size - B.decimal_pos)
	{
		return true;
	}
	for (int i = A.Size - 1; i >= 0; i--)
	{
		if (A.Nums[i] > B.Nums[i])
		{
			return false;
		}
		if (A.Nums[i] < B.Nums[i])
		{
			return true;
		}
	}
	return false;

}
bool HugeReal::QuantityWiseGreater(const HugeReal& I2)const
{
	return I2.QuantityWiseLesser(*this);
}
bool HugeReal::QuantityWiseEqual(const HugeReal& I2)const
{
	return this->QuantityWiseLesser(I2) == false && this->QuantityWiseGreater(I2) == false;
}
bool HugeReal::operator <(const HugeReal& I2)const
{
	if (this->isNeg == true && I2.isNeg == false)
	{
		return true;
	}
	if (this->isNeg == false && I2.isNeg == true)
	{
		return false;
	}
	if (this->isNeg)
	{
		if (this->QuantityWiseGreater(I2))
		{
			return true;
		}
		if (this->QuantityWiseLesser(I2))
		{
			return false;
		}
	}
	if (this->QuantityWiseLesser(I2))
	{
		return true;
	}
	return false;
}
bool HugeReal::operator <=(const HugeReal& I2)const
{
	return *this < I2 || *this == I2;
}
bool HugeReal::operator >(const HugeReal& I2)const
{
	return I2 < *this;
}
bool HugeReal::operator >=(const HugeReal& I2)const
{
	return *this > I2 || *this == I2;
}
bool HugeReal::operator ==(const HugeReal& I2)const
{
	return I2 < *this == false && I2>*this == false;
}
void HugeReal::operator =(const HugeReal& I2)
{
	delete[]this->Nums;
	this->isNeg = I2.isNeg;
	this->Size = I2.Size;
	this->decimal_pos = I2.decimal_pos;
	this->Nums = new int[this->Size];
	for (int i = 0; i < this->Size; i++)
	{
		this->Nums[i] = I2.Nums[i];
	}
}
HugeReal HugeReal::operator +(const HugeReal& I2)const
{
	HugeReal R;
	if (this->isNeg == I2.isNeg)
	{
		if ((*this).QuantityWiseGreater(I2))
		{
			R = (*this).QuantityWiseAdd(I2);
			R.isNeg = this->isNeg;

		}
		else
		{
			R = I2.QuantityWiseAdd(*this);
			R.isNeg = I2.isNeg;
		}
	}
	else
	{
		if ((*this).QuantityWiseGreater(I2))
		{
			R = (*this).QuantityWiseSub(I2);
			R.isNeg = this->isNeg;

		}
		else
		{
			R = I2.QuantityWiseSub(*this);
			R.isNeg = I2.isNeg;
		}
	}
	R.shrink();
	if (R.QuantityWiseEqual(NULLHI()))
	{
		R.isNeg = false;
	}
	return R;
}
HugeReal HugeReal:: operator -()const
{
	HugeReal temp = *this;
	temp.isNeg = !this->isNeg;
	return temp;
}
HugeReal HugeReal::operator -(const HugeReal& I2)const
{
	HugeReal R;
	HugeReal temp = -I2;
	R = *this + temp;
	return R;
}
const HugeReal& HugeReal::operator +=(const HugeReal& I2)
{
	*this = *this + I2;
	return *this;
}
const HugeReal& HugeReal::operator -=(const HugeReal& I2)
{
	*this = *this - I2;
	return *this;
}
void HugeReal::operator --()
{
	*this -= identity();
}
void HugeReal::operator ++()
{
	*this += identity();
}
HugeReal HugeReal::operator *(const HugeReal& I2)const
{
	HugeReal X = *this;
	HugeReal Y = I2;
	HugeReal R;
	R = NULLHI();
	HugeReal A = X;
	A.isNeg = false;
	A.decimal_pos = 0;
	HugeReal B = Y;
	B.isNeg = false;
	B.decimal_pos = 0;
	HugeReal Zero = NULLHI();
	HugeReal TR = A;
	HugeReal c = identity();
	while ((B > Zero))
	{
		HugeReal temp = c + c;
		while (temp <= B)
		{
			TR += TR;
			c += c;
			temp = c + c;
		}
		B -= c;
		R += TR;
		TR = A;
		c = identity();

	}
	if (this->isNeg == I2.isNeg)
	{
		R.isNeg = false;
	}
	else
	{
		R.isNeg = true;
	}
	R.decimal_pos = X.decimal_pos + Y.decimal_pos;
	R.shrink();
	return R;
}
const HugeReal& HugeReal::operator *=(const HugeReal& I2)
{
	*this = *this * I2;
	return *this;
}
HugeReal HugeReal::operator /(const HugeReal& I2)const
{
	HugeReal Ans = NULLHI();
	HugeReal Zero = NULLHI();
	if (I2.QuantityWiseEqual(Zero))
	{
		throw 0;
	}
	HugeReal One = identity();
	HugeReal X = (*this);
	X.isNeg = false;
	HugeReal Y = I2;
	Y.isNeg = false;
	HugeReal ten(2, 0);
	ten.Nums[0] = 0;
	ten.Nums[1] = 1;
	while (!(Y.decimal_pos == 0 && X.decimal_pos == 0))
	{
		X *= ten;
		Y *= ten;
	}
	//X.decimal_pos = 0;
	HugeReal R;
	R = NULLHI();
	HugeReal A = Y;
	A.isNeg = false;
	HugeReal B = X;
	B.isNeg = false;
	HugeReal TR = A;
	HugeReal c = identity();
	if (X >= Y)
	{
		while ((B > Zero))
		{
			HugeReal temp = TR + TR;
			while (temp <= B)
			{
				TR += TR;
				c += c;
				temp = TR + TR;
			}
			B -= TR;
			R += c;
			if (B < A)
			{
				break;
			}
			TR = A;
			c = identity();

		}
	}

	HugeReal Rem = B;
	Rem.isNeg = false;

	int addZeros = 1;
	HugeReal R2;
	R2 = NULLHI();
	HugeReal A2 = Y;
	A2.isNeg = false;
	HugeReal B2 = Rem;
	B2.isNeg = false;
	HugeReal TR2 = A2;
	c = identity();
	for (int i = 0; i < 20; i++)
	{
		B2 *= ten;
		if (B2 < A2)
		{
			addZeros++;
		}
	}
	while ((B2 > Zero))
	{
		HugeReal temp = TR2 + TR2;
		while (temp <= B2)
		{
			TR2 += TR2;
			c += c;
			temp = TR2 + TR2;
		}
		B2 -= TR2;
		R2 += c;
		if (B2 < A2)
		{
			break;
		}
		TR2 = A2;
		c = identity();

	}
	int R3_Size = R2.Size + addZeros;
	int R3_dp = R2.Size + addZeros - 1;
	HugeReal R3(R3_Size,R3_dp);
	for (int i = 0; i < R2.Size; i++)
	{
		R3.Nums[i] = R2.Nums[i];
	}
	R3.shrink();
	Ans = R + R3;
	if (this->isNeg == I2.isNeg)
	{
		Ans.isNeg = false;
	}
	else
	{
		Ans.isNeg = true;
	}
	Ans.shrink();
	return Ans;

}


const HugeReal& HugeReal::operator /=(const HugeReal& I2)
{
	*this = *this / I2;
	return *this;
}
HugeReal HugeReal::operator %(const HugeReal& I2)const
{
	HugeReal Zero = NULLHI();
	HugeReal One = identity();
	HugeReal X = (*this);
	X.isNeg = false;
	HugeReal Y = I2;
	Y.isNeg = false;
	HugeReal ten(2, 0);
	ten.Nums[0] = 0;
	ten.Nums[1] = 1;
	while (Y.decimal_pos != 0)
	{
		X *= ten;
		Y *= ten;
	}
	int dpi = X.decimal_pos;
	X.decimal_pos = 0;

	HugeReal R;
	R = NULLHI();
	HugeReal A = Y;
	A.isNeg = false;
	HugeReal B = X;
	B.isNeg = false;
	HugeReal TR = A;
	HugeReal c = identity();
	if (X > Y)
	{
		while ((B > Zero))
		{
			HugeReal temp = TR + TR;
			while (temp <= B)
			{
				TR += TR;
				c += c;
				temp = TR + TR;
			}
			B -= TR;
			R += c;
			//if (B < I2)
			if (B < A)
			{
				break;
			}
			TR = A;
			c = identity();

		}
	}
	HugeReal Rem = B;
	Rem.isNeg = false;

	return Rem;
}
const HugeReal& HugeReal::operator %=(const HugeReal& I2)
{
	*this = *this % I2;
	return *this;
}
HugeReal::~HugeReal()
{
	delete[]this->Nums;
}