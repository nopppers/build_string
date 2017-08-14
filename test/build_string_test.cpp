#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "build_string.hpp"

using namespace string::build;

TEST_CASE("Basic correctness")
{
    REQUIRE(build_string("test") == "test");
}

TEST_CASE("Basic sizing")
{
    REQUIRE(build_string("test").size() == 4);
}

TEST_CASE("std::string concatenation correctness")
{
    REQUIRE(build_string("test", "test") == "testtest");
}

TEST_CASE("std::string concatenation sizing")
{
    REQUIRE(build_string("test", "test").size() == 8);
}

TEST_CASE("Basic integer")
{
    REQUIRE(build_string(2) == "2");
}

TEST_CASE("Big integer")
{
    REQUIRE(build_string(22222) == "22222");
}

TEST_CASE("Integer sizing")
{
    REQUIRE(build_string(2).size() == 1);
}

TEST_CASE("Big integer sizing")
{
    REQUIRE(build_string(22222).size() == 5);
}

TEST_CASE("Integer concatenation correctness")
{
    REQUIRE(build_string(2, 2) == "22");
}

TEST_CASE("Big integer concatenation")
{
    REQUIRE(build_string(123, 456) == "123456");
}

TEST_CASE("Mixing integers with strings")
{
    REQUIRE(build_string("Max has ", 20, " dogs") == "Max has 20 dogs");
}

TEST_CASE("Character correctness")
{
    REQUIRE(build_string('J', 'a', 'k', 'e') == "Jake");
}

TEST_CASE("Character sizing")
{
    REQUIRE(build_string('K', 'a', 'k', 'e').size() == 4);
}

TEST_CASE("Mixing characters with strings")
{
    REQUIRE(build_string("Jake is ", 'a', " nut") == "Jake is a nut");
}

TEST_CASE("Mixing everything")
{
    REQUIRE(build_string("I have ", 2, ' ', 'a', 'n', 'd', " a half") == "I have 2 and a half");
}

TEST_CASE("StringBuilder default constructor")
{
    REQUIRE(StringBuilder() == "");
}

TEST_CASE("StringBuilder non-default constructor")
{
    REQUIRE(StringBuilder("Jason has ", 2, " sandwiches") == "Jason has 2 sandwiches");
}

TEST_CASE("StringBuilder append single")
{
    StringBuilder b;
    b.append("Dustin has ");
    for (int i = 1; i <= 5; ++i)
    {
        b.append(i);
    }
    b.append(" bananas");
    REQUIRE(b == "Dustin has 12345 bananas");
}

TEST_CASE("StringBuilder append multiple")
{
    StringBuilder b;
    b.append("Max has ");
    for (int i = 1; i <= 5; ++i)
    {
        b.append(i, i*i);
    }
    b.append(" lambdas");
    REQUIRE(b == "Max has 112439416525 lambdas");
}

TEST_CASE("StringBuilder complex")
{
    StringBuilder b("Dustin has ", 9, " tenants, two of whom sing: \n");
    for (int i = 5; i >= 1; --i)
    {
        b.append(i, 
                " DigiPen tears on the wall, ", 
                i, 
                " DigiPen tears, take one down, pass it around, ", 
                i - 1, 
                " DigiPen tears on the wall!\n");
    }

    std::string expected =
        "Dustin has 9 tenants, two of whom sing: \n"
        "5 DigiPen tears on the wall, 5 DigiPen tears, take one down, pass it around, 4 DigiPen tears on the wall!\n"
        "4 DigiPen tears on the wall, 4 DigiPen tears, take one down, pass it around, 3 DigiPen tears on the wall!\n"
        "3 DigiPen tears on the wall, 3 DigiPen tears, take one down, pass it around, 2 DigiPen tears on the wall!\n"
        "2 DigiPen tears on the wall, 2 DigiPen tears, take one down, pass it around, 1 DigiPen tears on the wall!\n"
        "1 DigiPen tears on the wall, 1 DigiPen tears, take one down, pass it around, 0 DigiPen tears on the wall!\n";

    REQUIRE(b == expected);
    REQUIRE(b.size() == expected.size());
}