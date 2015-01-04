#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include "Utils.hpp"
#include "Configure.h"
#include "Resource.h"
#include "RecommendCache.h"
#include "RecommendListStruct.h"
#include "ListCollection.h"

namespace songtaste
{

    RecommendCache::RecommendCache(unsigned int page /* = 1 */)
        : _page(page)
    {
        Configure &config = *(Configure::getInstance());

        _dir = config[constant::config::cachepath].asString();
    }

    RecommendCache::~RecommendCache()
    {

    }

    bool
    RecommendCache::exsit()
    {
        return boost::filesystem::exists(file());
    }

    void
    RecommendCache::save(ListCollection *collection)
    {
        assert(collection != nullptr);
        std::ofstream out(file(), std::ios::binary);
        std::string jsonstr = collection->toJsonString();
        out << clearspace(jsonstr);
        out.flush();
        out.close();
    }

    void
    RecommendCache::load(ListCollection *list)
    {
        assert(list != nullptr);

        std::ifstream in(file(), std::ios::binary);
        std::string json;
        in >> json;
        in.close();

        list->parseJsonArray<RecommendListStruct>(json);
    }

    std::string
    RecommendCache::file() const
    {
        boost::format formater("%s%s%s%d%s");
        formater
        % _dir
        % constant::config::recommend
        % "_"
        % _page
        % ".json";

        return formater.str();
    }

}



