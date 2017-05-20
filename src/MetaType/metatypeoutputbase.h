#ifndef METATYPEOUTPUTBASE_H
#define METATYPEOUTPUTBASE_H

#include <ostream>

namespace PropertySystemNS
{

class MetaTypeOutputBase
{
public:
    virtual ~MetaTypeOutputBase() {}
    virtual void outputOperator(std::ostream &ss, const void *o) = 0;
};

template<class Type>
class MetaTypeOutput: public MetaTypeOutputBase
{
public:
    virtual void outputOperator(std::ostream &ss, const void *o) override
    {
        ss << *static_cast<const Type*>(o);
    }
};

}

#endif // METATYPEOUTPUTBASE_H
