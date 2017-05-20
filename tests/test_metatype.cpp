#include "test_metatype.h"
#include "project_pch.h"
#include <QtTest>

#include "myclass.h"
#include "myclass2.h"
#include "myclass3.h"
#include "myclass4.h"
#include "myclass5.h"

#include <typeindex>

using namespace PropertySystemNS;



Test_MetaType::Test_MetaType()
{
//    qDebug() << (Variant::tIndex() == std::make_pair(std::type_index(typeid(int)),
//                                                     std::type_index(typeid(double))));
}

void Test_MetaType::createTypeFromText()
{
    QCOMPARE(MetaType::isRegistered(typeid(int)), true);

    QCOMPARE(MetaType::type("int"), std::type_index(typeid(int)));
    QCOMPARE(MetaType::typeName(typeid(int)), "int");

    MetaType::registerType<MyClass>("MyClass");
    QCOMPARE(MetaType::isRegistered(typeid(MyClass)), true);

    QCOMPARE(MetaType::type("MyClass"), std::type_index(typeid(MyClass)));
    QCOMPARE(MetaType::typeName(typeid(MyClass)), "MyClass");

    QCOMPARE(MetaType::isRegistered(typeid(std::string)), true);

    QCOMPARE(MetaType::isRegistered("int"), true);
}
