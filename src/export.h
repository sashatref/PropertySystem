#ifndef PROPERTYSYSTEM_EXPORT_H
#define PROPERTYSYSTEM_EXPORT_H



#if defined(PROPERTY_SYSTEM_DEFINE)
#  define PROPERTY_SYSTEM_EXPORT __declspec(dllexport)
#else

    #ifdef STATIC
        #define PROPERTY_SYSTEM_EXPORT
    #else
        #define PROPERTY_SYSTEM_EXPORT __declspec(dllimport)
    #endif
#endif

#endif //PROPERTYSYSTEM_EXPORT_H
