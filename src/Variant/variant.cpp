#include "project_pch.h"
#include "variant.h"
#include "variantmacro.h"
#include "variantholder.h"
#include "basetypeconverters.h"

namespace PropertySystemNS
{

static struct VariantFactoryData
{
    VariantFactoryData()
    {
        //register base creators
        registerVariantTypeCreator<char>();
        registerVariantTypeCreator<unsigned char>();
        registerVariantTypeCreator<short>();
        registerVariantTypeCreator<signed char>();
        registerVariantTypeCreator<unsigned short>();
        registerVariantTypeCreator<int>();
        registerVariantTypeCreator<unsigned int>();
        registerVariantTypeCreator<long>();
        registerVariantTypeCreator<unsigned long>();
        registerVariantTypeCreator<bool>();
        registerVariantTypeCreator<double>();
        registerVariantTypeCreator<float>();
        registerVariantTypeCreator<long long>();
        registerVariantTypeCreator<unsigned long long>();

        registerVariantTypeCreator<std::string>();
        //~register base creators


        //register base converters
        registerVariantInternalTypeConverter<int, double>();
        registerVariantInternalTypeConverter<double, int>();

        registerVariantInternalTypeConverter<int, char>();
        registerVariantInternalTypeConverter<char, int>();

        registerVariantInternalTypeConverter<double, float>();
        registerVariantInternalTypeConverter<float, double>();

        registerVariantInternalTypeConverter<int, float>();
        registerVariantInternalTypeConverter<float, int>();

        registerVariantInternalTypeConverter<int, long>();
        registerVariantInternalTypeConverter<long, int>();

        registerVariantInternalTypeConverter<int, bool>();
        registerVariantInternalTypeConverter<bool, int>();

        registerVariantTypeConverter<int, std::string>(intToStdString);
        registerVariantTypeConverter<std::string, int>(stdStringToInt);

        registerVariantTypeConverter<double, std::string>(doubleToStdString);
        registerVariantTypeConverter<std::string, double>(stdStringToDouble);

        registerVariantTypeConverter<float, std::string>(floatToStdString);
        registerVariantTypeConverter<std::string, float>(stdStringToFloat);
        //~register base converters


    }

    ~VariantFactoryData()
    {

    }

    VariantCreatorMap m_variantCreatorMap;
    VariantConverterMap m_variantConverterMap;

} m_variantFactoryData;


VariantCreatorMap &variantCreatorMap() {return m_variantFactoryData.m_variantCreatorMap;}
VariantConverterMap &variantConverterMap() {return m_variantFactoryData.m_variantConverterMap;}


Variant::Variant() {}
Variant::~Variant() {}

Variant::Variant(int v) :
    holder(std::make_shared<VariantHolder<int>>(typeid(int), v))
{

}

Variant::Variant(double v) :
    holder(std::make_shared<VariantHolder<double>>(typeid(double), v))
{

}

Variant::Variant(const std::string &v) :
    holder(std::make_shared<VariantHolder<std::string>>(typeid(std::string), v))
{

}

Variant::Variant(const Variant &v):
    holder(v.holder ? v.holder->clone() : 0)
{

}

Variant::Variant(std::type_index _typeInfo, void *copy)
{
    auto it =  m_variantFactoryData.m_variantCreatorMap.find(_typeInfo);
    if(it != m_variantFactoryData.m_variantCreatorMap.end())
    {
        holder = it->second(copy);
    } else
    {
        std::cerr << "Trying to construct unsupported type:" << _typeInfo.name() << "\n";
    }
}



IProperty *Variant::propertyPtr()
{
    return holder ? holder->propertyPtr() : 0;
}

const IProperty *Variant::propertyPtr() const
{
    return holder ? holder->propertyPtr() : 0;
}

void *Variant::dataPtr()
{
    return holder ? holder->dataPtr() : 0;
}

const void *Variant::dataPtr() const
{
    return holder ? holder->dataPtr() : 0;
}

void Variant::setValue(const Variant &v)
{
    holder = v.holder ? v.holder->clone() : 0;
}

bool Variant::convert(std::type_index _targetTypeId)
{
    if(!canConvert(_targetTypeId)) return false;

    auto it = variantConverterMap().find(std::make_pair(typeId(), _targetTypeId));
    if(it != variantConverterMap().end())
    {
        const void *data = holder->dataPtr();
        void *converted = it->second->convert(data);

        Variant other(_targetTypeId, converted);

        MetaType::invokeDestructor(_targetTypeId, converted);
        delete converted;

        *this = other;
        return true;
    }

    return false;
}

bool Variant::canConvert(std::type_index _toTypeId) const
{
    if(_toTypeId == typeId()) return true;

    auto it = variantConverterMap().find(std::make_pair(typeId(), _toTypeId));
    return it != variantConverterMap().end();
}

bool Variant::isType(std::type_index _typeId) const
{
    return holder ? _typeId == holder->typeInfo : false;
}

void Variant::operator=(const Variant &v)
{
    setValue(v);
}

bool Variant::operator ==(const Variant &_other) const
{
    if(isEmpty()) return false;

    return holder->isEquals(_other.holder.get());
}

bool Variant::operator!=(const Variant &other) const
{
    return !holder->isEquals(other.holder.get());
}

bool Variant::operator<(const Variant &other) const
{
    return holder->isLessThan(other.holder.get());
}

bool Variant::operator>(const Variant &other) const
{
    return other.holder->isLessThan(holder.get());
}

bool Variant::isValid() const {return static_cast<bool>(holder);}

bool Variant::isEmpty() const {return !holder;}

int Variant::toInt() const
{
    return value<int>();
}

bool Variant::toBool() const
{
    return value<bool>();
}

double Variant::toDouble() const
{
    return value<double>();
}

float Variant::toFloat() const
{
    return value<float>();
}

long Variant::toLong() const
{
    return value<long>();
}

std::string Variant::toString() const
{
    return value<std::string>();
}

std::type_index Variant::typeId() const
{
    return holder ? holder->typeId() : typeid(InvalidType);
}

const char *Variant::typeName() const
{
    return holder ? holder->typeName() : "";
}

const char *Variant::compilerBasedTypeName() const
{
    return holder ? holder->compilerBasedTypeName() : "";
}

std::ostream &operator <<(std::ostream &out, const Variant &_val)
{
    if(_val.holder)
    {
        out << "Variant(" << _val.typeName() << ", ";
        MetaType::invokeOutputOperator(_val.holder->typeId(), out, _val.holder->dataPtr());
        out << ")";
        return out;
    }

    out << "Variant(Invalid, )";
    return out;
}



}
