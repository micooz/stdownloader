#include <boost/filesystem.hpp>
#include "Utils.hpp"
#include "ICache.h"
#include "ListCollection.h"

namespace songtaste
{

    ICache::ICache()
    {

    }

    ICache::~ICache()
    {

    }

    bool ICache::exsit()
    {
        return boost::filesystem::exists(file());
    }

    void ICache::save(ListCollection *collection)
    {
        assert(collection != nullptr);
        std::ofstream out(file(), std::ios::binary);
        std::string jsonstr = collection->toJsonString();
        out << clearspace(jsonstr);
        out.flush();
        out.close();
    }

}
