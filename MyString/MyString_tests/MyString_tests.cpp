#define CATCH_CONFIG_MAIN
#include "../MyString/CMyString.h"
#include "../../../Catch/catch.hpp"

TEST_CASE("Default constructor creates empty string") {
    CMyString str;
    CHECK(str.GetLength() == 0);
    CHECK(std::string(str.GetStringData()) == "");
}

TEST_CASE("Constructor from C-string copies content") {
    const char* cstr = "Hello";
    CMyString str(cstr);
    CHECK(str.GetLength() == 5);
    CHECK(std::string(str.GetStringData()) == "Hello");
}

TEST_CASE("Constructor from C-string with length") {
    const char* cstr = "HelloWorld";
    CMyString str(cstr, 5);
    CHECK(str.GetLength() == 5);
    CHECK(std::string(str.GetStringData()) == "Hello");
}

TEST_CASE("Constructor from std::string") {
    std::string s = "Hi!";
    CMyString str(s);
    CHECK(str.GetLength() == 3);
    CHECK(std::string(str.GetStringData()) == "Hi!");
}

TEST_CASE("Copy constructor makes deep copy") {
    CMyString str1("CopyMe");
    CMyString str2(str1);
    CHECK(str1 == str2);
    CHECK(&str1 != &str2);
}

TEST_CASE("Move constructor transfers ownership") {
    CMyString str1("MoveMe");
    CMyString str2(std::move(str1));
    CHECK(str2 == CMyString("MoveMe"));
    CHECK(str1.GetLength() == 0);
}

TEST_CASE("Copy assignment works") {
    CMyString str1("Hello");
    CMyString str2;
    str2 = str1;
    CHECK(str2 == str1);
}

TEST_CASE("Move assignment works") {
    CMyString str1("Goodbye");
    CMyString str2;
    str2 = std::move(str1);
    CHECK(str2 == CMyString("Goodbye"));
    CHECK(str1.GetLength() == 0);
}

TEST_CASE("Operator + returns concatenated string") {
    CMyString str1("Hello");
    CMyString str2("World");
    CMyString str3 = str1 + str2;
    CHECK(str3 == CMyString("HelloWorld"));
}

TEST_CASE("Operator += appends string") {
    CMyString str("Hello");
    str += CMyString("World");
    CHECK(str == CMyString("HelloWorld"));
}

TEST_CASE("Comparison operators work correctly") {
    CMyString a("abc");
    CMyString b("abd");
    CHECK(a < b);
    CHECK(b > a);
    CHECK(a != b);
    CHECK(a == CMyString("abc"));
    CHECK(a <= CMyString("abc"));
    CHECK(b >= CMyString("abd"));
}

TEST_CASE("SubString returns valid substring") {
    CMyString str("HelloWorld");
    CMyString sub = str.SubString(5, 5);
    CHECK(sub == CMyString("World"));
}

TEST_CASE("Clear empties the string") {
    CMyString str("NotEmpty");
    str.Clear();
    CHECK(str.GetLength() == 0);
    CHECK(std::string(str.GetStringData()) == "");
}

TEST_CASE("Indexing works and throws on out-of-bounds") {
    CMyString str("abc");
    CHECK(str[0] == 'a');
    CHECK(str[1] == 'b');
    CHECK(str[2] == 'c');
    CHECK_THROWS_AS(str[3], std::out_of_range);
}
