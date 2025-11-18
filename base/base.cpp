#include "../head/base.hpp"
#include <algorithm>
#include <sstream>

std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    
    while(stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    
    r.push_back(str.substr(start));
    return r;
}

void print_ip(const std::vector<int>& ip) {
    for(auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) {
        if (ip_part != ip.cbegin()) {
            std::cout << ".";
        }
        std::cout << *ip_part;
    }
    std::cout << std::endl;
}