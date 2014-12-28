#include <json/json.h>
#include "CategoryListStruct.h"

namespace songtaste
{

    CategoryListStruct::CategoryListStruct()
    {
    }

    CategoryListStruct::~CategoryListStruct()
    {
    }

    const Json::Value CategoryListStruct::toJson()
    {
        Json::Value root;

        root["catid"    ] = catid;
        root["catname"  ] = catname;
        root["catnum"   ] = catnum;
        root["idx"      ] = idx;
        root["width"    ] = width;

        return root;
    }

}
