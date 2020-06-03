#include "test_psvalid.h"
#include <QtTest/QTest>

#include "myclass.h"
#include "myclass2.h"
#include "myclass3.h"
#include "myclass4.h"
#include "myclass5.h"
#include "myclass6.h"
#include "project_pch.h"

using namespace PropertySystemNS;

PS_DECLARE_METATYPE(MyClass6::SomeEnum)

PS_DECLARE_METATYPE(std::vector<int>)
PS_DECLARE_METATYPE(std::vector<MyClass>)

static const PropertySystemNS::MetaTypeRegistrator<std::map<std::string, int>>
    name_1("std::map<std::string, int>");

//#define PS_METASYSTEM(...)


//void Function(std::map<__VA_ARGS__>&x)

//PS_METASYSTEM(int, std::string);

MyClass5 MyClass4ToMyClass5(const MyClass4 &_in)
{
    MyClass5 out;
    out.m_intValue = _in.m_value;
    out.m_simpleValue = _in.m_simple;
    return out;
}

Test_PSValid::Test_PSValid(QObject *parent):
    QObject(parent)
{
    MetaType::registerLessOperator<MyClass>();
    MetaType::registerEqualsOperator<MyClass>();
    MetaType::registerEqualsOperator<MyClass4>();

    registerVariantTypeConverter<MyClass4, MyClass5>(MyClass4ToMyClass5);


}

void Test_PSValid::variantTest()
{
    Variant var;
    QCOMPARE(var.isEmpty(), true);
    QCOMPARE(var.isValid(), false);

    Variant var2(5);
    QCOMPARE(var2.isEmpty(), false);
    QCOMPARE(var2.isValid(), true);
    QCOMPARE(var2.value<int>(), 5);

    Variant var3(MyClass(3));
    QCOMPARE(var3.value<MyClass>().m_val, 3);

    MetaType::registerOutputOperator<MyClass>();

    QCOMPARE(var.typeId(), std::type_index(typeid(InvalidType)));
    QCOMPARE(QString(var.typeName()), QString(""));

    QCOMPARE(var2.typeId(), std::type_index(typeid(int)));
    QCOMPARE(QString(var2.typeName()), QString(typeid(int).name()));

    QCOMPARE(var3.typeId(), std::type_index(typeid(MyClass)));
    QCOMPARE(QString(var3.typeName()), QString(MetaType::typeName<MyClass>()));

   // std::cout << var << "\n" << var2 << "\n" << var3 << "\n";
}

void Test_PSValid::createVariantFromHashCode()
{
    Variant var1(typeid(int), 0);
    QCOMPARE(QString(var1.typeName()), QString(typeid(int).name()));

    int i = 10;
    Variant var4(typeid(int), &i);
    QCOMPARE(var4.value<int>(), 10);

    Variant var2(typeid(double), 0);
    QCOMPARE(QString(var2.typeName()), QString(typeid(double).name()));

    registerVariantTypeCreator<MyClass>();

    Variant var3(typeid(MyClass), 0);
    QCOMPARE(QString(var3.typeName()), QString(MetaType::typeName<MyClass>()));

    MyClass someClass(15);
    Variant var5(typeid(MyClass), &someClass);
    QCOMPARE(var5.value<MyClass>().m_val, 15);
}

void Test_PSValid::arrayElementType()
{
    std::type_index index = MetaType::getArrayElementType<std::vector<int>>();
    std::type_index index2 = MetaType::getArrayElementType<std::vector<MyClass>>();

    QCOMPARE(index, std::type_index(typeid(int)));
    QCOMPARE(index2, std::type_index(typeid(MyClass)));

    std::type_index mapIndex = MetaType::getMapElementType(typeid(std::map<std::string, int>));
    std::type_index mapKey = MetaType::getMapKeyType(typeid(std::map<std::string, int>));

    qDebug() << MetaType::typeName(typeid(std::map<std::string, int>));

    QCOMPARE(mapIndex, std::type_index(typeid(int)));
    QCOMPARE(mapKey, std::type_index(typeid(std::string)));
}

