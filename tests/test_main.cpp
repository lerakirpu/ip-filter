#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

// Копия класса IPv4 для тестирования
class IPv4 {
private:
    std::tuple<int, int, int, int> address;

public:
    IPv4(const std::string& ip_str) {
        std::stringstream ss(ip_str);
        std::string token;
        int octets[4];
        
        for (int i = 0; i < 4; ++i) {
            if (!std::getline(ss, token, '.')) {
                throw std::invalid_argument("Invalid IP format");
            }
            octets[i] = std::stoi(token);
            if (octets[i] < 0 || octets[i] > 255) {
                throw std::invalid_argument("Octet out of range");
            }
        }
        address = std::make_tuple(octets[0], octets[1], octets[2], octets[3]);
    }
    
    auto getOctet(int index) const -> int {
        switch(index) {
            case 0: return std::get<0>(address);
            case 1: return std::get<1>(address);
            case 2: return std::get<2>(address);
            case 3: return std::get<3>(address);
            default: throw std::out_of_range("Octet index out of range");
        }
    }
    
    auto operator>(const IPv4& other) const -> bool {
        return address > other.address;
    }
    
    bool hasOctet(int value) const {
        return std::get<0>(address) == value || 
               std::get<1>(address) == value || 
               std::get<2>(address) == value || 
               std::get<3>(address) == value;
    }
    
    auto toString() const -> std::string {
        std::stringstream ss;
        ss << std::get<0>(address) << "." << std::get<1>(address) << "." 
           << std::get<2>(address) << "." << std::get<3>(address);
        return ss.str();
    }
    
    auto getAddress() const -> const std::tuple<int, int, int, int>& {
        return address;
    }
};

// Тест 1: Создание и базовые операции с IPv4
class IPv4Test : public ::testing::Test {
protected:
    void SetUp() override {
        ip1 = std::make_unique<IPv4>("192.168.1.1");
        ip2 = std::make_unique<IPv4>("10.0.0.1");
        ip3 = std::make_unique<IPv4>("46.70.100.200");
    }

    void TearDown() override {
        ip1.reset();
        ip2.reset();
        ip3.reset();
    }

    std::unique_ptr<IPv4> ip1;
    std::unique_ptr<IPv4> ip2;
    std::unique_ptr<IPv4> ip3;
};

TEST_F(IPv4Test, ConstructorAndGetters) {
    EXPECT_EQ(ip1->getOctet(0), 192);
    EXPECT_EQ(ip1->getOctet(1), 168);
    EXPECT_EQ(ip1->getOctet(2), 1);
    EXPECT_EQ(ip1->getOctet(3), 1);
    
    EXPECT_EQ(ip2->getOctet(0), 10);
    EXPECT_EQ(ip3->getOctet(1), 70);
}

TEST_F(IPv4Test, HasOctetMethod) {
    EXPECT_TRUE(ip1->hasOctet(192));
    EXPECT_TRUE(ip1->hasOctet(168));
    EXPECT_TRUE(ip1->hasOctet(1));
    EXPECT_FALSE(ip1->hasOctet(255));
    
    EXPECT_TRUE(ip3->hasOctet(46));
    EXPECT_TRUE(ip3->hasOctet(70));
    EXPECT_FALSE(ip3->hasOctet(999));
}

TEST_F(IPv4Test, ToStringMethod) {
    EXPECT_EQ(ip1->toString(), "192.168.1.1");
    EXPECT_EQ(ip2->toString(), "10.0.0.1");
    EXPECT_EQ(ip3->toString(), "46.70.100.200");
}

// Тест 2: Обратная лексикографическая сортировка
TEST(IPv4SortingTest, ReverseLexicographicSorting) {
    std::vector<IPv4> ips = {
        IPv4("1.1.1.1"),
        IPv4("1.2.1.1"),
        IPv4("1.10.1.1"),
        IPv4("2.1.1.1")
    };
    
    // Сортировка в обратном лексикографическом порядке
    std::sort(ips.begin(), ips.end(), [](const IPv4& a, const IPv4& b) { 
        return a > b; 
    });
    
    // Проверяем порядок: 2.1.1.1 > 1.10.1.1 > 1.2.1.1 > 1.1.1.1
    EXPECT_EQ(ips[0].toString(), "2.1.1.1");
    EXPECT_EQ(ips[1].toString(), "1.10.1.1");
    EXPECT_EQ(ips[2].toString(), "1.2.1.1");
    EXPECT_EQ(ips[3].toString(), "1.1.1.1");
}

TEST(IPv4SortingTest, ByteComparisonNotString) {
    std::vector<IPv4> ips = {
        IPv4("1.2.1.1"),
        IPv4("1.10.1.1"),
        IPv4("1.20.1.1")
    };
    
    std::sort(ips.begin(), ips.end(), [](const IPv4& a, const IPv4& b) { 
        return a > b; 
    });
    
    // Числовое сравнение: 20 > 10 > 2
    EXPECT_EQ(ips[0].toString(), "1.20.1.1");
    EXPECT_EQ(ips[1].toString(), "1.10.1.1");
    EXPECT_EQ(ips[2].toString(), "1.2.1.1");
}

