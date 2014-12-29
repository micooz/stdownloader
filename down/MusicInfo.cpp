#include <json/json.h>
#include "MusicInfo.h"

namespace songtaste
{

    MusicInfo::MusicInfo()
    {

    }

    MusicInfo::~MusicInfo()
    {

    }

    std::string MusicInfo::toJson()
    {
        Json::FastWriter writer;
        Json::Value root;

        root["songid"   ] = songid;
        root["songname" ] = songname;
        root["singer"   ] = singer;
        root["isbox"    ] = isbox;
        root["idx"      ] = idx;
        root["songurl"  ] = songurl;
        root["midurl"   ] = midurl;

        return writer.write(root);
    }

}
