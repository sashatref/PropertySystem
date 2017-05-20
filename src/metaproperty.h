#ifndef METAPROPERTY_H
#define METAPROPERTY_H

#include <cstdio>

#include "export.h"
#include "Variant/variant.h"
#include "metapropertymacro.h"

namespace PropertySystemNS
{

class IProperty;

class PROPERTY_SYSTEM_EXPORT MetaProperty
{
public:
    MetaProperty(const char *_name);
    virtual ~MetaProperty();

    virtual Variant readProperty(const IProperty *_property) const = 0;
    virtual void writeProperty(IProperty *_property, const Variant &_value) const = 0;

    virtual bool isWritable() const = 0;
    virtual bool isReadable() const = 0;

    inline const char *name() const {return m_name;}

private:
    PS_DISABLE_COPY(MetaProperty);
    const char *m_name;
};


template<class ArgumentType, class ClassType>
class MetaPropertyT : public MetaProperty
{
public:
    typedef void(ClassType::*Setter)(const ArgumentType&);
    typedef const ArgumentType&(ClassType::*Getter)() const;

    MetaPropertyT(const char *_name, Setter _setter, Getter _getter):
        MetaProperty(_name),
        m_setter(_setter),
        m_getter(_getter)
    {

    }

    virtual Variant readProperty(const IProperty *_property) const override
    {
        if(!m_getter)
        {
            printf("Property '%s' have no getter function\n", name());
            return Variant();
        }

        const ClassType *p = dynamic_cast<const ClassType*>(_property);
        if(!p)
        {
            printf("Can't cast <const IProperty*> to <const %s*>\n", typeid(ClassType).name());
        }
        return Variant::fromValue((*p.*m_getter)());
    }
    virtual void writeProperty(IProperty *_property, const Variant &_value) const override
    {
        if(!m_setter)
        {
            printf("Property '%s' have no setter function\n", name());
            return;
        }

        ClassType *p = dynamic_cast<ClassType*>(_property);
        if(!p)
        {
            printf("Can't cast <IProperty*> to <%s*>\n", typeid(ClassType).name());
        }
        (*p.*m_setter)(_value.value<ArgumentType>());
    }

    inline bool isWritable() const { return m_setter; }
    inline bool isReadable() const { return m_getter; }

private:
    Setter m_setter;
    Getter m_getter;
};

template<class ArgumentType, class ClassType>
class MetaPropertyMember : public MetaProperty
{
public:
    typedef ArgumentType (ClassType::*MemberPointer);

    MetaPropertyMember(const char *_name, MemberPointer _member):
        MetaProperty(_name),
        m_member(_member)
    {
        if(!m_member)
        {
            printf("Null pointer passed as Class member at "
                        "<MetaPropertyMember> <%s::%s>\n", typeid(ClassType).name(), name());
        }
    }

    virtual Variant readProperty(const IProperty *_property) const override
    {
        if(!m_member)
        {
            printf("Property '%s' have no getter function\n", name());
            return Variant();
        }

        const ClassType *p = dynamic_cast<const ClassType*>(_property);
        if(!p)
        {
            printf("Can't cast <const IProperty*> to <const %s*>\n", typeid(ClassType).name());
        }
        return Variant::fromValue(*p.*m_member);
    }
    virtual void writeProperty(IProperty *_property, const Variant &_value) const override
    {
        if(!m_member)
        {
            printf("Property '%s' have no setter function\n", name());
            return;
        }

        ClassType *p = dynamic_cast<ClassType*>(_property);
        if(!p)
        {
            printf("Can't cast <IProperty*> to <%s*>\n", typeid(ClassType).name());
        }
        (*p).*m_member = _value.value<ArgumentType>();
    }

    inline bool isWritable() const { return m_member; }
    inline bool isReadable() const { return m_member; }

private:
    MemberPointer m_member;
};

}

#endif // METAPROPERTY_H
