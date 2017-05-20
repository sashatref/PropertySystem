#ifndef CONVERTERS_H
#define CONVERTERS_H

#include "export.h"
#include "Variant/variantmacro.h"
#include "Variant/variantmap.h"
#include "Variant/variantvector.h"

namespace PropertySystemNS
{

namespace ConverterRegistrator
{
template<class Arg>
void registerToVectorConverter()
{
    typedef std::vector<Arg> UserVectorType;

    registerVariantTypeConverter<VariantVector, UserVectorType>([](const VariantVector &_inVec)
                                                                -> UserVectorType
    {
        return _inVec.toVector<Arg>();
    });


    registerVariantTypeConverter<UserVectorType, VariantVector>([](const UserVectorType &_inVec)
                                                                -> VariantVector
    {
        return VariantVector().fromVector(_inVec);
    });
}

template<class KeyType, class ValueType>
void registerToMapConverter()
{
    typedef std::map<KeyType, ValueType> UserMapType;

    registerVariantTypeConverter<VariantMap, UserMapType>([](const VariantMap &_inMap)
                                                                           -> UserMapType
    {
        return _inMap.toMap<KeyType, ValueType>();
    });


    registerVariantTypeConverter<UserMapType, VariantMap>([](const UserMapType &_inMap)
                                                                           -> VariantMap
    {
        return VariantMap().fromMap(_inMap);
    });
}
}




}

#endif // CONVERTERS_H
