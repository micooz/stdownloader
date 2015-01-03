#include <boost/filesystem.hpp>
#include <fstream>
#include <assert.h>
#include "CCache.h"
#include "Configure.h"
#include "Resource.h"
#include "ListCollection.h"
#include "CategoryListStruct.h"

namespace songtaste
{

    static std::string clearspace(const std::string &str)
    {
        typedef std::string::const_iterator iterator;
        iterator begin = str.cbegin();
        iterator end   = str.cend();
        std::string result;
        result.reserve(str.size());
        for (auto i = begin; i != end; ++i) {
            if (*i == ' ')
                continue;
            result.push_back(*i);
        }
        return result;
    }

    CCache::CCache()
    {
        using namespace boost::filesystem;
        Configure &config = *(Configure::getInstance());

        _dir = config[constant::config::cachepath].asString();
        if (*(_dir.end() - 1) != '/') {
            _dir.push_back('/');
        }

        boost::system::error_code ec;
        create_directories(_dir, ec);
        if (ec) {
            throw std::logic_error(constant::error::create_directory_error + ": " + _dir);
        }
    }

    CCache::~CCache()
    {

    }

    bool CCache::exsit(const CCache::Type &type)
    {
        return boost::filesystem::exists(getPath(type));
    }

    void CCache::save(ListCollection *collection, const CCache::Type &type)
    {
        assert(collection != nullptr);
        std::ofstream out(getPath(type), std::ios::binary);
        std::string jsonstr = collection->toJsonString();//gb2312
        //convert to wide string
        out << clearspace(jsonstr);
        out.flush();
        out.close();
    }

    void CCache::load(const CCache::Type &type, ListCollection *pList)
    {
        assert(pList != nullptr);

        std::ifstream in(getPath(type), std::ios::binary);
        std::string json;
        in >> json;
        in.close();

        switch (type) {
        case CATEGORY:
            pList->parseJsonArray<CategoryListStruct>(json);
            break;
        }
    }

    std::string CCache::getPath(const CCache::Type &type)
    {
        std::string file(_dir);
        switch (type) {
        case CATEGORY:
            file.append(constant::config::category);
            break;
        case RECOMMEND:
            
            break;
        default:
            break;
        }
        file.append(".json");
        return file;
    }

}
