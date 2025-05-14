#define CATCH_CONFIG_MAIN
#include "../../../Catch/catch.hpp"
#include "../MyList/CMyList.h"

TEST_CASE("CMyList<int> basic operations") {
    CMyList<int> list;

    SECTION("Initially list is empty") {
        REQUIRE(list.GetSize() == 0);
        REQUIRE(list.IsEmpty());
    }

    SECTION("PushFront and PushBack work correctly") {
        list.PushFront(1);
        list.PushBack(2);
        list.PushFront(0);

        REQUIRE(list.GetSize() == 3);

        auto it = list.begin();
        REQUIRE(*it++ == 0);
        REQUIRE(*it++ == 1);
        REQUIRE(*it++ == 2);
        REQUIRE(it == list.end());
    }

    SECTION("Insert at begin and end") {
        list.PushBack(1);
        auto it = list.begin();
        list.Insert(it, 0);
        list.Insert(list.end(), 2);

        REQUIRE(list.GetSize() == 3);

        std::vector<int> expected = { 0, 1, 2 };
        size_t i = 0;
        for (int value : list) {
            REQUIRE(value == expected[i++]);
        }
    }

    SECTION("Erase works correctly") {
        list.PushBack(10);
        list.PushBack(20);
        list.PushBack(30);

        auto it = list.begin();
        ++it;
        list.Erase(it);

        std::vector<int> expected = { 10, 30 };
        size_t i = 0;
        for (int value : list) {
            REQUIRE(value == expected[i++]);
        }
        REQUIRE(list.GetSize() == 2);
    }

    SECTION("Clear removes all elements") {
        list.PushBack(1);
        list.PushBack(2);
        list.Clear();

        REQUIRE(list.GetSize() == 0);
        REQUIRE(list.IsEmpty());
        REQUIRE(list.begin() == list.end());
    }

    SECTION("Copy constructor makes deep copy") {
        list.PushBack(1);
        list.PushBack(2);

        CMyList<int> copy(list);
        REQUIRE(copy.GetSize() == 2);

        auto it1 = list.begin();
        auto it2 = copy.begin();
        while (it1 != list.end()) {
            REQUIRE(*it1++ == *it2++);
        }
    }

    SECTION("Move constructor transfers ownership") {
        list.PushBack(42);
        CMyList<int> moved(std::move(list));

        REQUIRE(moved.GetSize() == 1);
        REQUIRE(*moved.begin() == 42);
        REQUIRE(list.IsEmpty());
    }

    SECTION("Copy assignment operator works") {
        list.PushBack(5);
        CMyList<int> copy;
        copy = list;

        REQUIRE(copy.GetSize() == 1);
        REQUIRE(*copy.begin() == 5);
    }

    SECTION("Move assignment operator works") {
        list.PushBack(99);
        CMyList<int> moved;
        moved = std::move(list);

        REQUIRE(moved.GetSize() == 1);
        REQUIRE(*moved.begin() == 99);
        REQUIRE(list.IsEmpty());
    }

    SECTION("Reverse iterators iterate backward") {
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);

        std::vector<int> expected = { 3, 2, 1 };
        size_t i = 0;
        for (auto it = list.rbegin(); it != list.rend(); ++it) {
            REQUIRE(*it == expected[i++]);
        }
    }
}

TEST_CASE("CMyList<std::string> supports string operations") {
    CMyList<std::string> list;

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
    }

    SECTION("Copy and move with string list") {
        CMyList<std::string> copy(list);
        REQUIRE(copy.GetSize() == list.GetSize());

        CMyList<std::string> moved = std::move(copy);
        REQUIRE(moved.GetSize() == 3);
    }
}
