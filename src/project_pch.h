#ifndef H_PROJECT_PCH_H
#define H_PROJECT_PCH_H

#include <map>
#include <vector>
#include <type_traits>
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <memory>
#include <list>

#ifdef _DEBUG
    #ifdef USE_VLD
        #include <vld.h>
    #endif
#endif

struct cmp_str
{
   bool operator()(char const *a, char const *b) const
   {
      return std::strcmp(a, b) < 0;
   }
};

#endif //H_PROJECT_PCH_H
