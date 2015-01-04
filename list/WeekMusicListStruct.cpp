#include <json/json.h>
#include "WeekMusicListStruct.h"
#include "Resource.h"

namespace songtaste
{

    WeekMusicListStruct::WeekMusicListStruct()
    {

    }

    WeekMusicListStruct::~WeekMusicListStruct()
    {

    }

    const Json::Value WeekMusicListStruct::toJson()
    {
        Json::Value root;

        root["idx"      ] = idx;
        root["songid"   ] = songid;
        root["songname" ] = songname;
        root["singer"   ] = singer;
        root["sex"      ] = sex;
        root["uid"      ] = uid;
        root["uname"    ] = uname;
        root["width"    ] = width;
        root["lsnnum"   ] = lsnnum;

        return root;
    }

    void WeekMusicListStruct::parseJson(const std::string &jsonstr)
    {
        Json::Reader reader;
        Json::Value  root;

        if (!reader.parse(jsonstr, root)) {
            throw std::logic_error(constant::error::load_cache_error);
        }

        parseJson(root);
    }

    void WeekMusicListStruct::parseJson(const Json::Value &jsonval)
    {
        idx      = jsonval["idx"     ].asString();
        songid   = jsonval["songid"  ].asString();
        songname = jsonval["songname"].asString();
        singer   = jsonval["singer"  ].asString();
        uid      = jsonval["uid"     ].asString();
        uname    = jsonval["uname"   ].asString();
        width    = jsonval["width"   ].asString();
        lsnnum   = jsonval["lsnnum"  ].asString();
    }

}
