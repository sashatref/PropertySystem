#include "project_pch.h"
#include "metatype.h"
#include "Variant/variantmacro.h"

#include "metatypelessbase.h"

namespace PropertySystemNS
{

static struct MetaFactoryData
{
    MetaFactoryData()
    {
        //register type

        MetaType::registerType<char>("char");
        MetaType::registerType<unsigned char>("unsigned char");
        MetaType::registerType<short>("short");
        MetaType::registerType<signed char>("signed char");
        MetaType::registerType<unsigned short>("unsigned short");
        MetaType::registerType<int>("int");
        MetaType::registerType<unsigned int>("unsigned int");
        MetaType::registerType<long>("long");
        MetaType::registerType<unsigned long>("unsigned long");
        MetaType::registerType<bool>("bool");
        MetaType::registerType<double>("double");
        MetaType::registerType<float>("float");
        MetaType::registerType<long long>("long long");
        MetaType::registerType<unsigned long long>("unsigned long long");
        MetaType::registerType<std::string>("std::string");

        MetaType::registerLessOperator<char>();
        MetaType::registerLessOperator<unsigned char>();
        MetaType::registerLessOperator<short>();
        MetaType::registerLessOperator<signed char>();
        MetaType::registerLessOperator<unsigned short>();
        MetaType::registerLessOperator<int>();
        MetaType::registerLessOperator<unsigned int>();
        MetaType::registerLessOperator<long>();
        MetaType::registerLessOperator<unsigned long>();
        MetaType::registerLessOperator<bool>();
        MetaType::registerLessOperator<double>();
        MetaType::registerLessOperator<float>();
        MetaType::registerLessOperator<long long>();
        MetaType::registerLessOperator<unsigned long long>();
        MetaType::registerLessOperator<std::string>();

        MetaType::registerDestructor<std::string>();

        MetaType::registerEqualsOperator<char>();
        MetaType::registerEqualsOperator<unsigned char>();
        MetaType::registerEqualsOperator<short>();
        MetaType::registerEqualsOperator<signed char>();
        MetaType::registerEqualsOperator<unsigned short>();
        MetaType::registerEqualsOperator<int>();
        MetaType::registerEqualsOperator<unsigned int>();
        MetaType::registerEqualsOperator<long>();
        MetaType::registerEqualsOperator<unsigned long>();
        MetaType::registerEqualsOperator<bool>();
        MetaType::registerEqualsOperator<double>();
        MetaType::registerEqualsOperator<float>();
        MetaType::registerEqualsOperator<long long>();
        MetaType::registerEqualsOperator<unsigned long long>();
        MetaType::registerEqualsOperator<std::string>();

        MetaType::registerOutputOperator<char>();
        MetaType::registerOutputOperator<unsigned char>();
        MetaType::registerOutputOperator<short>();
        MetaType::registerOutputOperator<signed char>();
        MetaType::registerOutputOperator<unsigned short>();
        MetaType::registerOutputOperator<int>();
        MetaType::registerOutputOperator<unsigned int>();
        MetaType::registerOutputOperator<long>();
        MetaType::registerOutputOperator<unsigned long>();
        MetaType::registerOutputOperator<bool>();
        MetaType::registerOutputOperator<double>();
        MetaType::registerOutputOperator<float>();
        MetaType::registerOutputOperator<long long>();
        MetaType::registerOutputOperator<unsigned long long>();
        MetaType::registerOutputOperator<std::string>();
        //~register type
    }

    ~MetaFactoryData()
    {
        std::for_each(m_metaTypeList.begin(), m_metaTypeList.end(),
                      [](MetaType *_item)
        {
            delete _item;
        });

        std::for_each(m_indexList.begin(), m_indexList.end(),
                      [](const std::type_index* _item)
        {
            delete _item;
        });
    }

    std::vector<MetaType*> m_metaTypeList;
    std::vector<const std::type_index*> m_indexList;

    std::map<std::type_index, const char*> m_typeToName;
    std::map<std::type_index, MetaType*> m_typeToMetaType;

    std::map<const char *, const std::type_index *, cmp_str> m_nameToTypeId;
    std::map<const char *, MetaType*, cmp_str> m_nameToMetaType;

    std::map<std::type_index, const std::type_index *> m_listElementType;   //list type, element type

    void createMetaIfNoExist(std::type_index _typeIndex, int _typeSize, const char *_typeName)
    {
        auto it = m_typeToMetaType.find(_typeIndex);
        if(it == m_typeToMetaType.end())
        {
            MetaType *metaType = new MetaType(_typeSize);

            m_metaTypeList.push_back(metaType);

            m_typeToName[_typeIndex] = _typeName;
            m_typeToMetaType[_typeIndex] = metaType;
            m_nameToTypeId[_typeName] = &m_typeToName.find(_typeIndex)->first;
            m_nameToMetaType[_typeName] = metaType;
        } else
        {
            if(it->second->m_sizeOf != _typeSize)
            {
                std::cerr << "Type <" << _typeName << "> size <" << _typeSize << "> early registered "
                             "with size <" << it->second->m_sizeOf << ">\n";
            }
        }
    }

