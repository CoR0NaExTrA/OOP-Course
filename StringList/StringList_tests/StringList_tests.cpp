#define CATCH_CONFIG_MAIN
#include "../../../Catch/catch.hpp"
#include "../StringList/CStringList.h"

TEST_CASE("CMyList<std::string> supports string operations") {
    CStringList list;

    list.PushBack("alpha");
    list.PushBack("beta");
    list.PushFront("zero");

    REQUIRE(list.GetSize() == 3);

    auto it = list.begin();
    REQUIRE(*it++ == "zero");
    REQUIRE(*it++ == "alpha");
    REQUIRE(*it++ == "beta");

    SECTION("Insert and Erase with strings") {
        auto middle = list.begin();
        ++middle;
        list.Insert(middle, "inserted");

        std::vector<std::string> expected = { "zero", "inserted", "alpha", "beta" };
        size_t i = 0;
        for (auto& val : list) {
            REQUIRE(val == expected[i++]);
        }

        list.Erase(++list.begin());
        expected = { "zero", "alpha", "beta" };
        i = 0;
        for (auto& val : list) {
            REQUIRE(val == expected[i++]);
        }
    }

    SECTION("Clearing string list") {
        list.Clear();
        REQUIRE(list.GetSize() == 0);
        REQUIRE(list.begin() == list.end());

        list.Clear();
        REQUIRE(list.IsEmpty());
    }

    SECTION("Copy and move with string list") {
        CStringList copy(list);
        REQUIRE(copy.GetSize() == list.GetSize());

        auto it1 = list.begin();
        auto it2 = copy.begin();
        while (it1 != list.end()) {
            REQUIRE(*it1++ == *it2++);
        }

        CStringList moved = std::move(copy);
        REQUIRE(moved.GetSize() == 3);
    }

    SECTION("Reverse iteration") {
        std::vector<std::string> expected = { "beta", "alpha", "zero" };
        size_t i = 0;
        for (auto rit = list.rbegin(); rit != list.rend(); ++rit) {
            REQUIRE(*rit == expected[i++]);
        }
    }

    SECTION("Erasing all elements one by one") {
        while (!list.IsEmpty()) {
            list.Erase(list.begin());
        }
        REQUIRE(list.GetSize() == 0);
        REQUIRE(list.begin() == list.end());
    }

    SECTION("PushFront and PushBack combination") {
        CStringList l;
        l.PushFront("1");
        l.PushBack("2");
        l.PushFront("0");

        std::vector<std::string> expected = { "0", "1", "2" };
        size_t i = 0;
        for (auto& val : l) {
            REQUIRE(val == expected[i++]);
        }
    }

    SECTION("Insert at end") {
        list.Insert(list.end(), "omega");
        REQUIRE(*(std::prev(list.end())) == "omega");
    }

    SECTION("Insert at begin") {
        list.Insert(list.begin(), "start");
        REQUIRE(*list.begin() == "start");
    }

    SECTION("Erase begin and end - manual iteration") {
        list.Erase(list.begin());
        auto it = list.begin();
        REQUIRE(*it == "alpha");

        list.Erase(std::prev(list.end()));
        REQUIRE(list.GetSize() == 1);
        REQUIRE(*list.begin() == "alpha");
    }

    SECTION("Self assignment should not corrupt list") {
        list = list;
        REQUIRE(list.GetSize() == 3);
        std::vector<std::string> expected = { "zero", "alpha", "beta" };
        size_t i = 0;
        for (auto& val : list) {
            REQUIRE(val == expected[i++]);
        }
    }
}
