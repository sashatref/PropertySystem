#ifndef MYCLASS2_H
#define MYCLASS2_H

#include "project_pch.h"
#include "simple.h"

class MyClass2
{
    Q_GADGET
    Q_PROPERTY(int value READ getValue WRITE setValue)
    Q_PROPERTY(Simple simple READ getSimple WRITE setSimple)
public:
    MyClass2()
    {

    }

    void setValue(int _value)
    {
        m_value = _value;
    }

    int getValue() const
    {
        return m_value;
    }

    void setSimple(const Simple _value)
    {
        m_simple = _value;
    }

    Simple getSimple() const
    {
        return m_simple;
    }

    int m_value;
    Simple m_simple;
};

#endif // MYCLASS2_H
