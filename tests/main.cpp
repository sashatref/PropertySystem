#include <QCoreApplication>
#include <QTest>
#include "test_propertysystem.h"
#include "test_psvalid.h"
#include "test_metatype.h"
#include "locale"
#include <iostream>

#include "time.h"
#include <QDebug>

//#ifdef _DEBUG
//    #include "vld.h"
//#endif

#include "project_pch.h"

#include "classa.h"

class MyClass
{

};

int main(int argc, char *argv[])
{
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    QCoreApplication a(argc, argv);

    //QTest::qExec(&TestPropSystem(), argc, argv);

    Test_PSValid t1;
    Test_MetaType t2;
    TestPropSystem t3;

    QTest::qExec(&t1, argc, argv);
    QTest::qExec(&t2, argc, argv);
    //QTest::qExec(&t3, argc, argv);

    //return a.exec();
    return 0;
}

