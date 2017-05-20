#include "project_pch.h"
#include "variantholder.h"


namespace PropertySystemNS
{

VariantHolderBase::VariantHolderBase(std::type_index _typeInfo) :
    typeInfo(_typeInfo)
{

}

VariantHolderBase::~VariantHolderBase()
{

}

bool VariantHolderBase::sameType(const VariantHolderBase *other) const
{
    return typeInfo == other->typeInfo;
}

}
