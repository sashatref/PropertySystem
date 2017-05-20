#ifndef VARIANTCONVERTER_H
#define VARIANTCONVERTER_H

#include "../export.h"

#include <ostream>
#include <functional>

namespace PropertySystemNS
{

class VariantConverterBase
{
public:
    VariantConverterBase() {}
    virtual ~VariantConverterBase() {}

    virtual void* convert(const void* _input) const = 0;
};

template<class From, class To>
class VariantConverter : public VariantConverterBase
{
public:
    typedef std::function<To(const From &)> ConvertFunc;

    VariantConverter(ConvertFunc _convertFunc):
        m_converter(_convertFunc)
    {

    }

    virtual ~VariantConverter()
    {

    }

    virtual void *convert(const void *_input) const override
    {
        const From* fromPtr = static_cast<const From*>(_input);
        To *toPtr = new To(m_converter(*fromPtr));
        return toPtr;
    }

    ConvertFunc m_converter;
};

#pragma warning(push, 0)

template<class From, class To>
class InternalTypeConverter : public VariantConverterBase
{
public:
    virtual void *convert(const void *_input) const override
    {
        return new To(static_cast<To>(*static_cast<const From*>(_input)));
    }
};

#pragma warning(pop)


}

#endif // VARIANTCONVERTER_H
