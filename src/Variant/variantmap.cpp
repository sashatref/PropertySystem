#include "variantmap.h"

namespace PropertySystemNS
{

VariantMap::VariantMap():
    std::map<std::string, Variant>()
{

}

VariantMap::VariantMap(const std::map<std::string, Variant> &_map):
    std::map<std::string, Variant>(_map)
{

}

VariantMap &VariantMap::operator =(const std::map<std::string, Variant> &_map)
{
    std::map<std::string, Variant>::operator =(_map);
    return *this;
}


}
