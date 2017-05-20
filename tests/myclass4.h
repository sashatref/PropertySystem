#ifndef MYCLASS4_H
#define MYCLASS4_H

#include "project_pch.h"
#include "simple.h"

class MyClass4 : public PropertySystemNS::IProperty
{
public:
    I_PROPERTY

public:
    //buildPropertyP(int, value)
    //buildPropertyP(Simple, simple)


    void set_value(const int &_value)
    {
        m_value = _value;
    }

    const int &get_value() const
    {
        return m_value;
    }

    void set_simple(const  Simple &_value)
    {
        m_simple = _value;
    }

    const Simple &get_simple() const
    {
        return m_simple;
    }

    MyClass4(int _value = 0):
        m_value(_value)
    {

    }

    int m_value;
    Simple m_simple;
};

inline bool operator ==(const MyClass4 &o1, const MyClass4 &o2)
{
    if(o1.m_value != o2.m_value) return false;
    if(o1.m_simple != o2.m_simple) return false;

    return true;
}

#endif // MYCLASS4_H
