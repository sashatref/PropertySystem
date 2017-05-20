#include "project_pch.h"
#include "myclass4.h"

METAOBJECT_START(MyClass4)
METAPROPERTY(int, "value", MyClass4, &MyClass4::set_value, &MyClass4::get_value)
METAPROPERTY(Simple, "simple", MyClass4, &MyClass4::set_simple, &MyClass4::get_simple)
METAOBJECT_END

PS_DECLARE_METATYPE(MyClass4)

//const MetaObject *MyClass4::staticMetaObject = (new MetaObject("MyClass4"))
//        ->add(new MetaPropertyT<int, MyClass4>(false,
//                                               "value",
//                                                &MyClass4::set_value,
//                                                &MyClass4::get_value));

//const MetaObject *MyClass4::metaObject() const { return MyClass4::staticMetaObject; }

//namespace
//{
//    void deleteMetaObject() { delete MyClass4::staticMetaObject; }
//    REGISTER_DESTRUCTOR_FUNC(deleteMetaObject)
//}
