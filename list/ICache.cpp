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

        namespace fs = boost::filesystem;
        fs::path fp(file());
        fs::path dir = fp.branch_path();
        if (!fs::exists(dir)) {
            if (!fs::create_directories(dir)) {
                throw std::logic_error(constant::error::create_directory_error + ":" + dir.string());
            }
        }

        std::ofstream out(file(), std::ios::binary);
        std::string jsonstr = collection->toJsonString();
        out << convertSpace(jsonstr);
        out.flush();
        out.close();
    }

}
