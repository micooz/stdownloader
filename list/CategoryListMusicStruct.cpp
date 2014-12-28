#include <json/json.h>
#include "CategoryListMusicStruct.h"

namespace songtaste
{

    CategoryListMusicStruct::CategoryListMusicStruct()
    {
    }

    CategoryListMusicStruct::~CategoryListMusicStruct()
    {
    }

    const Json::Value CategoryListMusicStruct::toJson()
    {
        Json::Value root;

        root["songid"   ] = songid;
        root["songname" ] = songname;
        root["recnum"   ] = recnum;

        return root;
    }

}
