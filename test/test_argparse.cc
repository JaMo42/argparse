#include "argparse.h"
#include "gtest/gtest.h"
#include <memory>
using namespace argparse;

#define prog_path "/path/to/program/program_name"
#define make_parser std::make_unique<ArgumentParser>

struct ArgparseTest : public ::testing::Test {
    // Parser with default settings
    std::unique_ptr<ArgumentParser> parser_def;
    // Parser with abbreviations enabled
    std::unique_ptr<ArgumentParser> parser_abbr;

    ArgparseTest() {
        // Create argument parsers
        parser_def = make_parser();
        parser_abbr = make_parser();
        parser_abbr->allow_abbreviations = true;
    }

};
/*
TEST_F(ArgparseTest, Parameters) {
    constexpr const char *argv[] = {prog_path, "-a", "5", "Hello, ", "World!"};
    constexpr int argc = 5;
    const Arguments args = parser->parse(argc, (const char **)argv);
}
*/