#include "project_pch.h"
#include "iproperty.h"
#include "metaproperty.h"


namespace PropertySystemNS
{

IProperty::IProperty()
{

}

void IProperty::setProperty(const char *_propertyName, const Variant &_val)
{
    const MetaProperty *prop = metaObject()->property(_propertyName);
    if(prop)
    {
        prop->writeProperty(this, _val);
    }
}

Variant IProperty::getProperty(const char *_propertyName) const
{
    const MetaProperty *prop = metaObject()->property(_propertyName);
    if(prop)
    {
        return prop->readProperty(this);
    }

    return Variant();
}



IProperty::~IProperty()
{

}

}
