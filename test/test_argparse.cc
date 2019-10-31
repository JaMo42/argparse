#include "argparse.h"
#include "gtest/gtest.h"
#include <memory>
using namespace argparse;

#define prog_path "/path/to/program/program_name"
#define make_parser std::make_unique<ArgumentParser>
#define add_arg(opt) parser->add_argument(opt); parser_abbr->add_argument(opt)

struct ArgparseTest : public ::testing::Test {
    // Normal parser
    std::unique_ptr<ArgumentParser> parser;
    // Parser with abbreviations enabled
    std::unique_ptr<ArgumentParser> parser_abbr;

    ArgparseTest() {
        // Options
        const std::vector<Option> options = {
            Option{.name = "flag", .flag = 'f', .long_opt = "flag"},
            Option{.name = "input_flag", .flag = 'i'},
            Option{.name = "value_a", .flag = 'a', .value = has_value::required},
            Option{.name = "value_b", .flag = 'b', .value = has_value::required},
            Option{.name = "value_c", .flag = 'c', .value = has_value::required},
            Option{.name = "optional", .long_opt = "opt", .value = has_value::optional},
            Option{.name = "optimization", .flag = 'o'},
            Option{.name = "secret", .long_opt = "secret"},
            Option{.name = "standart", .long_opt = "std", .value = has_value::required},
            Option{.name = "some_name", .flag = 's'}
        };
        // Create argument parsers
        parser = make_parser();
        //parser->option_errors = false;
        parser_abbr = make_parser();
        parser_abbr->allow_abbreviations = true;
        //parser_abbr->option_errors = false;
        // Add arguments
        for (const Option &opt : options) {
            parser->add_argument(opt);
            parser_abbr->add_argument(opt);
        }
    }

};

TEST_F(ArgparseTest, Parameters) {
    const char *argv[] = {prog_path, "-a", "5", "--flag", "Hello, ", "-b", "2", "World!"};
    int argc = 8;
    const Arguments args = parser->parse(argc, argv);
    const std::vector<std::string_view> expected = {"Hello, ", "World!"};
    ASSERT_EQ(args.parameters, expected);
}

TEST_F(ArgparseTest, PosixFlagSingleNoValue) {
    const char *argv[] = {prog_path, "hello", "-i", "world", "-o", "-f"};
    int argc = 7;
    Arguments args = parser->parse(argc, argv);
    ASSERT_EQ(args.count("input_flag"), 1);
    ASSERT_EQ(args.count("optimization"), 1);
    ASSERT_EQ(args.count("flag"), 1);
}

TEST_F(ArgparseTest, PosixFlagSingleValue) {
    const char *argv[] = {prog_path, "salt", "-a", "20", "hello", "-f", "-b", "5", "world", "-a10", "-c"};
    int argc = 11;
    Arguments args = parser->parse(argc, argv);
    ASSERT_EQ(args.count("value_a"), 2);
    ASSERT_EQ(args.count("value_b"), 1);
    ASSERT_EQ(args.count("value_c"), 1);
    std::string out = "<nil>";
    ASSERT_TRUE(args.next_arg("value_a", out));
    ASSERT_EQ(out, "10");
    ASSERT_TRUE(args.next_arg("value_a", out));
    ASSERT_EQ(out, "20");
    ASSERT_FALSE(args.next_arg("value_a", out));

    ASSERT_TRUE(args.next_arg("value_b", out));
    ASSERT_EQ(out, "5");
    ASSERT_FALSE(args.next_arg("value_b", out));
}

TEST_F(ArgparseTest, PosixFlagMultiple) {
    const char *argv[] = {prog_path, "-f", "-f", "-f", "-iii", "-o3"};
    int argc = 6;
    Arguments args = parser->parse(argc, argv);
    ASSERT_EQ(args.count("flag"), 3);
    ASSERT_EQ(args.count("input_flag"), 3);
    ASSERT_EQ(args.count("optimization"), 3);
}

TEST_F(ArgparseTest, LongOptionNoValue) {
    const char *argv[] = {prog_path, "Hello", "--flag", ", ", "World", "--secret", "!", "--flag"};
    int argc = 8;
    Arguments args = parser->parse(argc, argv);
    ASSERT_EQ(args.count("flag"), 2);
    ASSERT_EQ(args.count("secret"), 1);
}

TEST_F(ArgparseTest, LongOptionValue) {
    const char *argv[] = {prog_path, "Hello", "--opt", "10", "World", "--std=C++17", "--opt"};
    int argc = 7;
    Arguments args = parser->parse(argc, argv);
    ASSERT_EQ(args.count("optional"), 2);
    ASSERT_EQ(args.count("standart"), 1);
    std::string out;
    ASSERT_TRUE(args.next_arg("optional", out));
    ASSERT_EQ(out, "10");
    ASSERT_FALSE(args.next_arg("optional", out));

    ASSERT_TRUE(args.next_arg("standart", out));
    ASSERT_EQ(out, "C++17");
    ASSERT_FALSE(args.next_arg("standart", out));
}

TEST_F(ArgparseTest, Abbreviated) {
    const char *argv[] = { prog_path, "-std=C++17" };
    int argc = 2;
    Arguments args = parser_abbr->parse(argc, argv);
    ASSERT_EQ(args.count("standart"), 1);
    ASSERT_EQ(args.count("some_name"), 0); // This also matches -s, but should be ignored
}
