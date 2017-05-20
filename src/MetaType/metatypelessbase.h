#ifndef METATYPELESSBASE_H
#define METATYPELESSBASE_H

namespace PropertySystemNS
{

class MetaTypeLessBase
{
public:
    virtual bool lessOperator(const void *o1, const void *o2) = 0;

    virtual ~MetaTypeLessBase() {}
};

template<class Type>
class MetaTypeLess : public MetaTypeLessBase
{
public:
    virtual bool lessOperator(const void *o1, const void *o2) override
    {
        return *static_cast<const Type*>(o1) < *static_cast<const Type*>(o2);
    }
};

}

#endif // METATYPELESSBASE_H
