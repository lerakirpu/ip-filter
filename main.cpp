#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <tuple>
#include <functional>

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

template<typename Predicate>
void printFilteredIPs(const std::vector<IPv4>& ips, Predicate pred) {
    for (const auto& ip : ips) {
        if (pred(ip)) {
            std::cout << ip.toString() << std::endl;
        }
    }
}

int main() {
    std::vector<IPv4> ip_addresses;
    std::string line;
    
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string ip_str;
        
        if (std::getline(ss, ip_str, '\t')) {
            try {
                ip_addresses.emplace_back(ip_str);
            } catch (...) {
                continue;
            }
        }
    }
    
    auto reverse_lex_comparator = [](const IPv4& a, const IPv4& b) { 
        return a > b; 
    };
    std::sort(ip_addresses.begin(), ip_addresses.end(), reverse_lex_comparator);
    
    // 1. Полный список после сортировки
    printFilteredIPs(ip_addresses, [](const IPv4&) { return true; });
    
    // 2. Первый байт равен 1
    printFilteredIPs(ip_addresses, [](const IPv4& ip) { 
        return ip.getOctet(0) == 1; 
    });
    
    // 3. Первый байт 46, второй 70
    printFilteredIPs(ip_addresses, [](const IPv4& ip) { 
        return ip.getOctet(0) == 46 && ip.getOctet(1) == 70; 
    });
    
    // 4. Любой байт равен 46
    printFilteredIPs(ip_addresses, [](const IPv4& ip) { 
        return ip.hasOctet(46); 
    });
    
    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> a4ababa8710bc826c16bc5a79746d6e3b73e7b15
