#include "project_pch.h"
#include "metaobject.h"

namespace PropertySystemNS
{

    class MetaObjectPrivate
    {
    public:
        MetaObjectPrivate(const char *_className):
            className(_className)
        { }

        std::vector<const MetaProperty*> propList;
        std::map<const char*, std::shared_ptr<const MetaProperty>, cmp_str> propMap;
        const char *className;
    };


    MetaObject::MetaObject(const char *_className):
        d(new MetaObjectPrivate(_className))
    {

    }

    MetaObject::~MetaObject()
    {
        delete d;
    }

    MetaObject *MetaObject::add(const MetaProperty *_prop)
    {
        d->propList.push_back(_prop);

        std::shared_ptr<const MetaProperty> sharedPtr;
        sharedPtr.reset(_prop);
        d->propMap[_prop->name()] = sharedPtr;
        return this;
    }

    const MetaProperty *MetaObject::property(const char *_propertyName) const
    {
        auto it = d->propMap.find(_propertyName);
        if(it != d->propMap.end())
        {
            return it->second.get();
        }

        return 0;
    }

    std::vector<const MetaProperty *> MetaObject::properties() const
    {
        return d->propList;
    }

}
