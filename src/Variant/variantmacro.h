#ifndef VARIANTMACRO_H
#define VARIANTMACRO_H

namespace FuncInvokers
{
    struct InvokeAsConstructor
    {
        InvokeAsConstructor(void func())
        {
            func();
        }
    };

    struct InvokeAsDestructor
    {
        typedef void(*Func)();

        InvokeAsDestructor(Func _func):
            m_func(_func)
        {}

        ~InvokeAsDestructor()
        {
            m_func();
        }

        Func m_func;
    };
}




#define PS_CONCAT_(x,y) x##y

#define PS_CONCAT_COMA(x,y) x##,y

#define PS_CONCAT(x,y) PS_CONCAT_(x,y)

#define PS_STRINGIZE(x) PS_STRINGIZE2(x)

#define PS_STRINGIZE2(x) #x

#define PS_UNIQUE_NAME2(base) PS_CONCAT(base, __COUNTER__)


#ifndef PS_REGISTER_CONSTRUCTOR_FUNC
    #define PS_REGISTER_CONSTRUCTOR_FUNC(_func)                             \
    namespace                                                               \
    {                                                                       \
        static const FuncInvokers::InvokeAsConstructor                      \
            PS_UNIQUE_NAME2(InvokeAsConstructorClassInstance_)(_func);      \
    }
#endif

#ifndef PS_REGISTER_DESTRUCTOR_FUNC
    #define PS_REGISTER_DESTRUCTOR_FUNC(_func)                              \
    namespace                                                               \
    {                                                                       \
        static const FuncInvokers::InvokeAsDestructor                      \
            PS_UNIQUE_NAME2(InvokeAsDestructorClassInstance_)(_func);      \
    }
#endif



#define PS_DECLARE_METATYPE(ClassName)                                  \
namespace                                                               \
{                                                                       \
    static const PropertySystemNS::MetaTypeRegistrator<ClassName>       \
        PS_UNIQUE_NAME2(MetaTypeRegistratorClassInstance_)(#ClassName); \
}

#define PS_DECLARE_METATYPE_MAP(Part1, Part2)                           \
namespace                                                               \
{                                                                       \
    static const PropertySystemNS::MetaTypeRegistrator<Part1, ##Part2>       \
        PS_UNIQUE_NAME2(MetaTypeRegistratorClassInstance_)(PS_STRINGIZE(PS_CONCAT_COMA(Part1, Part2))); \
}

#endif // VARIANTMACRO_H