void Test_PSValid::createVariantFromName()
{
    Variant var1(MetaType::type("int"), 0);
    QCOMPARE(QString(var1.typeName()), QString(typeid(int).name()));



//    int i = 10;
//    Variant var4(typeid(int).hash_code(), &i);
//    QCOMPARE(var4.value<int>(), 10);

//    Variant var2(typeid(double).hash_code(), 0);
//    QCOMPARE(QString(var2.typeName()), QString(typeid(double).name()));

    MetaType::registerType<MyClass>("MyClass");

    registerVariantTypeCreator<MyClass>();

    Variant var3(MetaType::type("MyClass"), 0);
    QCOMPARE(QString(var3.typeName()), QString(MetaType::typeName<MyClass>()));

//    MyClass someClass(15);
//    Variant var5(typeid(MyClass).hash_code(), &someClass);
//    QCOMPARE(var5.value<MyClass>().m_val, 15);
}

void Test_PSValid::variantConvertTest()
{
    Variant var1(5.3);
    Variant var2(5);
    Variant var3(MyClass(10));
    Variant var4(std::string("12.3"));

    QCOMPARE(var1.canConvert<double>(), true);
    QCOMPARE(var1.canConvert<int>(), true);

    QCOMPARE(var2.canConvert<double>(), true);
    QCOMPARE(var2.canConvert<int>(), true);

    QCOMPARE(var1.value<int>(), 5);

    QCOMPARE(qFuzzyCompare(var2.value<double>(), 5.0), true);

    registerVariantTypeConverter<MyClass, int>(&MyClass::toInt);

    QCOMPARE(var3.canConvert<int>(), true);
    QCOMPARE(var3.value<int>(), 10);

    QCOMPARE(var1.value<std::string>(), std::string("5.3"));
    QCOMPARE(var4.value<std::string>(), std::string("12.3"));
    QCOMPARE(var4.value<int>(), 12);
    QCOMPARE(qFuzzyCompare(var4.value<double>(), 12.3), true);
    QCOMPARE(qFuzzyCompare(var4.value<float>(), 12.3f), true);

    QCOMPARE(var4.toString(), std::string("12.3"));
    QCOMPARE(var4.toInt(), 12);
    QCOMPARE(qFuzzyCompare(var4.toDouble(), 12.3), true);
    QCOMPARE(qFuzzyCompare(var4.toFloat(), 12.3f), true);


    Variant var5(5);

    QCOMPARE(var5.typeName(), MetaType::typeName<int>());

    var5.convert(typeid(std::string));

    QCOMPARE(var5.typeName(), MetaType::typeName<std::string>());

    var5.convert(typeid(double));

    QCOMPARE(var5.typeName(), MetaType::typeName<double>());


    Variant var6(MyClass4(11));

    QCOMPARE(var6.canConvert<MyClass5>(), true);
    QCOMPARE(var6.convert<MyClass5>(), true);

    QCOMPARE(var6.typeId(), std::type_index(typeid(MyClass5)));
}

void Test_PSValid::variantEquals()
{
    Variant var1(5);
    Variant var2(5);

    QCOMPARE(var1 == var2, true);

    Variant var3(5.3);
    Variant var4(5.3);

    QCOMPARE(var3 == var4, true);

    Variant var5(MyClass(10));
    Variant var6(MyClass(10));

    QCOMPARE(var5 == var6, true);
}

void Test_PSValid::variantLess()
{
    Variant var1(5);
    Variant var2(6);

    QCOMPARE(var1 > var2, false);
    QCOMPARE(var1 < var2, true);

    Variant var3(5.3);
    Variant var4(5.31);

    QCOMPARE(var3 > var4, false);
    QCOMPARE(var3 < var4, true);

    Variant var5(MyClass(10));
    Variant var6(MyClass(12));

    QCOMPARE(var5 > var6, false);
    QCOMPARE(var5 < var6, true);
}

