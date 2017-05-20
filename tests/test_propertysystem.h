#pragma once

#include <QObject>

class TestPropSystem : public QObject
{
    Q_OBJECT
public:
    TestPropSystem(QObject *parent = 0);

private slots:
    void setIntValueDirectly();
    void setIntValueQtGadgetSystem();
    void setIntValueQtObjectSystem();
    void setIntValueQtObject2System();
    void setIntValueIPropertySystem();

    void setSimpleValueDirectly();
    void setSimpleValueQtGadgetSystem();
    void setSimpleValueQtObjectSystem();
    void setSimpleValueQtObject2System();
    void setSimpleValueIPropertySystem();

    void testMapStdString();
    void testMapConstChar();

    void testStdStringComp();
    void testConstCharComp();


    void propertyIterate();

    void memberProperty();

private:
    int m_count;
};

