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
