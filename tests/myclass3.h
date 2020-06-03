#ifndef MYCLASS3_H
#define MYCLASS3_H


#include "project_pch.h"
#include "simple.h"

class MyClass3 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int value READ getValue WRITE setValue)
    Q_PROPERTY(Simple simple READ getSimple WRITE setSimple)
public:
    void setValue(int _value)
    {
        m_value = _value;
    }

    int getValue() const
    {
        return m_value;
    }

    void setSimple(const Simple &_value)
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

#endif // MYCLASS3_H
