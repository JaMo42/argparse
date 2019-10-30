#include "argparse.h"
#include "gtest/gtest.h"
#include <memory>
using namespace argparse;

struct ArgparseTest : public ::testing::Test {
    std::unique_ptr<ArgumentParser> parser;

    ArgparseTest() {
        parser = std::make_unique<ArgumentParser>();
    }

};

TEST_F(ArgparseTest, Parameters) {
}
