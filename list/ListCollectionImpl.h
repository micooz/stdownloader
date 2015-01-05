#ifndef LISTCOLLECTIONIMPL
#define LISTCOLLECTIONIMPL

#include <json/json.h>
#include "IListStruct.h"
#include "Resource.h"
#include "Utils.hpp"

namespace songtaste
{
    class ListCollection;

    template<typename T>
    void ListCollection::parseJsonArray(const std::string &jsonstr)
    {
        Json::Reader reader;
        Json::Value  root;

        std::string json = convertSpace(jsonstr, true);

        if (!reader.parse(json, root)) {
            throw std::logic_error(constant::error::load_cache_error);
        }

        typedef Json::Value::iterator iterator;

        iterator begin = root.begin();
        iterator end   = root.end();

        for (auto i = begin; i != end; ++i) {
            IListStruct *item = new T;
            item->parseJson(*i);
            add(item);
        }
    }

}

#endif // LISTCOLLECTIONIMPL
