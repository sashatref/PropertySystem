#ifndef VARIANTOUTPUT_H
#define VARIANTOUTPUT_H

#include "../export.h"
#include <ostream>

namespace PropertySystemNS
{

class VariantOutputBase
{
public:
    VariantOutputBase() {}
    virtual ~VariantOutputBase() {}

    virtual void output(std::ostream &ss, const void *_input) const = 0;
};

template<class Type>
class VariantOutput : public VariantOutputBase
{
public:
    VariantOutput() {}
    virtual ~VariantOutput() {}

    virtual void output(std::ostream &ss, const void *_input) const override
    {
        ss << *static_cast<const Type*>(_input);
    }
};

}


#endif // VARIANTOUTPUT_H
