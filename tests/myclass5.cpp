#include "project_pch.h"
#include "myclass5.h"

//METAOBJECT_START(MyClass5)

//METAOBJECT_END

using namespace PropertySystemNS;


const MetaObject *MyClass5::staticMetaObject = (new MetaObject("MyClass5"))
        ->add(new MetaPropertyMember<int, MyClass5>(
                                               "intValue",
                                                &MyClass5::m_intValue))
        ->add(new MetaPropertyMember<Simple, MyClass5>("simpleValue",
                                                &MyClass5::m_simpleValue));


const MetaObject *MyClass5::metaObject() const { return MyClass5::staticMetaObject; }

namespace
{
    void deleteMetaObject() { delete MyClass5::staticMetaObject; }
    PS_REGISTER_DESTRUCTOR_FUNC(deleteMetaObject)
}


PS_DECLARE_METATYPE(MyClass5)
