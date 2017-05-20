#ifndef SIMPLE_H
#define SIMPLE_H

#include <QMetaType>
#include "project_pch.h"

class Simple : public IProperty
{
    I_PROPERTY
public:
    Simple(int _val = 2);

    int m_intValue;
    QString m_stringValue;

    bool operator ==(const Simple &other) const;
    bool operator !=(const Simple &other) const;

    static void registerType();

    Simple &random();

    friend QDebug &operator<<(QDebug &_debug, const Simple &other);
};


Q_DECLARE_METATYPE(Simple)

#endif // SIMPLE_H
