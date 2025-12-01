#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "head/base.hpp"    

// Тест: разделение по табуляции
TEST(SplitTest, TabDelimiter) {
    std::vector<std::string> expected{"101.105.104.255", "0", "1"};
    EXPECT_EQ(split("101.105.104.255\t0\t1", '\t'), expected);
}

// Тест: разделение IP-адреса по точкам
TEST(SplitTest, DotDelimiter) {
    std::vector<std::string> expected{"113", "162", "145", "156"};
    EXPECT_EQ(split("113.162.145.156", '.'), expected);
}

// Тест: максимальный IP-адрес
TEST(SplitTest, MaxIP) {
    std::vector<std::string> expected{"255", "255", "255", "255"};
    EXPECT_EQ(split("255.255.255.255", '.'), expected);
}

// Тест: строка без разделителей
TEST(SplitTest, SingleElement) {
    std::vector<std::string> expected{"192"};
    EXPECT_EQ(split("192", '.'), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}