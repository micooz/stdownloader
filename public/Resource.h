//
// Resource.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

namespace songtaste
{
    namespace constant
    {
#ifndef CONST(var,val)
#define CONST(var,val) const std::string var = val
#endif
        namespace config
        {
            CONST(urls,         "urls"          );
            CONST(recommend,    "recommend"     );
            CONST(category,     "category"      );
            CONST(catsong,      "catsong"       );
            CONST(categorylist, "categorylist"  );

            CONST(regexs,       "regexs"        );


        }
        namespace error
        {
            CONST(configure_error, "configure item is empty");
            CONST(page_error, "page error");
        }

    }
}

#endif // RESOURCE_H
