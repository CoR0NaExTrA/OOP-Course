#define CATCH_CONFIG_MAIN
#include "../../../Catch/catch.hpp"
#include "../ParseExpression/ParseExpression.h"
#include <sstream>

TEST_CASE("Basic operations") {
    std::istringstream input1("(+ 7)");
    REQUIRE(Evaluate(input1) == 7);

    std::istringstream input2("(* 8)");
    REQUIRE(Evaluate(input2) == 8);
}

TEST_CASE("Addition and multiplication") {
    std::istringstream input3("(+ 2 3)");
    REQUIRE(Evaluate(input3) == 5);

    std::istringstream input4("(* 2 4)");
    REQUIRE(Evaluate(input4) == 8);
}

TEST_CASE("Nested expressions") {
    std::istringstream input5("(+ (* 2 3) (* 3 4))");
    REQUIRE(Evaluate(input5) == 18);

    std::istringstream input6("(* (+ 1 2) (+ 3 1))");
    REQUIRE(Evaluate(input6) == 12);
}

TEST_CASE("Invalid expressions") {
    std::istringstream input7("(+)");
    REQUIRE_THROWS_AS(Evaluate(input7), std::runtime_error);

    std::istringstream input8("(+ 5 a)");
    REQUIRE_THROWS_AS(Evaluate(input8), std::runtime_error);
}
