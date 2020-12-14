#pragma once

#ifndef TVector_H

#define TVector_H

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;

template <class Type>

class TVector

{

protected:

	Type* pVec;

	int Size;

	int StartIndex;

public:

	TVector(int s = 10, int si = 0);

	TVector(const TVector& v);

	int GetSize() { return Size; };

	int GetStartIndex() { return StartIndex; };

	Type& GetValue(int pos);

	Type& operator[](int pos);

	bool operator==(const TVector& v);

	bool operator!=(const TVector& v);

	TVector& operator=(const TVector& v);

	TVector operator+(const Type& val);

	TVector operator-(const Type& val);

	TVector operator*(const Type& val);

	TVector operator+(const TVector& v);

	TVector operator-(const TVector& v);

	Type operator*(const TVector& v);

	friend istream& operator>>(istream& in, TVector& v)

	{

		for (int i = 0; i < v.Size; i++)

			in >> v.pVec[i];

		return in;

	}

	friend ostream& operator<<(ostream& out, TVector& v)

	{

		for (int i = 0; i < v.Size; i++)

			out << v.pVec[i] << " ";

		return out;

	}

};

template <class Type>

TVector<Type>::TVector(int s, int si)

{

	//if (s > MAX_VECTOR_SIZE || s<0 || si>s || si < 0)

	//{ throw out_of_range("Given size(s) must be less than 100000000 and greater than 0"); }

	Size = s;

	StartIndex = si;

	pVec = new Type[Size];

	for (int i = 0; i < Size; i++)

		pVec[i] = 0;

}

template <class Type>

TVector<Type>::TVector(const TVector& v)

{

	Size = v.Size;

	StartIndex = v.StartIndex;

	pVec = new Type[Size];

	for (int i = 0; i < Size; i++)

		pVec[i] = v.pVec[i];

}

template<class Type>

Type& TVector<Type>::GetValue(int pos)

{

	//if (pos > Size || pos < StartIndex) throw out_of_range("You cannot reach this element. No such element. Out of range.");

	return pVec[pos - StartIndex];

}

template<class Type>

Type& TVector<Type>::operator[](int pos)

{

	return pVec[pos - StartIndex];

}

template<class Type>

bool TVector<Type>::operator==(TVector const& v)

{

	if (Size != v.Size || StartIndex != v.StartIndex)

		return false;

	for (int i = 0; i < v.Size; i++)

	{

		if (v.pVec[i] != pVec[i])

			return false;

	}

	return true;

}

template<class Type>

bool TVector<Type>::operator!=(TVector const& v)

{

	if (Size != v.Size || StartIndex != v.StartIndex)

		return true;

	for (int i = 0; i < v.Size; i++)

	{

		if (v.pVec[i] != pVec[i])
			return true;

	}

	return false;

}

template<class Type>

TVector<Type>& TVector<Type>::operator=(const TVector& v)

{

	if (this != &v)

	{

		if (Size != v.Size)

		{

			delete[] pVec;

			pVec = new Type[v.Size];

		}

		Size = v.Size;

		StartIndex = v.StartIndex;

		for (int i = 0; i < Size; i++)

		{

			pVec[i] = v.pVec[i];

		}

	}

	return *this;

}

template<class Type>

TVector<Type> TVector<Type>::operator+(Type const& val)

{

	TVector<Type> tmp(*this);

	for (int i = 0; i < this->Size; i++)

		tmp.pVec[i] += val;

	return tmp;

}

template<class Type>

TVector<Type> TVector<Type>::operator-(Type const& val)

{

	TVector<Type> tmp(*this);

	for (int i = 0; i < this->Size; i++)

		tmp.pVec[i] -= val;

	return tmp;

}

template<class Type>

TVector<Type> TVector<Type>::operator*(const Type& val)

{

	TVector<Type> tmp(*this);

	for (int i = 0; i < this->Size; i++)

		tmp.pVec[i] *= val;

	return tmp;

}

template<class Type>

TVector<Type> TVector<Type>:: operator+(const TVector& v)

{

	TVector<Type> tmp(*this);

	if (v.Size != tmp.Size || v.StartIndex != tmp.StartIndex) throw length_error("Vectors' sizes must be equal");

	for (int i = 0; i < tmp.Size; i++)

		tmp.pVec[i] = tmp.pVec[i] + v.pVec[i];

	return tmp;

}

template<class Type>

TVector<Type> TVector<Type>:: operator-(const TVector& v)

{

	TVector<Type> tmp(*this);

	if (v.Size != tmp.Size || v.StartIndex != tmp.StartIndex) throw length_error("Vectors' sizes must be equal");

	for (int i = 0; i < tmp.Size; i++)

		tmp.pVec[i] = tmp.pVec[i] - v.pVec[i];

	return tmp;

}

