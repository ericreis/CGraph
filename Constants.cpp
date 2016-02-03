//
// Created by Eric Reis on 11/17/15.
//

#include "Constants.h"

int Constants::string2int(const std::string &s)
{
    std::stringstream ss(s);
    int result;
    return ss >> result ? result : 0;
}

float Constants::string2float(const std::string &s)
{
    std::stringstream ss(s);
    float result;
    return ss >> result ? result : 0;
}

std::vector<std::string> Constants::split(const std::string &s, const char c)
{
    std::istringstream iss(s);
    std::vector<std::string> v;
    std::string str;
    while (getline(iss, str, c))
        v.push_back(str);
    return v;
}

int Constants::factorial(const int n)
{
    int fact = 1;
    for (int i = 1; i <= n; ++i)
        fact *= i;
    return fact;
}