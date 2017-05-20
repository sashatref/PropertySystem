#include "project_pch.h"
#include "variantvector.h"

namespace PropertySystemNS
{

VariantVector::VariantVector():
    std::vector<Variant>()
{

}

VariantVector::VariantVector(const std::vector<Variant> &_vec):
    std::vector<Variant>(_vec)
{

}

VariantVector &VariantVector::operator =(const std::vector<Variant> &_vec)
{
    std::vector<Variant>::operator =(_vec);
    return *this;
}

}

