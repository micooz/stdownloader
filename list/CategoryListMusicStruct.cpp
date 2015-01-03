#include <json/json.h>
#include "CategoryListMusicStruct.h"
#include "Resource.h"

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

    void CategoryListMusicStruct::parseJson(const std::string &jsonstr)
    {
        Json::Reader reader;
        Json::Value  root;

        if (!reader.parse(jsonstr, root)) {
            throw std::logic_error(constant::error::load_cache_error);
        }

        parseJson(root);
    }

    void CategoryListMusicStruct::parseJson(const Json::Value &jsonval)
    {
        songid   = jsonval["songid"  ].asString();
        songname = jsonval["songname"].asString();
        recnum   = jsonval["recnum"  ].asString();
    }

}
