#include "option.h"
#include "gtest/gtest.h"
#include <memory>
using namespace argparse;

// Holds an option and the expected test result
namespace {
    struct Testcase {
        const Option option;
        const bool expected;
    };
}

TEST(OptionTest, ValidateOption) {
    const std::vector<::Testcase> test_cases = {
        // No flag
        {{"opt0", "", 0, "", has_value::none}, false},
        // No name
        {{"", "no name", 0, "no", has_value::none}, false},
        // No value
        {{"opt1", "", 'f', "flag", has_value::none}, true},
        {{"opt2", "", 0, "long", has_value::none}, true},
        {{"opt2", "", 'h', "hello", has_value::none}, true},
        // Required value
        {{"opt3", "", 'a', "" , has_value::required}, true},
        {{"opt4", "", 0, "also-a", has_value::required}, true},
        {{"opt5", "", 'b', "sill-b", has_value::required}, true},
        // Optional value
        {{"opt6", "", 'o', "", has_value::optional}, false},
        {{"opt7", "", 0, "opt", has_value::optional}, true},
        {{"opt7", "", 'w', "world", has_value::optional}, false},
        // Special characters
        {{"opt8", "", '$', "", has_value::none}, false},
        {{"opt8", "", 0, "@fl~ag%", has_value::none}, false},
        {{"opt8", "", 0, "under_score", has_value::none}, false}
    };
    for (const ::Testcase &test_case : test_cases) {
        EXPECT_EQ(validate_option(test_case.option), test_case.expected);
    }
}

TEST(OptionTest, ContainsOption) {
    const std::vector<Option> options = {
        Option{.name = "opt_a", .flag = 'a'},
        Option{.name = "opt_b", .flag = 'b'},
        Option{.name = "opt_c", .flag = 'c'},
        Option{.name = "opt_1", .flag = '1'},
        Option{.name = "opt_2", .flag = '2'},
        Option{.name = "opt_3", .flag = '3'}
    };
    const std::vector<::Testcase> test_cases = {
        {Option{.name = "opt_d", .flag = 'd'}, false},
        {Option{.name = "opt_a", .flag = 'a'}, true},
        {Option{.name = "opt_4", .flag = '4'}, false},
        {Option{.name = "opt_2", .flag = '2'}, true},
    };
    for (const ::Testcase& test_case : test_cases) {
        ASSERT_EQ(contains_option(options, test_case.option), test_case.expected);
    }
}
