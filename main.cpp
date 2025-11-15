#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <tuple>
#include <functional>
#include <stdexcept>
#include "head/base.hpp"

class IPv4 {
private:
    std::tuple<int, int, int, int> address;

public:
    IPv4(const std::string& ip_str) {
        std::vector<std::string> octets_str = split(ip_str, '.');
        if (octets_str.size() != 4) throw std::invalid_argument("Invalid IP format");
        
        int octets[4];
        for (int i = 0; i < 4; ++i) {
            octets[i] = std::stoi(octets_str[i]);
            if (octets[i] < 0 || octets[i] > 255) throw std::invalid_argument("Octet out of range");
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
    
    auto operator>(const IPv4& other) const -> bool { return address > other.address; }
    
    bool hasOctet(int value) const {
        return std::get<0>(address) == value || std::get<1>(address) == value || 
               std::get<2>(address) == value || std::get<3>(address) == value;
    }
    
    auto toString() const -> std::string {
        return std::to_string(std::get<0>(address)) + "." + std::to_string(std::get<1>(address)) + "." +
               std::to_string(std::get<2>(address)) + "." + std::to_string(std::get<3>(address));
    }
};

template<typename Predicate>
void printFilteredIPs(const std::vector<IPv4>& ips, Predicate pred) {
    for (const auto& ip : ips) if (pred(ip)) std::cout << ip.toString() << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--help") {
        std::cout << "IP Filter - processes and filters IPv4 addresses\nUsage: echo '1.1.1.1\\tdata' | ./ip_filter" << std::endl;
        return 0;
    }
    
    std::vector<IPv4> ip_addresses;
    std::string line;
    
    while (std::getline(std::cin, line)) {
        std::vector<std::string> parts = split(line, '\t');
        if (!parts.empty()) try { ip_addresses.emplace_back(parts[0]); } catch (...) { continue; }
    }
    
    std::sort(ip_addresses.begin(), ip_addresses.end(), [](const IPv4& a, const IPv4& b) { return a > b; });
    
    printFilteredIPs(ip_addresses, [](const IPv4&) { return true; });
    printFilteredIPs(ip_addresses, [](const IPv4& ip) { return ip.getOctet(0) == 1; });
    printFilteredIPs(ip_addresses, [](const IPv4& ip) { return ip.getOctet(0) == 46 && ip.getOctet(1) == 70; });
    printFilteredIPs(ip_addresses, [](const IPv4& ip) { return ip.hasOctet(46); });
    
    return 0;
}