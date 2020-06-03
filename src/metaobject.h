#ifndef METAOBJECT_H
#define METAOBJECT_H

#include "metaproperty.h"
#include "export.h"

#include <vector>

namespace PropertySystemNS
{

class MetaProperty;
class MetaObjectPrivate;

class PROPERTY_SYSTEM_EXPORT MetaObject
{
    friend class IProperty;
public:
    MetaObject(const char *_className);
    virtual ~MetaObject();

    MetaObject *add(const MetaProperty *_prop);

    const MetaProperty *property(const char *_propertyName) const;

    const std::vector<const MetaProperty*> &properties() const;

private:
    PS_DISABLE_COPY(MetaObject);
    MetaObjectPrivate *const d;
};

}
#endif // METAOBJECT_H
