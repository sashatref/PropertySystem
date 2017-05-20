#ifndef VARIANTMAP_H
#define VARIANTMAP_H

#include <map>

#include "../export.h"
#include "variant.h"


namespace PropertySystemNS
{

#  pragma warning( push )
#  pragma warning( disable: 4251 )

class PROPERTY_SYSTEM_EXPORT VariantMap : public std::map<std::string, Variant>
{
public:
    VariantMap();
    VariantMap(const std::map<std::string, Variant> &_map);
    VariantMap &operator =(const std::map<std::string, Variant> &_map);

    template<class KeyType, class ValueType>
    VariantMap &fromMap(const std::map<KeyType, ValueType> &_vec)
    {
        std::map<std::string, Variant>::clear();

        for(auto it = _vec.begin(); it != _vec.end(); ++it)
        {
            const std::string key = Variant(it->first).value<std::string>();
            std::map<std::string, Variant>::operator [](key) = Variant(it->second);
        }

        return *this;
    }

    template<class KeyType, class ValueType>
    std::map<KeyType, ValueType> toMap() const
    {
        std::map<KeyType, ValueType> outMap;

        for(auto it = std::map<std::string, Variant>::begin();
            it != std::map<std::string, Variant>::end();
            ++it)
        {
            const KeyType key = Variant(it->first).value<KeyType>();
            outMap[key] = it->second.value<ValueType>();
        }

        return outMap;
    }
};

#pragma warning( pop )

}

#endif // VARIANTMAP_H