    MetaType *getMetaType(std::type_index _typeIndex)
    {
        auto it = m_typeToMetaType.find(_typeIndex);
        if(it == m_typeToMetaType.end()) return 0;

        return it->second;
    }

} m_metaFactoryData;




MetaType::MetaType(unsigned int _sizeOf):
    m_sizeOf            (_sizeOf),
    m_outputOperator    (0),
    m_lessOperator      (0),
    m_equalsOperator    (0),
    m_destructor        (0)
{

}

MetaType::~MetaType()
{
    delete m_outputOperator;
    delete m_lessOperator;
    delete m_equalsOperator;
    delete m_destructor;
}

std::type_index MetaType::type(const char *_typeName)
{
    auto it = m_metaFactoryData.m_nameToTypeId.find(_typeName);
    if(it != m_metaFactoryData.m_nameToTypeId.end())
    {
        return *it->second;
    }

    return typeid(InvalidType);
}

const char *MetaType::typeName(std::type_index _typeInfo)
{
    auto it =  m_metaFactoryData.m_typeToName.find(_typeInfo);
    if(it !=  m_metaFactoryData.m_typeToName.end())
    {
        return it->second;
    }

    return "";
}

bool MetaType::isRegistered(std::type_index _typeInfo)
{
    return m_metaFactoryData.m_typeToName.find(_typeInfo) != m_metaFactoryData.m_typeToName.end();
}

bool MetaType::isRegistered(const char *_typeName)
{
    return m_metaFactoryData.m_nameToTypeId.find(_typeName) != m_metaFactoryData.m_nameToTypeId.end();
}

std::type_index MetaType::getArrayElementType(std::type_index _index)
{
    auto it = m_metaFactoryData.m_listElementType.find(_index);
    if(it != m_metaFactoryData.m_listElementType.end())
    {
        return *it->second;
    }

    std::cerr << "ArrayType not registered for <" << _index.name() << ">" << std::endl;
    return typeid(InvalidType);
}

void MetaType::registerArrayType(std::type_index _listType, std::type_index _elementType)
{
    m_metaFactoryData.m_indexList.push_back(new std::type_index(_elementType));
    m_metaFactoryData.m_listElementType[_listType] = m_metaFactoryData.m_indexList.back();
}

void MetaType::registerType(std::type_index _typeInfo, const char *_typeName, int _typeSize)
{
    //std::cout << "TypeName:" << _typeName << " | Size:" << _typeSize << "\n";

    m_metaFactoryData.createMetaIfNoExist(_typeInfo, _typeSize, _typeName);
}

bool MetaType::registerLessOperator(std::type_index _typeInfo, MetaTypeLessBase *_lessOperator)
{
    MetaType *metaType = m_metaFactoryData.getMetaType(_typeInfo);
    if(!metaType)
    {
        delete _lessOperator;
        return false;
    }

    delete metaType->m_lessOperator;
    metaType->m_lessOperator = _lessOperator;

    return true;
}

bool MetaType::registerEqualsOperator(std::type_index _typeInfo, MetaTypeEqualsBase *_equalsOperator)
{
    MetaType *metaType = m_metaFactoryData.getMetaType(_typeInfo);
    if(!metaType)
    {
        delete _equalsOperator;
        return false;
    }

    delete metaType->m_equalsOperator;
    metaType->m_equalsOperator = _equalsOperator;

    return true;
}

bool MetaType::registerOutputOperator(std::type_index _typeInfo, MetaTypeOutputBase *_outputOperator)
{
    MetaType *metaType = m_metaFactoryData.getMetaType(_typeInfo);
    if(!metaType)
    {
        delete _outputOperator;
        return false;
    }

    delete metaType->m_outputOperator;
    metaType->m_outputOperator = _outputOperator;

    return true;
}

bool MetaType::registerDestructor(std::type_index _typeInfo, MetaTypeDestructorBase *_destructor)
{
    MetaType *metaType = m_metaFactoryData.getMetaType(_typeInfo);
    if(!metaType)
    {
        delete _destructor;
        return false;
    }

    delete metaType->m_destructor;
    metaType->m_destructor = _destructor;

    return true;
}

bool MetaType::invokeLessOperator(std::type_index _typeIndex, const void *o1, const void *o2)
{
    MetaType *metaType = m_metaFactoryData.getMetaType(_typeIndex);
    if(!metaType)
    {
        std::cerr << "Type <" << _typeIndex.name() << "> not registered in meta system\n";
        return false;
    }
    if(!metaType->m_lessOperator)
    {
        std::cerr << "Type <" << MetaType::typeName(_typeIndex) << "> have no less operator\n";
        return false;
    }

    return metaType->m_lessOperator->lessOperator(o1, o2);
}

bool MetaType::invokeEqualsOperator(std::type_index _typeIndex, const void *o1, const void *o2)
{
    MetaType *metaType = m_metaFactoryData.getMetaType(_typeIndex);
    if(!metaType)
    {
        std::cerr << "Type <" << _typeIndex.name() << "> not registered in meta system\n";
        return false;
    }
    if(!metaType->m_equalsOperator)
    {
        std::cerr << "Type <" << MetaType::typeName(_typeIndex) << "> have no equals operator\n";
        return false;
    }

    return metaType->m_equalsOperator->equalsOperator(o1, o2);
}

bool MetaType::invokeOutputOperator(std::type_index _typeIndex, std::ostream &ss, const void *o1)
{
    MetaType *metaType = m_metaFactoryData.getMetaType(_typeIndex);
    if(!metaType)
    {
        std::cerr << "Type <" << _typeIndex.name() << "> not registered in meta system\n";
        return false;
    }
    if(!metaType->m_outputOperator)
    {
        std::cerr << "Type <" << MetaType::typeName(_typeIndex) << "> have no output operator\n";
        return false;
    }

    metaType->m_outputOperator->outputOperator(ss, o1);
    return true;
}

bool MetaType::invokeDestructor(std::type_index _typeIndex, void *o1)
{
    MetaType *metaType = m_metaFactoryData.getMetaType(_typeIndex);
    if(metaType && metaType->m_destructor)
    {
        metaType->m_destructor->destruct(o1);
        return true;
    }

    return false;
}


}
