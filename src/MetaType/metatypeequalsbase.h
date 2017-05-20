#ifndef METATYPEEQUALSBASE_H
#define METATYPEEQUALSBASE_H


namespace PropertySystemNS
{

class MetaTypeEqualsBase
{
public:
    virtual ~MetaTypeEqualsBase() {}
    virtual bool equalsOperator(const void *o1, const void *o2) = 0;
};

template<class Type>
class MetaTypeEquals : public MetaTypeEqualsBase
{
public:
    virtual bool equalsOperator(const void *o1, const void *o2) override
    {
        return *static_cast<const Type*>(o1) == *static_cast<const Type*>(o2);
    }
};

}

#endif // METATYPEEQUALSBASE_H
