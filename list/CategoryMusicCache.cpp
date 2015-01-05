#include <boost/format.hpp>
#include <fstream>
#include "CategoryMusicCache.h"
#include "Configure.h"
#include "CategoryListMusicStruct.h"
#include "ListCollection.h"
#include "Resource.h"

namespace songtaste
{

    CategoryMusicCache::CategoryMusicCache(unsigned int catid, unsigned int page /* = 1 */)
        : _page(page), _catid(catid)
    {
        Configure &config = *(Configure::getInstance());

        _dir = config[constant::config::cachepath].asString();
    }

    CategoryMusicCache::~CategoryMusicCache()
    {

    }

    void
    CategoryMusicCache::load(ListCollection *list)
    {
        assert(list != nullptr);

        std::ifstream in(file(), std::ios::binary);
        std::string json;
        in >> json;
        in.close();

        list->parseJsonArray<CategoryListMusicStruct>(json);
    }

    std::string
    CategoryMusicCache::file() const
    {
        boost::format formater("%s%s%s%d%s%d%s");
        formater
        % _dir
        % constant::config::catsong
        % "_"
        % _catid
        % "_"
        % _page
        % ".json";

        return formater.str();
    }

}
