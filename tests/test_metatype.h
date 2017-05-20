#ifndef TEST_METATYPE_H
#define TEST_METATYPE_H

#include <QObject>

class Test_MetaType : public QObject
{
    Q_OBJECT
public:
    Test_MetaType();

private slots:
    void createTypeFromText();
};

#endif // TEST_METATYPE_H
