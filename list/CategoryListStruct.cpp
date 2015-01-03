#include <json/json.h>
#include "Resource.h"
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

    void CategoryListStruct::parseJson(const std::string &jsonstr)
    {
        Json::Reader reader;
        Json::Value  root;
        
        if (!reader.parse(jsonstr, root)) {
            throw std::logic_error(constant::error::load_cache_error);
        }
        
        parseJson(root);
    }
    
    void CategoryListStruct::parseJson(const Json::Value &jsonval)
    {
        catid   = jsonval["catid"  ].asString();
        catname = jsonval["catname"].asString();
        catnum  = jsonval["catnum" ].asString();
        idx     = jsonval["idx"    ].asString();
        width   = jsonval["width"  ].asString();
    }

}