template<class Type>

Type TVector<Type>::operator*(const TVector& v)

{

	Type tmp = 0;

	if (v.Size != Size || v.StartIndex != StartIndex) throw length_error("Vectors' sizes must be equal");

	for (int i = 0; i < Size; i++)

		tmp = tmp + (this->pVec[i] * v.pVec[i]);

	return tmp;

}

#endif

#pragma once

#ifndef TMatrix_H

#define TMatrix_H

#include "TVector.h"

#include <iostream>

const int MAX_MATRIX_SIZE = 10000;

template<class Type>

class TMatrix : public TVector<TVector<Type> >

{

public:

	TMatrix(int s = 10);

	TMatrix(const TMatrix& mt);

	TMatrix(const TVector<TVector<Type> >& mt);

	bool operator==(const TMatrix& mt);

	TMatrix& operator=(const TMatrix& mt);

	TMatrix operator+(const TMatrix& mt);

	TMatrix operator-(const TMatrix& mt);

	TMatrix operator*(const TMatrix& mt);

	friend istream& operator>>(istream& in, TMatrix& mt)

	{

		for (int i = 0; i < mt.Size; i++)

			in >> mt.pVec[i];

		return in;

	}

	friend ostream& operator<<(ostream& out, TMatrix& mt)

	{

		for (int i = 0; i < mt.Size; i++)

			out << mt.pVec[i] << "\n";

		return out;

	}

};

template<class Type>

TMatrix<Type>::TMatrix(int s) : TVector<TVector<Type> >(s)

{

	for (int i = 0; i < s; i++)

		this->pVec[i] = TVector<Type>(s - i, i);

}

template<class Type>

TMatrix<Type>::TMatrix(const TMatrix<Type>& mt) :TVector<TVector<Type> >(mt) {}

template<class Type>

TMatrix<Type>::TMatrix(const TVector<TVector<Type> >& mt) : TVector<TVector<Type> >(mt)

{

	for (int i = 0; i < this->GetSize(); i++)

	{

		if (this->pVec[i].GetSize() != this->GetSize() - i)

			throw std::out_of_range("This is not a triangle matrix");

	}

}

template<class Type>

TMatrix<Type>& TMatrix<Type>:: operator=(const TMatrix& mt)

{

	if (this != &mt)

	{

		if (this->Size != mt.Size)

		{

			delete[] this->pVec;

			this->pVec = new TVector<Type>[mt.Size];

		}

		this->Size = mt.Size;

		this->StartIndex = mt.StartIndex;

		for (int i = 0; i < this->Size; i++)

		{

			this->pVec[i] = mt.pVec[i];

		}

	}

	return *this;

}

template<class Type>

bool TMatrix<Type>::operator==(TMatrix const& mt)

{

	if (this->Size != mt.Size || this->StartIndex != mt.StartIndex)

		return false;

	for (int i = 0; i < mt.Size; i++)

	{

		if (mt.pVec[i] != this->pVec[i])

			return false;

	}

	return true;

}

template<class Type>

TMatrix<Type> TMatrix<Type>::operator+(const TMatrix& mt)

{

	TMatrix tmp(*this);

	//if (mt.Size != tmp.Size || mt.StartIndex != tmp.StartIndex) throw length_error("Matrixes' sizes must be equal");

	for (int i = 0; i < tmp.Size; i++)

		tmp.pVec[i] = tmp.pVec[i] + mt.pVec[i];

	return tmp;

}

template<class Type>

TMatrix<Type> TMatrix<Type>::operator-(const TMatrix& mt)

{

	TMatrix tmp(*this);

	//if (mt.Size != tmp.Size || mt.StartIndex != tmp.StartIndex) throw length_error("Matrixes' sizes must be equal");

	for (int i = 0; i < tmp.Size; i++)

		tmp.pVec[i] = tmp.pVec[i] - mt.pVec[i];

	return tmp;

}

template<class Type>

TMatrix<Type> TMatrix<Type>::operator*(const TMatrix& mt)

{

	//if (mt.Size != this->Size || mt.StartIndex != this->StartIndex) throw length_error("Matrixes' sizes must be equal");

	TMatrix<Type> tmp(this->Size);

	for (int i = 0; i < this->Size; i++)

		for (int j = 0; j < this->Size / 2; j++) //size/2

		{
			Type tp = Type();

			for (int k = i; k <= j; ++k)

			{

				tp = tp + (this->pVec[i][k] * mt.pVec[k][j]);

			}

			tmp.pVec[i][j] = tp;

		}

	return tmp;

}

#endif