// Тест 3: Фильтрация IP-адресов
TEST(IPv4FilterTest, FilterByFirstOctet) {
    std::vector<IPv4> ips = {
        IPv4("1.1.1.1"),
        IPv4("1.2.3.4"),
        IPv4("2.1.1.1"),
        IPv4("46.70.1.1"),
        IPv4("1.10.20.30")
    };
    
    auto filter_first_1 = [](const IPv4& ip) { return ip.getOctet(0) == 1; };
    std::vector<std::string> filtered;
    
    for (const auto& ip : ips) {
        if (filter_first_1(ip)) {
            filtered.push_back(ip.toString());
        }
    }
    
    EXPECT_EQ(filtered.size(), 3);
    EXPECT_EQ(filtered[0], "1.1.1.1");
    EXPECT_EQ(filtered[1], "1.2.3.4");
    EXPECT_EQ(filtered[2], "1.10.20.30");
}

TEST(IPv4FilterTest, FilterByMultipleOctets) {
    std::vector<IPv4> ips = {
        IPv4("46.70.100.200"),
        IPv4("46.70.1.1"),
        IPv4("46.71.1.1"),
        IPv4("47.70.1.1"),
        IPv4("46.70.255.255")
    };
    
    auto filter_46_70 = [](const IPv4& ip) { 
        return ip.getOctet(0) == 46 && ip.getOctet(1) == 70; 
    };
    
    std::vector<std::string> filtered;
    for (const auto& ip : ips) {
        if (filter_46_70(ip)) {
            filtered.push_back(ip.toString());
        }
    }
    
    EXPECT_EQ(filtered.size(), 3);
    EXPECT_EQ(filtered[0], "46.70.100.200");
    EXPECT_EQ(filtered[1], "46.70.1.1");
    EXPECT_EQ(filtered[2], "46.70.255.255");
}

TEST(IPv4FilterTest, FilterByAnyOctet) {
    std::vector<IPv4> ips = {
        IPv4("192.168.46.1"),
        IPv4("10.46.0.1"),
        IPv4("46.70.100.200"),
        IPv4("1.2.3.4"),
        IPv4("255.255.255.46")
    };
    
    auto filter_any_46 = [](const IPv4& ip) { return ip.hasOctet(46); };
    std::vector<std::string> filtered;
    
    for (const auto& ip : ips) {
        if (filter_any_46(ip)) {
            filtered.push_back(ip.toString());
        }
    }
    
    EXPECT_EQ(filtered.size(), 4);
}

// Тест 4: Исключительные ситуации
TEST(IPv4ExceptionTest, InvalidFormat) {
    EXPECT_THROW(IPv4("192.168.1"), std::invalid_argument);
    EXPECT_THROW(IPv4("192.168.1.1.1"), std::invalid_argument);
    EXPECT_THROW(IPv4("192.168.1."), std::invalid_argument);
}

TEST(IPv4ExceptionTest, InvalidOctetRange) {
    EXPECT_THROW(IPv4("256.168.1.1"), std::invalid_argument);
    EXPECT_THROW(IPv4("192.300.1.1"), std::invalid_argument);
    EXPECT_THROW(IPv4("192.168.-1.1"), std::invalid_argument);
}

TEST(IPv4ExceptionTest, InvalidCharacters) {
    EXPECT_THROW(IPv4("192.168.a.1"), std::invalid_argument);
    EXPECT_THROW(IPv4("192.168.1.1a"), std::invalid_argument);
}

// Тест 5: Интеграционный тест - полный сценарий
TEST(IPv4IntegrationTest, CompleteWorkflow) {
    std::vector<IPv4> ips = {
        IPv4("1.1.1.1"),
        IPv4("1.2.1.1"), 
        IPv4("1.10.1.1"),
        IPv4("46.70.100.200"),
        IPv4("46.70.1.1"),
        IPv4("192.168.46.1")
    };
    
    // Сортировка
    std::sort(ips.begin(), ips.end(), [](const IPv4& a, const IPv4& b) { 
        return a > b; 
    });
    
    // Проверяем сортировку
    EXPECT_GT(ips[0], ips[1]);
    EXPECT_GT(ips[1], ips[2]);
    
    // Фильтрация по первому октету = 1
    auto count_first_1 = std::count_if(ips.begin(), ips.end(), 
        [](const IPv4& ip) { return ip.getOctet(0) == 1; });
    EXPECT_EQ(count_first_1, 3);
    
    // Фильтрация по 46.70
    auto count_46_70 = std::count_if(ips.begin(), ips.end(),
        [](const IPv4& ip) { return ip.getOctet(0) == 46 && ip.getOctet(1) == 70; });
    EXPECT_EQ(count_46_70, 2);
    
    // Фильтрация по любому октету = 46
    auto count_any_46 = std::count_if(ips.begin(), ips.end(),
        [](const IPv4& ip) { return ip.hasOctet(46); });
    EXPECT_EQ(count_any_46, 3);
}