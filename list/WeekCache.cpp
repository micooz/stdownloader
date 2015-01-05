#include <fstream>
#include <assert.h>
#include "Configure.h"
#include "ListCollection.h"
#include "Resource.h"
#include "WeekCache.h"
#include "WeekListStruct.h"

namespace songtaste
{

    WeekCache::WeekCache()
    {
        Configure &config = *(Configure::getInstance());

        _dir = config[constant::config::cachepath].asString();
    }

    WeekCache::~WeekCache()
    {

    }

    void
    WeekCache::load(ListCollection *list)
    {
        assert(list != nullptr);

        std::ifstream in(file(), std::ios::binary);
        std::string json;
        in >> json;
        in.close();

        list->parseJsonArray<WeekListStruct>(json);
    }

    std::string
    WeekCache::file() const
    {
        std::string path(_dir);
        path.append(constant::config::week);
        path.append(".json");
        return path;
    }

}
