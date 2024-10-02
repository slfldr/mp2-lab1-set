// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len >= 0)
    {
        BitLen = len;
        MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
        pMem = new TELEM[MemLen];

        std::fill(pMem, pMem + MemLen, 0);
    }
    else
    {
        throw std::invalid_argument("Length must be positive!");
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];

    std::copy(bf.pMem, bf.pMem + MemLen, pMem);
}

TBitField::~TBitField()
{
    delete[] pMem;
    
    pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n % (sizeof(TELEM) * 8));
}

// Доступ к битам битового поля
int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= 0 && n < BitLen)
    {
        pMem[GetMemIndex(n)] |= GetMemMask(n);
    }
    else
    {
        throw std::out_of_range("Bit index out of range!");
    }
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n >= 0 && n < BitLen)
    {
        pMem[GetMemIndex(n)] &= ~GetMemMask(n);
    }
    else
    {
        throw std::out_of_range("Bit index out of range!");
    }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= 0 && n < BitLen)
    {
        return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
    }
    else
    {
        throw std::out_of_range("Bit index out of range!");
    }
}

// Битовые операции
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf)
    {
        delete[] pMem;

        pMem = nullptr;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];

        std::copy(bf.pMem, bf.pMem + bf.MemLen, pMem);
    }
    else
    {
        return *this;
    }
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen == bf.BitLen)
    {
        for (int i = 0; i < MemLen; i++)
        {
            if (pMem[i] != bf.pMem[i])
            {
                return 0;
            }
        }

        return 1;
    }
    else
    {
        return 0;
    }
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int len = std::max(BitLen, bf.BitLen);
    
    TBitField result(len);

    int minMemLen = std::min(MemLen, bf.MemLen);

    for (int i = 0; i < minMemLen; i++)
    {
        result.pMem[i] = pMem[i] | bf.pMem[i];
    }

    if (MemLen > minMemLen)
    {
        std::copy(pMem + minMemLen, pMem + MemLen, result.pMem + minMemLen);
    }
    else if (bf.MemLen > minMemLen)
    {
        std::copy(bf.pMem + minMemLen, bf.pMem + bf.MemLen, result.pMem + minMemLen);
    }
    
    int bitsInLastElem = BitLen % (sizeof(TELEM) * 8);

    if (bitsInLastElem != 0)
    {
        result.pMem[MemLen - 1] &= ((1 << bitsInLastElem) - 1);
    }

    return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int len = std::max(BitLen, bf.BitLen);

    TBitField result(len);

    int minMemLen = std::min(MemLen, bf.MemLen);
    
    for (int i = 0; i < minMemLen; i++)
    {
        result.pMem[i] = pMem[i] & bf.pMem[i];
    }

    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(BitLen);

    for (int i = 0; i < MemLen; i++)
    {
        result.pMem[i] = ~pMem[i];
    }

    int bitsInLastElem = BitLen % (sizeof(TELEM) * 8);

    if (bitsInLastElem != 0)
    {
        result.pMem[MemLen - 1] &= ((1 << bitsInLastElem) - 1);
    }

    return result;
}

// Ввод/вывод
istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int len;

    istr >> len;

    TBitField temp(len);

    for (int i = 0; i < len; i++)
    {
        char bit;
    
        istr >> bit;

        if (bit == '1')
        {
            temp.SetBit(i);
        }
    }

    bf = temp;

    return istr;
}
ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    ostr << bf.BitLen << '\n';

    for (int i = 0; i < bf.BitLen; i++)
    {
        if (bf.GetBit(i))
        {
            ostr << '1';
        }
        else
        {
            ostr << '0';
        }
    }

    return ostr;
}