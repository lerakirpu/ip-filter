#include<vector>
#include<string>
#include<gtest/gtest.h>
#include"../head/base.hpp"
TEST(firstSplit,test1){
    std::vector<std::string> ans{"101.105.104.255","0","1"};
    EXPECT_EQ(split("101.105.104.255	0	1",'\t'), ans);
}
TEST(secondSplit,test2){
    std::vector<std::string> a{"113", "162", "145", "156"};
    EXPECT_EQ(split("113.162.145.156", '.'), a);
}
TEST(ThirdSplit,test2){
    std::vector<std::string> a{"255", "255", "255", "255"};
    EXPECT_EQ(split("255.255.255.255", '.'), a);
}