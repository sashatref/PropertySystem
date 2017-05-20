#ifndef VARIANTHOLDER_H
#define VARIANTHOLDER_H

#include "../MetaType/metatype.h"

#include <memory>
#include <iostream>
#include <string>
#include <type_traits>

namespace PropertySystemNS
{


#  pragma warning( push )
#  pragma warning( disable: 4251 )

class MetaType;
class IProperty;

class PROPERTY_SYSTEM_EXPORT VariantHolderBase
{
public:
    VariantHolderBase(std::type_index _typeInfo);
    virtual ~VariantHolderBase();

    bool sameType(const VariantHolderBase* other) const;

    virtual std::type_index typeId() const = 0;
    virtual const char* typeName() const = 0;
    virtual const char* compilerBasedTypeName() const = 0;

    virtual bool isEquals(const VariantHolderBase* other) const = 0;
    virtual bool isLessThan(const VariantHolderBase* other) const = 0;
    virtual IProperty *propertyPtr() = 0;
    virtual void *dataPtr() = 0;
    virtual std::shared_ptr<VariantHolderBase> clone() = 0;

    std::type_index typeInfo;
};

#pragma warning(pop)


template <typename ArgType>
class VariantHolder : public VariantHolderBase
{
public:
    ArgType value;
    IProperty *propData;

    void setIProperty(IProperty *_ptr)
    {
        propData = _ptr;
    }

    void setIProperty(void *)
    {
        propData = 0;
    }

    VariantHolder(std::type_index _typeInfo, const ArgType& v):
        VariantHolderBase(_typeInfo),
        value(v)
    {
        setIProperty(&value);
    }

    virtual std::type_index typeId() const override
    {
        return typeid(ArgType);
    }

    virtual const char *typeName() const override
    { 
        return MetaType::typeName(std::type_index(typeid(ArgType)));
    }

    virtual const char *compilerBasedTypeName() const override
    {
        return typeid(ArgType).name();
    }

    virtual IProperty *propertyPtr() override
    {
        return propData;
    }

    virtual void *dataPtr() override
    {
        return &value;
    }

    virtual bool isEquals(const VariantHolderBase *other) const override
    {
        if(!sameType(other))
        {
            return false;
        }

        return MetaType::invokeEqualsOperator(typeInfo,
                                              &value,
                                              &static_cast<const VariantHolder<ArgType>*>(other)->value);
    }

    virtual bool isLessThan(const VariantHolderBase *other) const override
    {
        if (!sameType(other))
            return false;

        return MetaType::invokeLessOperator(typeInfo,
                                            &value,
                                            &static_cast<const VariantHolder<ArgType>*>(other)->value);
    }

    virtual std::shared_ptr<VariantHolderBase> clone() override
    {
        VariantHolder<ArgType> *newHolderPtr = new VariantHolder(this->typeInfo, this->value);
        std::shared_ptr<VariantHolder<ArgType>> sharedPtr;
        sharedPtr.reset(newHolderPtr);
        return sharedPtr;
    }


};

typedef std::shared_ptr<VariantHolderBase> HolderPtr;

}
#endif // VARIANTHOLDER_H
