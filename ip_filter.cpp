#include<vector>
#include<string>
#include<algorithm>
#include<iostream>
#include<tuple>
#include "head/base.hpp"

int main()
{
    try
    {
        std::vector<std::vector<std::string>> ip_pool;
        std::vector<std::vector<int>> ip_pool_int;

        for (std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        for (const auto &ip_str : ip_pool)
        {
            std::vector<int> temp_vector;
            for (const auto &ip_part : ip_str)
            {
                temp_vector.push_back(std::stoi(ip_part));
            }
            ip_pool_int.push_back(temp_vector);
        }

        std::sort(ip_pool_int.begin(), ip_pool_int.end(), [](const std::vector<int> &first, const std::vector<int> &second)
                  { return first > second; });

        print(ip_pool_int); // вывод всех IP-адресов

        std::vector<std::vector<int>> print1, print4670, print46;

        for (const auto &ip : ip_pool_int)
        {
            if (ip[0] == 1)
                print1.push_back(ip);
            if (ip[0] == 46)
            {
                print46.push_back(ip);
                if (ip[1] == 70)
                    print4670.push_back(ip);
            }
        }
        auto s= std::make_tuple(print1,print4670,print46);
        print(std::get<0>(s));
        print(std::get<1>(s));
        print(std::get<2>(s));
        int a;
        std::cin>>a;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}