#include "CMyString.h"
#include <cstring>
#include <stdexcept>
#include <algorithm>

namespace
{
    char g_empty = '\0';
}

CMyString::CMyString()
    : m_length(0), m_capacity(0), m_data(&g_empty)
{
}

CMyString::CMyString(const char* pString)
    : CMyString(pString, std::strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
{
    AllocateAndCopy(pString, length);
}

CMyString::CMyString(const std::string& str)
    : CMyString(str.c_str(), str.length())
{
}

CMyString::CMyString(const CMyString& other)
{
    AllocateAndCopy(other.m_data, other.m_length);
}

CMyString::CMyString(CMyString&& other) noexcept
    : m_data(other.m_data), m_length(other.m_length), m_capacity(other.m_capacity)
{
    other.m_data = &g_empty;
    other.m_length = 0;
    other.m_capacity = 0;
}

CMyString::~CMyString()
{
    if (m_data != &g_empty)
    {
        delete[] m_data;
    }
}

CMyString& CMyString::operator=(const CMyString& other)
{
    if (this != &other)
    {
        AllocateAndCopy(other.m_data, other.m_length);
    }
    return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
    if (this != &other)
    {
        if (m_data != &g_empty)
        {
            delete[] m_data;
        }
        m_data = other.m_data;
        m_length = other.m_length;
        m_capacity = other.m_capacity;

        other.m_data = &g_empty;
        other.m_length = 0;
        other.m_capacity = 0;
    }
    return *this;
}

CMyString CMyString::operator+(const CMyString& other) const
{
    CMyString result;
    result.EnsureCapacity(m_length + other.m_length);
    std::copy(m_data, m_data + m_length, result.m_data);
    std::copy(other.m_data, other.m_data + other.m_length, result.m_data + m_length);
    result.m_length = m_length + other.m_length;
    result.m_data[result.m_length] = '\0';
    return result;
}

CMyString& CMyString::operator+=(const CMyString& other)
{
    EnsureCapacity(m_length + other.m_length);
    std::copy(other.m_data, other.m_data + other.m_length, m_data + m_length);
    m_length += other.m_length;
    m_data[m_length] = '\0';
    return *this;
}

bool CMyString::operator==(const CMyString& other) const
{
    return m_length == other.m_length && std::memcmp(m_data, other.m_data, m_length) == 0;
}

bool CMyString::operator!=(const CMyString& other) const
{
    return !(*this == other);
}

bool CMyString::operator<(const CMyString& other) const
{
    size_t minLen = std::min(m_length, other.m_length);
    int cmp = std::memcmp(m_data, other.m_data, minLen);
    return cmp < 0 || (cmp == 0 && m_length < other.m_length);
}

bool CMyString::operator>(const CMyString& other) const
{
    return other < *this;
}

bool CMyString::operator<=(const CMyString& other) const
{
    return !(other < *this);
}

bool CMyString::operator>=(const CMyString& other) const
{
    return !(*this < other);
}

char& CMyString::operator[](size_t index)
{
    if (index >= m_length)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return m_data[index];
}

const char& CMyString::operator[](size_t index) const
{
    if (index >= m_length)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return m_data[index];
}

std::ostream& operator<<(std::ostream& os, const CMyString& str)
{
    return os.write(str.GetStringData(), str.GetLength());
}

std::istream& operator>>(std::istream& is, CMyString& str)
{
    std::string temp;
    is >> temp;
    str = CMyString(temp);
    return is;
}

size_t CMyString::GetLength() const
{
    return m_length;
}

size_t CMyString::GetCapacity()
{
    return m_capacity;
}

const char* CMyString::GetStringData() const
{
    return m_data;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
    if (start > m_length)
        throw std::out_of_range("Start index is out of range");

    size_t actualLength = std::min(length, m_length - start);
    return CMyString(m_data + start, actualLength);
}

void CMyString::Clear()
{
    m_length = 0;
    if (m_data != nullptr)
    {
        m_data[0] = '\0';
    }
}

void CMyString::AllocateAndCopy(const char* pString, size_t length)
{
    if (m_data != &g_empty)
    {
        delete[] m_data;
    }

    m_capacity = length;
    m_length = length;
    m_data = new char[m_capacity + 1];
    std::copy(pString, pString + length, m_data);
    m_data[length] = '\0';
}

void CMyString::EnsureCapacity(size_t newLength)
{
    if (newLength <= m_capacity)
        return;

    size_t newCapacity = std::max(newLength, m_capacity * 2);
    char* newData = new char[newCapacity + 1];
    std::copy(m_data, m_data + m_length, newData);
    newData[m_length] = '\0';

    if (m_data != &g_empty)
    {
        delete[] m_data;
    }

    m_data = newData;
    m_capacity = newCapacity;
}
