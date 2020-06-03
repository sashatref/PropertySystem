#ifndef VARIANT_H
#define VARIANT_H

#include <map>
#include <type_traits>

//#ifdef _DEBUG
//#include "vld.h"
//#endif

#include "../export.h"
#include "variantholder.h"
#include "variantconverter.h"
#include "variantoutput.h"
#include "../converters.h"
#include "../MetaType/metatype.h"

#  pragma warning( push )
#  pragma warning( disable: 4251 )

namespace PropertySystemNS
{

class IProperty;

class PROPERTY_SYSTEM_EXPORT Variant
{
    friend class VariantCreator;
public:
    Variant();
    Variant(int v);
    Variant(double v);
    Variant(const std::string &v);
    Variant(const Variant &v);
    Variant(const char *_v);
    void setValue(const Variant& v);
    void operator=(const Variant& v);

    bool convert(std::type_index _targetTypeId);

    bool canConvert(std::type_index _toTypeId) const;
    bool isType(std::type_index _typeId) const;

    explicit Variant(std::type_index _typeInfo, void *copy);
    virtual ~Variant();

    IProperty *propertyPtr();
    const IProperty *propertyPtr() const;

    void *dataPtr();
    const void *dataPtr() const;

    template <typename ArgType>
    explicit Variant(const ArgType& v)
        : holder(std::make_shared<VariantHolder<ArgType>>(typeid(ArgType), v))
    {
    }

    template <typename ArgType>
    static Variant fromValue(const ArgType& v)
    {
        Variant var;
        var.holder = std::make_shared<VariantHolder<ArgType>>(typeid(ArgType), v);
        return var;
    }

    template <typename ArgType>
    bool isType() const
    {
        return isType(typeid(ArgType));
    }

    template <typename Type>
    Type value() const
    {
        if(!holder)
        {
            return Type();
        }

        std::type_index toTypeId = typeid(Type);

        if(typeId() == toTypeId)
        {
            return std::static_pointer_cast<VariantHolder<Type>>(holder)->value;
        }

        auto it = variantConverterMap().find(std::make_pair(typeId(), toTypeId));
        if(it != variantConverterMap().end())
        {
            const void *data = holder->dataPtr();
            void *converted = it->second->convert(data);

            Type *output = static_cast<Type*>(converted);
            Type rValue(*output);
            delete output;
            return rValue;
        }

        return Type();
    }


    template <typename ArgType>
    void setValue(const ArgType& v)
    {
        holder = std::make_shared<VariantHolder<ArgType>>(typeid(ArgType), v);
    }


    template <typename ArgType>
    void operator=(const ArgType& v)
    {
        setValue(v);
    }

    template<class Type>
    bool canConvert() const
    {
        return canConvert(typeid(Type));
    }

    template<class Type>
    bool convert()
    {
        return convert(typeid(Type));
    }


    template<class Type>
    Type *valuePtr()
    {
        if(!holder) return 0;
        if(!isType<Type>()) return 0;

        return &static_cast<VariantHolder<Type>*>(holder.get())->value;
    }

    template<class Type>
    const Type *valuePtr() const
    {
        if(!holder) return 0;
        if(!isType<Type>()) return 0;

        return &static_cast<VariantHolder<Type>*>(holder.get())->value;
    }


    bool operator==(const Variant &_other) const;
    bool operator!=(const Variant& other) const;
    bool operator<(const Variant& other) const;
    bool operator>(const Variant& other) const;

    bool isValid() const;
    bool isEmpty() const;

    int toInt() const;
    bool toBool() const;
    double toDouble() const;
    float toFloat() const;
    long toLong() const;
    std::string toString() const;

    std::type_index typeId() const;
    const char *typeName() const;
    const char *compilerBasedTypeName() const;

    friend std::ostream PROPERTY_SYSTEM_EXPORT &operator <<(std::ostream &out, const Variant &_val);

private:
    HolderPtr holder;
};

#pragma warning( pop )


//variant creator scope

typedef HolderPtr(*VCreateFunc)(void *);
typedef std::map<std::type_index, VCreateFunc> VariantCreatorMap;

VariantCreatorMap PROPERTY_SYSTEM_EXPORT &variantCreatorMap();

template<class Type>
HolderPtr variantTypeCreator(void *copy)
{
    std::shared_ptr<VariantHolderBase> sharePtr;

    if(copy)
    {
        sharePtr.reset(new VariantHolder<Type>(typeid(Type), *static_cast<Type*>(copy)));
    } else
    {
        sharePtr.reset(new VariantHolder<Type>(typeid(Type), Type()));
    }

    return sharePtr;
}

template<class Type>
void registerVariantTypeCreator()
{
    variantCreatorMap()[typeid(Type)] = variantTypeCreator<Type>;
}

void PROPERTY_SYSTEM_EXPORT unregisterVariant();



//~variant creator scope

//variant converter scope

typedef std::pair<std::type_index, std::type_index> ConvertTypePair;
typedef std::map<ConvertTypePair, std::shared_ptr<VariantConverterBase>> VariantConverterMap;

VariantConverterMap PROPERTY_SYSTEM_EXPORT &variantConverterMap();

template<class From, class To, class ConvertFunc>
void registerVariantTypeConverter(ConvertFunc _convertFunc)
{
    std::shared_ptr<VariantConverterBase> sharedPtr;
    sharedPtr.reset(new VariantConverter<From, To>(_convertFunc));

    variantConverterMap()[std::make_pair(std::type_index(typeid(From)),
                                         std::type_index(typeid(To)))] = sharedPtr;
}

template<class From, class To>
void registerVariantInternalTypeConverter()
{
    std::shared_ptr<VariantConverterBase> sharedPtr;
    sharedPtr.reset(new InternalTypeConverter<From, To>());

    variantConverterMap()[std::make_pair(std::type_index(typeid(From)),
                                         std::type_index(typeid(To)))] = sharedPtr;
}

//~variant converter scope

template<class Type>
struct MetaTypeRegistrator
{
    template<class Type>
    static void registerArrayType(const std::vector<Type> &)
    {
        MetaType::registerArrayType<std::vector<Type>>();
        ConverterRegistrator::registerToVectorConverter<Type>();
    }

    template<class Type>
    static void registerArrayType(const Type &) {}


    template<class KeyType, class ValueType>
    static void registerMapType(const std::map<KeyType, ValueType> &)
    {
        MetaType::registerMapType<std::map<KeyType, ValueType>>();
        ConverterRegistrator::registerToMapConverter<KeyType, Type>();
    }

    template<class Type>
    static void registerMapType(const Type &) {}


    MetaTypeRegistrator(const char *_value)
    {
        MetaType::registerType<Type>(_value);
        MetaTypeRegistrator::registerArrayType(Type());
        MetaTypeRegistrator::registerMapType(Type());
        MetaType::registerDestructor<Type>();
        registerVariantTypeCreator<Type>();
    }
};


}


#endif //VARIANT_H
