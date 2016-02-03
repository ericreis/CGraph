//
// Created by Eric Reis on 11/17/15.
//

#ifndef CGRAPH_CONSTANTS_H
#define CGRAPH_CONSTANTS_H

#include <string>
#include <sstream>
#include <vector>


class Constants
{
public:
    static int string2int(const std::string &s);
    static float string2float(const std::string &s);
    static std::vector<std::string> split(const std::string &s, const char c);
    static int factorial(const int n);
};


#endif //CGRAPH_CONSTANTS_H
