#include <json/json.h>
#include "Resource.h"
#include "RecommendListStruct.h"

namespace songtaste
{

    RecommendListStruct::RecommendListStruct()
    {
    }

    RecommendListStruct::~RecommendListStruct()
    {
    }

    const Json::Value RecommendListStruct::toJson()
    {
        Json::Value root;

        root["songname" ]  = songname;
        root["songid"   ]  = songid;
        root["uname"    ]  = uname;
        root["uid"      ]  = uid;
        root["uicon"    ]  = uicon;
        root["recwidth" ]  = recwidth;
        root["rateuid"  ]  = rateuid;
        root["ratedt"   ]  = ratedt;
        root["rateuname"]  = rateuname;

        return root;
    }

    void RecommendListStruct::parseJson(const std::string &jsonstr)
    {
        Json::Reader reader;
        Json::Value root;
        if (!reader.parse(jsonstr, root)) {
            throw std::logic_error(constant::error::load_cache_error);
        }
        parseJson(root);
    }
    
    void RecommendListStruct::parseJson(const Json::Value &jsonval)
    {
        songname    = jsonval["songname"   ].asString();
        songid      = jsonval["songid"     ].asString();
        uname       = jsonval["uname"      ].asString();
        uid         = jsonval["uid"        ].asString();
        uicon       = jsonval["uicon"      ].asString();
        recwidth    = jsonval["recwidth"   ].asString();
        rateuid     = jsonval["rateuid"    ].asString();
        ratedt      = jsonval["ratedt"     ].asString();
        rateuname   = jsonval["rateuname"  ].asString();
    }

}
