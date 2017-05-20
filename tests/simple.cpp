#include "project_pch.h"
#include "simple.h"

METAOBJECT_START(Simple)
METAPROPERTY_MEMBER(int, "intValue", Simple, &Simple::m_intValue)
METAPROPERTY_MEMBER(QString, "stringValue", Simple, &Simple::m_stringValue)
METAOBJECT_END

PS_DECLARE_METATYPE(Simple)

Simple::Simple(int val):
    m_intValue(val),
    m_stringValue()
{}

bool Simple::operator ==(const Simple &other) const
{
    if(m_intValue != other.m_intValue) return false;
    if(m_stringValue != other.m_stringValue) return false;
    return true;
}

bool Simple::operator !=(const Simple &other) const
{
    return !(*this == other);
}

void Simple::registerType()
{
    QMetaType::registerEqualsComparator<Simple>();
    QMetaType::registerDebugStreamOperator<Simple>();
}

Simple &Simple::random()
{
    m_intValue = rand() % 100;
    m_stringValue = Text::getRandomString();
    return *this;
}

QDebug &operator<<(QDebug &_debug, const Simple &other)
{
    _debug << other.m_intValue << "|" << other.m_stringValue;
    return _debug;
}
