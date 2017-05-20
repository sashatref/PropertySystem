#ifndef IPROPERTY_H
#define IPROPERTY_H

#include "export.h"
#include "Variant/variant.h"

#include <map>
#include "metaproperty.h"
#include "metaobject.h"

namespace PropertySystemNS
{

class PROPERTY_SYSTEM_EXPORT IProperty
{
public:
    IProperty();

    virtual const MetaObject *metaObject() const = 0;

    void setProperty(const char *_propertyName, const Variant &_val);
    Variant getProperty(const char *_propertyName) const;

    virtual ~IProperty();
};



}

#endif // IPROPERTY_H
