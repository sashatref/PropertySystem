#include "project_pch.h"
#include "test_propertysystem.h"
#include <QtTest/QTest>

#include "myclass.h"
#include "myclass2.h"
#include "myclass3.h"
#include "myclass4.h"
#include "myclass5.h"

using namespace PropertySystemNS;

struct cmp_str1
{
   bool operator()(char const *a, char const *b) const
   {
      return std::strcmp(a, b) < 0;
   }
};

TestPropSystem::TestPropSystem(QObject *parent) : QObject(parent)
{
    m_count = 1000000;
}

void TestPropSystem::setIntValueDirectly()
{
    //QSKIP("");
    QList<MyClass*> list;

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count; ++i)
        {
            MyClass *item = new MyClass();
            item->m_val = i;
            list << item;
        }
    }
    qDeleteAll(list);
}

void TestPropSystem::setIntValueQtGadgetSystem()
{
    //QSKIP("");
    QList<MyClass2*> list;

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count; ++i)
        {
            MyClass2 *item = new MyClass2();

            const int propIndex = MyClass2::staticMetaObject.indexOfProperty("value");
            MyClass2::staticMetaObject.property(propIndex).writeOnGadget(item, i);

            list << item;
        }
    }

    qDeleteAll(list);
}

void TestPropSystem::setIntValueQtObjectSystem()
{
    //QSKIP("");
    QList<MyClass3*> list;

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count; ++i)
        {
            MyClass3 *item = new MyClass3();

            const int propIndex = MyClass3::staticMetaObject.indexOfProperty("value");
            MyClass3::staticMetaObject.property(propIndex).write(item, i);

            list << item;
        }
    }

    qDeleteAll(list);
}

void TestPropSystem::setIntValueQtObject2System()
{
    //QSKIP("");

    QList<MyClass3*> list;

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count; ++i)
        {
            MyClass3 *item = new MyClass3();
            item->setProperty("value", i);
            list << item;
        }
    }

    qDeleteAll(list);
}

void TestPropSystem::setIntValueIPropertySystem()
{
    //QSKIP("");

    QList<MyClass4*> list;

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count; ++i)
        {
            MyClass4 *item = new MyClass4();
            item->setProperty("value", i);
            list << item;
        }
    }

    qDeleteAll(list);
}

void TestPropSystem::setSimpleValueDirectly()
{
    //QSKIP("");
    QList<MyClass*> list;

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count; ++i)
        {
            MyClass *item = new MyClass();
            item->m_simple = Simple(i);
            list << item;
        }
    }
    qDeleteAll(list);
}

void TestPropSystem::setSimpleValueQtGadgetSystem()
{
    //QSKIP("");
    QList<MyClass2*> list;

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count; ++i)
        {
            MyClass2 *item = new MyClass2();

            const int propIndex = MyClass2::staticMetaObject.indexOfProperty("simple");
            MyClass2::staticMetaObject.property(propIndex).writeOnGadget(item, QVariant::fromValue(Simple(i)));

            list << item;
        }
    }

    qDeleteAll(list);
}

void TestPropSystem::setSimpleValueQtObjectSystem()
{
    //QSKIP("");
    QList<MyClass3*> list;

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count; ++i)
        {
            MyClass3 *item = new MyClass3();

            const int propIndex = MyClass3::staticMetaObject.indexOfProperty("simple");
            MyClass3::staticMetaObject.property(propIndex).write(item, QVariant::fromValue(Simple(i)));

            list << item;
        }
    }

    qDeleteAll(list);
}

void TestPropSystem::setSimpleValueQtObject2System()
{
    //QSKIP("");

    QList<MyClass3*> list;

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count; ++i)
        {
            MyClass3 *item = new MyClass3();
            item->setProperty("simple", QVariant::fromValue(Simple(i)));
            list << item;

        }
    }

    qDeleteAll(list);
}

void TestPropSystem::setSimpleValueIPropertySystem()
{
    //QSKIP("");

    QList<MyClass4*> list;

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count; ++i)
        {
            MyClass4 *item = new MyClass4();
            item->setProperty("simple", Variant(Simple(i)));
            list << item;
        }
    }

    qDeleteAll(list);
}

void TestPropSystem::testMapStdString()
{
    //QSKIP("");
    std::map<std::string, int> map;

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count / 40; ++i)
        {
            std::stringstream ss;
            ss << "item_" << i;
            map[ss.str()] = i;
        }

        for(int i = 0 ; i < m_count / 40; i++)
        {
            std::stringstream ss;
            ss << "item_" << i;
            const int val = map[ss.str()];
            Q_UNUSED(val);
        }
    }
}

void TestPropSystem::testMapConstChar()
{
    //QSKIP("");
    std::map<const char*, int, cmp_str1> map;

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count / 40; ++i)
        {
            std::stringstream ss;
            ss << "item_" << i;
            map[ss.str().c_str()] = i;
        }

        for(int i = 0 ; i < m_count / 40; i++)
        {
            std::stringstream ss;
            ss << "item_" << i;
            const int val = map[ss.str().c_str()];
            Q_UNUSED(val);
        }
    }
}

void TestPropSystem::testStdStringComp()
{
   // QSKIP("");

    std::string str1 = "item1", str2 = "item2";

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count; i++)
        {
            const bool res = str1 == str2;
            (void)res;
        }
    }
}

void TestPropSystem::testConstCharComp()
{
    //QSKIP("");

    const char *str1 = "item1", *str2 = "item2";

    QBENCHMARK
    {
        for(int i = 0 ; i < m_count; i++)
        {
            const bool res = std::strcmp(str1, str2) < 0;
            (void)res;
        }
    }
}

void TestPropSystem::propertyIterate()
{
    MyClass4 someClass;

    std::vector<const MetaProperty*> props = someClass.metaObject()->properties();

    for(size_t i = 0 ; i < props.size(); i++)
    {
        qDebug() << props.at(i)->name();
    }
}

void TestPropSystem::memberProperty()
{
    MyClass5 val1(10);

    QCOMPARE(val1.getProperty("intValue").value<int>(), 10);

    val1.setProperty("intValue", 11);

    QCOMPARE(val1.m_intValue, 11);
}

