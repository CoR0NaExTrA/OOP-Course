#define CATCH_CONFIG_MAIN
#include "../../../Catch/catch.hpp"
#include "../Calculator/Calculator.h"

#include <sstream>
#include <string>

TEST_CASE("Declare and assign variables") {
    Calculator calc;

    SECTION("Declare variable") {
        calc.ExecuteCommand("var x");
        std::ostringstream out;
        std::streambuf* old = std::cout.rdbuf(out.rdbuf());
        calc.ExecuteCommand("print x");
        std::cout.rdbuf(old);
        REQUIRE(out.str() == "nan\n");
    }

    SECTION("Assign value to variable") {
        calc.ExecuteCommand("var x");
        calc.ExecuteCommand("let x = 3.14");
        std::ostringstream out;
        std::streambuf* old = std::cout.rdbuf(out.rdbuf());
        calc.ExecuteCommand("print x");
        std::cout.rdbuf(old);
        REQUIRE(out.str() == "3.14\n");
    }

    SECTION("Assign value from another variable") {
        calc.ExecuteCommand("var a");
        calc.ExecuteCommand("var b");
        calc.ExecuteCommand("let a = 10");
        calc.ExecuteCommand("let b = a");
        std::ostringstream out;
        std::streambuf* old = std::cout.rdbuf(out.rdbuf());
        calc.ExecuteCommand("print b");
        std::cout.rdbuf(old);
        REQUIRE(out.str() == "10.00\n");
    }
}

TEST_CASE("Define functions and evaluate") {
    Calculator calc;

    SECTION("Define function from variable") {
        calc.ExecuteCommand("var x");
        calc.ExecuteCommand("let x = 2");
        calc.ExecuteCommand("fn doubleX = x + x");
        std::ostringstream out;
        std::streambuf* old = std::cout.rdbuf(out.rdbuf());
        calc.ExecuteCommand("print doubleX");
        std::cout.rdbuf(old);
        REQUIRE(out.str() == "4.00\n");
    }

    SECTION("Handle whitespace in function definition") {
        calc.ExecuteCommand("var x");
        calc.ExecuteCommand("let x = 5");
        calc.ExecuteCommand("fn incX = x+1");
        std::ostringstream out;
        std::streambuf* old = std::cout.rdbuf(out.rdbuf());
        calc.ExecuteCommand("print incX");
        std::cout.rdbuf(old);
        REQUIRE(out.str() == "6.00\n");
    }
}

TEST_CASE("Print all variables and functions") {
    Calculator calc;
    calc.ExecuteCommand("var x");
    calc.ExecuteCommand("let x = 1.5");
    calc.ExecuteCommand("fn fx = x + x");

    std::ostringstream out;
    std::streambuf* old = std::cout.rdbuf(out.rdbuf());

    calc.ExecuteCommand("printvars");
    calc.ExecuteCommand("printfns");

    std::cout.rdbuf(old);

    std::string output = out.str();
    REQUIRE(output.find("x:1.50") != std::string::npos);
    REQUIRE(output.find("fx:3.00") != std::string::npos);
}

TEST_CASE("Invalid expression")
{
    Calculator calc;

    SECTION("Invalid command declare variable")
    {
        std::ostringstream out;
        std::streambuf* old = std::cout.rdbuf(out.rdbuf());
        calc.ExecuteCommand("var");
        std::cout.rdbuf(old);
        REQUIRE(out.str() == "Invalid usage\n");
    }

    SECTION("Invalid command declare function")
    {
        calc.ExecuteCommand("var x");
        std::ostringstream out;
        std::streambuf* old = std::cout.rdbuf(out.rdbuf());
        calc.ExecuteCommand("fn");
        std::cout.rdbuf(old);
        REQUIRE(out.str() == "Invalid usage\n");
    }

    SECTION("Invalid name variable")
    {
        std::ostringstream out;
        std::streambuf* old = std::cout.rdbuf(out.rdbuf());
        calc.ExecuteCommand("var 1x");
        std::cout.rdbuf(old);
        REQUIRE(out.str() == "Invalid usage\n");
    }

    SECTION("Invalid name function")
    {
        calc.ExecuteCommand("var x");
        std::ostringstream out;
        std::streambuf* old = std::cout.rdbuf(out.rdbuf());
        calc.ExecuteCommand("fn 1x");
        std::cout.rdbuf(old);
        REQUIRE(out.str() == "Invalid usage\n");
    }
}
