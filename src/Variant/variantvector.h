#ifndef VARIANTVECTOR_H
#define VARIANTVECTOR_H

#include <vector>

#include "variant.h"
#include "../export.h"

namespace PropertySystemNS
{

#  pragma warning( push )
#  pragma warning( disable: 4251 )

class PROPERTY_SYSTEM_EXPORT VariantVector : public std::vector<Variant>
{
public:
    VariantVector();
    VariantVector(const std::initializer_list<Variant> &_vec);
    VariantVector(const std::vector<Variant> &_vec);
    VariantVector &operator =(const std::vector<Variant> &_vec);

    template<class Type>
    VariantVector &fromVector(const std::vector<Type> &_vec)
    {
        std::vector<Variant>::clear();
        for(size_t i = 0, count = _vec.size(); i < count; ++i)
        {
            push_back(Variant(_vec.at(i)));
        }
        return *this;
    }

    template<class Type>
    std::vector<Type> toVector() const
    {
        std::vector<Type> outVec;
        for(size_t i = 0, count = std::vector<Variant>::size(); i < count; ++i)
        {
            outVec.push_back(std::vector<Variant>::at(i).value<Type>());
        }
        return outVec;
    }
};

#pragma warning( pop )

}

#endif // VARIANTVECTOR_H
