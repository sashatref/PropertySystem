#ifndef METATYPE_H
#define METATYPE_H

#include "../export.h"
#include <typeinfo>
#include <typeindex>
#include "../metapropertymacro.h"
#include "metatypelessbase.h"
#include "metatypedestructorbase.h"
#include "metatypeequalsbase.h"
#include "metatypeoutputbase.h"

namespace PropertySystemNS
{

class InvalidType {};

class Variant;
class IProperty;
class MetaTypeOutputBase;
class MetaTypeLessBase;
class MetaTypeEqualsBase;
class MetaTypeDestructorBase;

class PROPERTY_SYSTEM_EXPORT MetaType
{
    static void registerArrayType(std::type_index _listType, std::type_index _elementType);
    static void registerMapType(std::type_index _mapType,
                                std::type_index _keyType,
                                std::type_index _elementType);
public:
    MetaType(unsigned int _sizeOf);

    virtual ~MetaType();

    static std::type_index type(const char *_typeName);

    template<class Type>
    static const char * typeName()
    {
        return typeName(typeid(Type));
    }

    static const char * typeName(std::type_index _typeInfo);

    template<class Type>
    static bool isRegistered()
    {
        return isRegistered(typeid(Type));
    }

    static bool isRegistered(std::type_index _typeInfo);
    static bool isRegistered(const char *_typeName);

    template<class T>
    static void registerArrayType()
    {
        registerArrayType(typeid(T), typeid(T::value_type));
    }

    template<class T>
    static void registerMapType()
    {
        registerMapType(typeid(T), typeid(T::key_type), typeid(T::mapped_type));
    }

    template<class Type>
    static std::type_index getArrayElementType()
    {
        return getArrayElementType(typeid(Type));
    }

    static std::type_index getArrayElementType(std::type_index _index);
    static std::type_index getMapElementType(std::type_index _index);
    static std::type_index getMapKeyType(std::type_index _index);

    template<class Type>
    static void registerType(const char *_typeName)
    {
        registerType(typeid(Type), _typeName, sizeof(Type));
    }

    static void registerType(std::type_index _typeInfo, const char *_typeName, int _typeSize);

    template<class Type>
    static bool registerLessOperator()
    {
        return registerLessOperator(typeid(Type), new MetaTypeLess<Type>());
    }

    static bool registerLessOperator(std::type_index _typeInfo, MetaTypeLessBase *_lessOperator);

    template<class Type>
    static bool registerEqualsOperator()
    {
        return registerEqualsOperator(typeid(Type), new MetaTypeEquals<Type>());
    }

    static bool registerEqualsOperator(std::type_index _typeInfo, MetaTypeEqualsBase *_equalsOperator);

    template<class Type>
    static bool registerOutputOperator()
    {
        return registerOutputOperator(typeid(Type), new MetaTypeOutput<Type>());
    }

    static bool registerOutputOperator(std::type_index _typeInfo, MetaTypeOutputBase *_outputOperator);

    template<class Type>
    static bool registerDestructor()
    {
        return registerDestructor(typeid(Type), new MetaTypeDestructor<Type>());
    }

    static bool registerDestructor(std::type_index _typeInfo, MetaTypeDestructorBase *_destructor);

    static bool invokeLessOperator(std::type_index _typeIndex, const void *o1, const void *o2);
    static bool invokeEqualsOperator(std::type_index _typeIndex, const void *o1, const void *o2);
    static bool invokeOutputOperator(std::type_index _typeIndex, std::ostream &ss, const void *o1);
    static bool invokeDestructor(std::type_index _typeIndex, void *o1);

    static void unregisterAll();

public:
    unsigned int m_sizeOf;
    MetaTypeOutputBase *m_outputOperator;
    MetaTypeLessBase *m_lessOperator;
    MetaTypeEqualsBase *m_equalsOperator;
    MetaTypeDestructorBase *m_destructor;

private:
    PS_DISABLE_COPY(MetaType);
};


}

#endif // METATYPE_H
