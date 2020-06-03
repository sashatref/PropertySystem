#pragma once

#include "project_pch.h"
#include "simple.h"



class MyClass6 : public IProperty
{
    I_PROPERTY
public:

    enum SomeEnum
    {
        Value1 = 0,
        Value2
    };

    MyClass6 &random();
    MyClass6(int _value = 0);
    ~MyClass6() { /*qDebug() << "~Myclass" << m_field1;*/ }
    bool operator ==(const MyClass6 &other) const;
    bool operator !=(const MyClass6 &other) const;
    bool operator <(const MyClass6 &_other) const;

    static void registerType();
    friend QDebug &operator<<(QDebug &_debug, const MyClass6 &other);

    int m_field1;
    QString m_field2;
    double m_field3;
    bool m_field4;
    QPoint m_pointField;
    QPointF m_pointFField;
    QSize m_size;
    Simple m_simple;
    SomeEnum somEnum;
};

Q_DECLARE_METATYPE(MyClass6)
