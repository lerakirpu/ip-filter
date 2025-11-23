#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "head/base.hpp"  

int main(int, char **) {
    try {
        std::vector<std::vector<int>> ip_pool;
        
        for(std::string line; std::getline(std::cin, line);) {
            auto v = split(line, '\t');
            auto ip_str = v.at(0);
            auto ip = split(ip_str, '.');
            std::vector<int> ip_int;
            for(const auto& octet : ip) {
                ip_int.push_back(std::stoi(octet));
            }
            ip_pool.push_back(ip_int);
        }

        std::sort(ip_pool.begin(), ip_pool.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            for(size_t i = 0; i < std::min(a.size(), b.size()); ++i) {
                if(a[i] != b[i]) {
                    return a[i] > b[i];
                }
            }
            return a.size() > b.size();
        });

        for(const auto& ip : ip_pool) {
            print_ip(ip);
        }

        for(const auto& ip : ip_pool) {
            if(ip.at(0) == 1) {
                print_ip(ip);
            }
        }

        for(const auto& ip : ip_pool) {
            if(ip.at(0) == 46 && ip.at(1) == 70) {
                print_ip(ip);
            }
        }

        for(const auto& ip : ip_pool) {
            if(std::any_of(ip.begin(), ip.end(), [](int byte) { return byte == 46; })) {
                print_ip(ip);
            }
        }

    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}