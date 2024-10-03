// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include <algorithm>
#include <stdexcept>
#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// Конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// Конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem > 0 || Elem < MaxPower)
    {
        return BitField.GetBit(Elem);
    }
    else
    {
        throw out_of_range("Element out of range!");
    }
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem > 0 || Elem < MaxPower)
    {
        BitField.SetBit(Elem);
    }
    else
    {
        throw out_of_range("Element out of range!");
    }
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem > 0 || Elem < MaxPower)
    {
        BitField.ClrBit(Elem);
    }
    else
    {
        throw out_of_range("Element out of range!");
    }
}

// Теоретико-множественные операции
TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this != &s)
    {
        BitField = s.BitField;
        MaxPower = s.MaxPower;
    }
    else
    {
        return *this;
    }
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int newMaxPower = max(MaxPower, s.MaxPower);

    TSet result(newMaxPower);

    for (int i = 0; i < MaxPower; i++)
    {
        if (BitField.GetBit(i))
        {
            result.InsElem(i);
        }
    }

    for (int i = 0; i < s.MaxPower; i++)
    {
        if (s.BitField.GetBit(i))
        {
            result.InsElem(i);
        }
    }

    return result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res = *this;

    res.InsElem(Elem);

    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet res = *this;

    res.DelElem(Elem);

    return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
    return TSet(~BitField);
}

// Ввод/вывод
istream &operator>>(istream &istr, TSet &s) // ввод
{
    int elem;

    while (istr >> elem)
    {
        s.InsElem(elem);
    }

    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << "{ ";

    for (int i = 0; i < s.GetMaxPower(); i++)
    {
        if (s.IsMember(i))
        {
            ostr << i << " ";
        }
    }

    ostr << "}";

    return ostr;
}