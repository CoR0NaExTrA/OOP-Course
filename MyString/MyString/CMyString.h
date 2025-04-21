#pragma once

#include <cstddef>
#include <string>
#include <iostream>

class CMyString
{
public:
    CMyString();
    CMyString(const char* pString);
    CMyString(const char* pString, size_t length);
    CMyString(const std::string& str);
    CMyString(const CMyString& other);
    CMyString(CMyString&& other) noexcept;
    ~CMyString();

    CMyString& operator=(const CMyString& other);
    CMyString& operator=(CMyString&& other) noexcept;

    CMyString operator+(const CMyString& other) const;
    CMyString& operator+=(const CMyString& other);

    bool operator==(const CMyString& other) const;
    bool operator!=(const CMyString& other) const;
    bool operator<(const CMyString& other) const;
    bool operator>(const CMyString& other) const;
    bool operator<=(const CMyString& other) const;
    bool operator>=(const CMyString& other) const;

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const CMyString& str);
    friend std::istream& operator>>(std::istream& is, CMyString& str);

    size_t GetLength() const;
    size_t GetCapacity();
    const char* GetStringData() const;

    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
    void Clear();

private:
    void AllocateAndCopy(const char* pString, size_t length);
    void EnsureCapacity(size_t newLength);

    size_t m_length = 0;
    size_t m_capacity = 0;
    char* m_data = nullptr;
};