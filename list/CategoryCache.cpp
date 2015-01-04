#include <boost/filesystem.hpp>
#include "Utils.hpp"
#include "Configure.h"
#include "ListCollection.h"
#include "Resource.h"
#include "CategoryCache.h"
#include "CategoryListStruct.h"

namespace songtaste
{

    CategoryCache::CategoryCache()
    {
        Configure &config = *(Configure::getInstance());

        _dir = config[constant::config::cachepath].asString();
    }

    CategoryCache::~CategoryCache()
    {

    }

    bool
    CategoryCache::exsit(void)
    {
        return boost::filesystem::exists(file());
    }

    void
    CategoryCache::save(ListCollection *collection)
    {
        assert(collection != nullptr);
        std::ofstream out(file(), std::ios::binary);
        std::string jsonstr = collection->toJsonString();
        out << clearspace(jsonstr);
        out.flush();
        out.close();
    }

    void
    CategoryCache::load(ListCollection *list)
    {
        assert(list != nullptr);

        std::ifstream in(file(), std::ios::binary);
        std::string json;
        in >> json;
        in.close();

        list->parseJsonArray<CategoryListStruct>(json);
    }

    std::string
    CategoryCache::file() const
    {
        std::string path(_dir);
        path.append(constant::config::category);
        path.append(".json");
        return path;
    }

}
