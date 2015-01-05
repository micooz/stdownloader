#include <fstream>
#include <assert.h>
#include "Configure.h"
#include "ListCollection.h"
#include "Resource.h"
#include "WeekMusicCache.h"
#include "WeekMusicListStruct.h"

namespace songtaste
{

    WeekMusicCache::WeekMusicCache()
    {
        Configure &config = *(Configure::getInstance());

        _dir = config[constant::config::cachepath].asString();
    }

    WeekMusicCache::~WeekMusicCache()
    {

    }

    void WeekMusicCache::load(ListCollection *list)
    {
        assert(list != nullptr);

        std::ifstream in(file(), std::ios::binary);
        std::string json;
        in >> json;
        in.close();

        list->parseJsonArray<WeekMusicListStruct>(json);
    }

    std::string WeekMusicCache::file() const
    {
        std::string path(_dir);
        path.append(constant::config::chartmusic);
        path.append(".json");
        return path;
    }

}



