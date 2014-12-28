#include <json/json.h>
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

}
