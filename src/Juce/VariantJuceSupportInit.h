#pragma once

#include <LogHelper.h>
#include <PropertySystem/Variant/variant.h>

PS_DECLARE_METATYPE(juce::String)

inline int juceStringToInt(const juce::String &_str)
{
	return _str.getIntValue();
}

inline juce::String intTojuceString(const int &_val)
{
	return juce::String(_val);
}

inline double juceStringToDouble(const juce::String &_str)
{
	return _str.getDoubleValue();
}

inline juce::String doubleTojuceString(const double &_val)
{
	return juce::String(_val, 2);
}

inline void registerVariantJuceSupport()
{
    PropertySystemNS::MetaType::registerOutputOperator<juce::String>();
    PropertySystemNS::MetaType::registerEqualsOperator<juce::String>();
    PropertySystemNS::MetaType::registerLessOperator<juce::String>();

	PropertySystemNS::registerVariantTypeConverter<int, juce::String>(intTojuceString);
	PropertySystemNS::registerVariantTypeConverter<juce::String, int>(juceStringToInt);

	PropertySystemNS::registerVariantTypeConverter<double, juce::String>(doubleTojuceString);
	PropertySystemNS::registerVariantTypeConverter<juce::String, double>(juceStringToDouble);
}


inline LogHelper &operator<<(LogHelper &_helper, const PropertySystemNS::Variant &_value)
{
	std::stringstream ss;
	ss << _value;
	_helper << ss.str();
	return _helper;
}
