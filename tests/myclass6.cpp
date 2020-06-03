#include "project_pch.h"
#include "myclass6.h"
#include "utils.h"

//#define MOVE_COPY


METAOBJECT_START(MyClass6)
METAPROPERTY_MEMBER(int, "field1", MyClass6, &MyClass6::m_field1)
METAPROPERTY_MEMBER(QString, "field2", MyClass6, &MyClass6::m_field2)
METAPROPERTY_MEMBER(double, "field3", MyClass6, &MyClass6::m_field3)
METAPROPERTY_MEMBER(bool, "field4", MyClass6, &MyClass6::m_field4)
METAPROPERTY_MEMBER(QPoint, "m_pointField", MyClass6, &MyClass6::m_pointField)
METAPROPERTY_MEMBER(QPointF, "m_pointFField", MyClass6, &MyClass6::m_pointFField)
METAPROPERTY_MEMBER(QSize, "size", MyClass6, &MyClass6::m_size)
METAPROPERTY_MEMBER(Simple, "simple", MyClass6, &MyClass6::m_simple)
METAPROPERTY_MEMBER(SomeEnum, "somEnum", MyClass6, &MyClass6::somEnum)
METAOBJECT_END

PS_DECLARE_METATYPE(MyClass6)

MyClass6::MyClass6(int _value)
{
#ifdef MOVE_COPY
    qDebug() << "MyClass()";
#endif
    m_field1 = _value;
    m_field2 = "hello";
    m_field3 = 5.6;
    m_field4 = false;
    somEnum = Value1;
}

MyClass6 &MyClass6::random()
{
    m_field1 = rand()%100;
    m_field2 = Text::getRandomString();
    m_field3 = rand()%100;
    m_field4 = rand()%2;
    m_pointField = QPoint(rand() % 10, rand() % 10);
    m_pointFField = QPointF(Numerics::getRandomDouble(), Numerics::getRandomDouble());
    m_size = QSize(rand() % 20, rand() % 20);
    m_simple.random();
    return *this;
}



bool MyClass6::operator ==(const MyClass6 &other) const
{
    if(m_field1 != other.m_field1) return false;
    if(m_field2 != other.m_field2) return false;
    if(m_field3 != other.m_field3) return false;
    if(m_field4 != other.m_field4) return false;
    if(m_pointFField != other.m_pointFField) return false;
    if(m_pointField != other.m_pointField) return false;
    if(m_size != other.m_size) return false;
    return true;
}

bool MyClass6::operator !=(const MyClass6 &other) const
{
    return !operator ==(other);
}

bool MyClass6::operator <(const MyClass6 &_other) const
{
    return false;
}


QList<MyClass6> toMyClassList(const QVariantList &input)
{
    QList<MyClass6> out;
    for(auto &it : input)
    {
        out << it.value<MyClass6>();
    }
    return out;
}

QList<Simple> toSimpleList (const QVariantList &list)
{
    QList<Simple> output;
    for(int i = 0 ; i < list.size(); i++)
    {
        output.append(list[i].value<Simple>());
    }
    return output;
}

QVector<QList<Simple>> toSimple2List(const QVariantList &list)
{
    QVector<QList<Simple>> output;
    for(int i = 0 ; i < list.size(); i++)
    {
        output.append(list[i].value<QList<Simple>>());
    }
    return output;
}

QVariantList fromMyClassVec(const QVector<MyClass6> &list)
{
    QVariantList output;
    for(int i = 0 ; i < list.size(); i++)
    {
        output.append(QVariant::fromValue(list[i]));
    }
    return output;
}

QVector<MyClass6> toMyClassVec(const QVariantList &list)
{
    QVector<MyClass6> output;
    for(int i = 0 ; i < list.size(); i++)
    {
        output.append(list[i].value<MyClass6>());
    }
    return output;
}

void MyClass6::registerType()
{
    QMetaType::registerDebugStreamOperator<MyClass6>();
    QMetaType::registerEqualsComparator<MyClass6>();
}


QDebug &operator<<(QDebug &_debug, const MyClass6 &other)
{
    _debug.space()
            << other.m_field1 << "|"
            << other.m_field2 << "|"
            << other.m_field3 << "|"
            << other.m_field4 << "|"
            << other.m_pointFField << "|"
            << other.m_pointField << "|"
            << other.m_size;
    return _debug;
}




