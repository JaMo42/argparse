#include "arguments.h"
#include "gtest/gtest.h"
#include <memory>
using namespace argparse;

namespace {
    struct Testcase {
        const std::string_view name;
        const bool expected;
    };
}

struct ArgumentsTest : public ::testing::Test {
    std::unique_ptr<Arguments> args;

    ArgumentsTest() {
        args = std::make_unique<Arguments>();
        auto &opts = args->options;
        opts["no_value"] = {1, std::forward_list<std::string_view>()};
        opts["single_value"] = {1, {"3.141"}};
        opts["multiple_values"] = {4, {"Hello", ",", "World", "!"}};
    }

};

TEST_F(ArgumentsTest, HasOption) {
    const std::vector<::Testcase> test_cases = {
        {"non_existent", false},
        {"no_value", true},
        {"even_less_existent", false},
        {"multiple_values", true}
    };
    for (const ::Testcase &test_case : test_cases) {
        ASSERT_EQ(args->has_option(test_case.name), test_case.expected);
    }
}

TEST_F(ArgumentsTest, OptionHasArg) {
    const std::vector<::Testcase> test_cases = {
        {"non_existent", false},
        {"no_value", false},
        {"even_less_existent", false},
        {"single_value", true},
        {"multiple_values", true}
    };
    for (const ::Testcase &test_case : test_cases) {
        ASSERT_EQ(args->option_has_arg(test_case.name), test_case.expected);
    }
}

TEST_F(ArgumentsTest, NextArg) {
    std::string out;
    ASSERT_FALSE(args->next_arg("non_existent", out));
    ASSERT_FALSE(args->next_arg("even_less_existent", out));
    ASSERT_FALSE(args->next_arg("no_value", out));
    ASSERT_TRUE(args->next_arg("single_value", out));
    ASSERT_TRUE(out == "3.141");
    ASSERT_TRUE(args->next_arg("multiple_values", out));
    ASSERT_TRUE(out == "Hello");
    ASSERT_TRUE(args->next_arg("multiple_values", out));
    ASSERT_TRUE(out == ",");
    ASSERT_TRUE(args->next_arg("multiple_values", out));
    ASSERT_TRUE(out == "World");
    ASSERT_TRUE(args->next_arg("multiple_values", out));
    ASSERT_TRUE(out == "!");
    ASSERT_FALSE(args->next_arg("multiple_values", out));
}
