#include <boost/filesystem.hpp>
#include "Utils.hpp"
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

    bool
    WeekCache::exsit()
    {
        return boost::filesystem::exists(file());
    }

    void
    WeekCache::save(ListCollection *collection)
    {
        assert(collection != nullptr);
        std::ofstream out(file(), std::ios::binary);
        std::string jsonstr = collection->toJsonString();
        out << clearspace(jsonstr);
        out.flush();
        out.close();
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
