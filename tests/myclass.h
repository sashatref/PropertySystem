#ifndef MYCLASS_H
#define MYCLASS_H


#include "project_pch.h"
#include "simple.h"

class MyClass
{
public:
    MyClass(int _val = 0):
        m_val(_val)
    {

    }

    static int toInt(const MyClass & _val)
    {
        return _val.m_val;
    }

    bool operator==(const MyClass &_other) const
    {
        if(m_val != _other.m_val) return false;
        return true;
    }

    bool operator <(const MyClass &_other) const
    {
        return m_val < _other.m_val;
    }


    friend std::ostream& operator <<(std::ostream &out, const MyClass &_val)
    {
        out << _val.m_val;
        return out;
    }

    int m_val;
    Simple m_simple;
};

#endif // MYCLASS_H
