#ifndef BASETYPECONVERTERS_H
#define BASETYPECONVERTERS_H

#include <string>
#include <sstream>

namespace PropertySystemNS
{

inline std::string intToStdString(const int &_val)
{
    std::stringstream ss;
    ss << _val;
    return ss.str();
}

inline int stdStringToInt(const std::string &_val)
{
    std::stringstream ss(_val);
    int output;
    ss >> output;
    return output;
}

inline std::string doubleToStdString(const double &_val)
{
    std::stringstream ss;
    ss << _val;
    return ss.str();
}

inline double stdStringToDouble(const std::string &_val)
{
    std::stringstream ss(_val);
    double output;
    ss >> output;
    return output;
}

inline std::string floatToStdString(const float &_val)
{
    std::stringstream ss;
    ss << _val;
    return ss.str();
}

inline float stdStringToFloat(const std::string &_val)
{
    std::stringstream ss(_val);
    float output;
    ss >> output;
    return output;
}
}

#endif // BASETYPECONVERTERS_H
