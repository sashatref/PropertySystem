#ifndef METAPROPERTYMACRO_H
#define METAPROPERTYMACRO_H

#include "Variant/variantmacro.h"

namespace PropertySystemNS
{
    template<class Type>
    void deleteMetaObject()
    {
        delete Type::staticMetaObject;
    }
}

#ifndef METAOBJECT_START
    #define METAOBJECT_START(ClassName)                                             \
        namespace                                                                   \
        {                                                                           \
            PS_REGISTER_DESTRUCTOR_FUNC(PropertySystemNS::deleteMetaObject<ClassName>)  \
        }                                                                           \
                                                                                    \
        const PropertySystemNS::MetaObject *ClassName::metaObject() const           \
        {                                                                           \
            return staticMetaObject;                                                \
        }                                                                           \
                                                                                    \
        const PropertySystemNS::MetaObject *ClassName::staticMetaObject =           \
                    (new PropertySystemNS::MetaObject(#ClassName))
#endif


#ifndef METAPROPERTY
    #define METAPROPERTY(Type, PropertyName, ClassName, Setter, Getter)             \
    ->add(new PropertySystemNS::MetaPropertyT<Type, ClassName>(                     \
                                                PropertyName,                       \
                                                Setter,                             \
                                                Getter))
#endif

#ifndef METAPROPERTY_MEMBER
    #define METAPROPERTY_MEMBER(Type, PropertyName, ClassName, Member)              \
    ->add(new PropertySystemNS::MetaPropertyMember<Type, ClassName>(                \
                                                PropertyName,                       \
                                                Member))
#endif

#ifndef METAOBJECT_END
    #define METAOBJECT_END ;
#endif

#ifndef I_PROPERTY
    #define I_PROPERTY                                                              \
        public:                                                                     \
            virtual const PropertySystemNS::MetaObject *metaObject() const override;\
        static const PropertySystemNS::MetaObject *staticMetaObject;
#endif


//#ifndef buildPropertyP
//    #define buildPropertyP(_type, member)                                           \
//      public:                                                                       \
//      inline void set_##member(const _type &_arg_##member)                          \
//      {                                                                             \
//        m_##member = _arg_##member;                                                 \
//      }                                                                             \
//      inline const _type &get_##member() const                                      \
//      {                                                                             \
//        return m_##member;                                                          \
//      }                                                                             \
//        _type m_##member;                                                           \
//      public:
//#endif

#ifndef PS_DISABLE_COPY
    #define PS_DISABLE_COPY(ClassName)                                              \
        ClassName(const ClassName &);                                               \
        ClassName &operator=(const ClassName &)
#endif


#endif // METAPROPERTYMACRO_H
