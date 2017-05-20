#ifndef MYCLASS5_H
#define MYCLASS5_H

#include "project_pch.h"
#include "simple.h"

class MyClass5 : public PropertySystemNS::IProperty
{
    I_PROPERTY
public:


    MyClass5(int _value = 0):
        m_intValue(_value)
    {
        i = new char();
    }

    MyClass5(const MyClass5 &Other)
    {
        m_intValue = Other.m_intValue;
        m_simpleValue = Other.m_simpleValue;
        i = new char(*Other.i);
    }

    MyClass5 &operator=(const MyClass5 &Other)
    {
        m_intValue = Other.m_intValue;
        m_simpleValue = Other.m_simpleValue;
        i = new char(*Other.i);

        return *this;
    }

    ~MyClass5()
    {
        delete i;
    }



    int m_intValue;
    Simple m_simpleValue;

    char *i;
};

#endif // MYCLASS5_H
