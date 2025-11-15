#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "../head/base.hpp"

TEST(SplitTest, TabDelimiter) {
    std::vector<std::string> expected{"101.105.104.255", "0", "1"};
    EXPECT_EQ(split("101.105.104.255\t0\t1", '\t'), expected);
}

TEST(SplitTest, DotDelimiter) {
    std::vector<std::string> expected{"113", "162", "145", "156"};
    EXPECT_EQ(split("113.162.145.156", '.'), expected);
}

TEST(SplitTest, MaxIP) {
    std::vector<std::string> expected{"255", "255", "255", "255"};
    EXPECT_EQ(split("255.255.255.255", '.'), expected);
}

TEST(SplitTest, EmptyString) {
    std::vector<std::string> expected{""};
    EXPECT_EQ(split("", '.'), expected);
}

TEST(SplitTest, SingleElement) {
    std::vector<std::string> expected{"192"};
    EXPECT_EQ(split("192", '.'), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}