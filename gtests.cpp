// gtests.cpp
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

// Сортировка
TEST(IPFilterTest, SortTest) {
    std::vector<std::vector<std::string>> ip_pool = {
        {"1", "1", "234", "8"},
        {"222", "173", "235", "246"},
        {"46", "70", "225", "39"},
        {"222", "82", "198", "61"}
    };
    
    std::sort(ip_pool.begin(), ip_pool.end(), [](auto& a, auto& b) {
        return a > b;
    });
    
    EXPECT_EQ(ip_pool[0][0], "222");
    EXPECT_EQ(ip_pool[2][0], "46");
    EXPECT_EQ(ip_pool[3][0], "1");
}

// Фильтр по первому октету 46
TEST(IPFilterTest, FilterFirstByte46) {
    std::vector<std::vector<std::string>> ip_pool = {
        {"46", "70", "225", "39"},
        {"222", "173", "235", "246"},
        {"46", "70", "147", "26"},
        {"1", "87", "203", "225"}
    };
    
    std::vector<std::vector<std::string>> result;
    for (const auto& ip : ip_pool) {
        if (ip[0] == "46") {
            result.push_back(ip);
        }
    }
    
    EXPECT_EQ(result.size(), 2);
    for (const auto& ip : result) {
        EXPECT_EQ(ip[0], "46");
    }
}

// Фильтр по двум октетам 46 и 70
TEST(IPFilterTest, FilterTwoBytes46_70) {
    std::vector<std::vector<std::string>> ip_pool = {
        {"46", "70", "225", "39"},
        {"222", "173", "235", "246"},
        {"46", "70", "147", "26"},
        {"1", "87", "203", "225"}
    };
    
    std::vector<std::vector<std::string>> result;
    for (const auto& ip : ip_pool) {
        if (ip[0] == "46" && ip[1] == "70") {
            result.push_back(ip);
        }
    }
    
    EXPECT_EQ(result.size(), 2);
    for (const auto& ip : result) {
        EXPECT_EQ(ip[0], "46");
        EXPECT_EQ(ip[1], "70");
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}