void Test_PSValid::setGetTest()
{   
    //QSKIP("");

    MyClass4 someObj;

    someObj.m_value = 5;

    QCOMPARE(5, someObj.getProperty("value").value<int>());
    QCOMPARE(Simple(), someObj.getProperty("simple").value<Simple>());

    someObj.setProperty("value", 10);
    someObj.setProperty("simple", Variant(Simple(22)));

    QCOMPARE(someObj.m_value, 10);
    QCOMPARE(someObj.m_simple.m_intValue, 22);

//    for(int i = 0 ; i < someObj.metaObject()->properties().size(); i++)
//    {
//        const MetaProperty *p = someObj.metaObject()->properties().at(i);

//        qDebug() << p->name();
//        Variant va = p->readProperty(&someObj);
//        if(va.canConvert<std::string>())
//        {
//            qDebug() << va.value<std::string>().c_str();
//        }
    //    }
}

void Test_PSValid::variantIternalProperty()
{
    Variant var(5);

    QCOMPARE((bool)var.dataPtr(), true);
    QCOMPARE((bool)var.propertyPtr(), false);
    QCOMPARE((bool)var.valuePtr<double>(), false);
    QCOMPARE((bool)var.valuePtr<int>(), true);

    Variant var2(MyClass4(6));

    QCOMPARE((bool)var2.dataPtr(), true);
    QCOMPARE((bool)var2.propertyPtr(), true);

    QCOMPARE(var2.propertyPtr()->getProperty("value").toInt(), 6);

    var2.propertyPtr()->setProperty("value", 10);

    QCOMPARE(var2.propertyPtr()->getProperty("value").toInt(), 10);

    var2.valuePtr<MyClass4>()->m_value = 15;

    QCOMPARE(var2.propertyPtr()->getProperty("value").toInt(), 15);
}

void Test_PSValid::variantCopy()
{
    Variant var1(5);

    Variant var2 = var1;

    QCOMPARE(var1, var2);
    QCOMPARE(var1.value<int>(), var2.value<int>());
    QCOMPARE(var1.dataPtr() == var2.dataPtr(), false);

    var1 = 10;

    QCOMPARE(var1 != var2, true);

    var2 = 10;
    QCOMPARE(var1 == var2, true);

    Variant var3(MyClass4(10));

    Variant var4 = var3;

    QCOMPARE(var3.dataPtr() == var4.dataPtr(), false);
    QCOMPARE(var3.propertyPtr() == var4.propertyPtr(), false);

    Variant var5(var3);

    QCOMPARE(var3 == var5, true);
    QCOMPARE(var3.dataPtr() == var5.dataPtr(), false);
    QCOMPARE(var3.propertyPtr() == var5.propertyPtr(), false);

    Variant invVar;

    Variant var6(invVar);
}

void Test_PSValid::variantMapTest()
{
    std::map<int, MyClass6> myCLassTest;

    for(int i = 0 ; i < 10; i++)
    {
        myCLassTest[i] = MyClass6().random();
    }

    VariantMap map;
    map.fromMap(myCLassTest);

    std::map<int, MyClass6> res = map.toMap<int, MyClass6>();

    QCOMPARE(myCLassTest, res);
}

void Test_PSValid::variantVectorTest()
{
    std::vector<MyClass6> myCLassTest;

    for(int i = 0 ; i < 10; i++)
    {
        myCLassTest.push_back(MyClass6().random());
    }

    VariantVector vec;
    vec.fromVector(myCLassTest);

    std::vector<MyClass6> res = vec.toVector<MyClass6>();

    QCOMPARE(myCLassTest, res);
}

void Test_PSValid::enumTest()
{
//    MyClass6 someObj;

//    Variant val(1);

//    int v = (int)val.value<MyClass6::SomeEnum>();

//    QCOMPARE(v, 1);

//    someObj.setProperty("somEnum", 1);

//    QCOMPARE(someObj.somEnum, MyClass6::Value2);
}
