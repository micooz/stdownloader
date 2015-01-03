#include <json/json.h>
#include "IListStruct.h"
#include "ListCollection.h"
#include "Resource.h"

namespace songtaste
{

    ListCollection::ListCollection()
    {

    }

    ListCollection::~ListCollection()
    {
        for (IListStruct *item : _data) {
            SAFERELEASE(item);
        }
    }

    void ListCollection::add(IListStruct *item)
    {
        _data.push_back(item);
    }

    const std::string ListCollection::toJsonString(bool compress /* = true */)
    {
        Json::Writer *writer = nullptr;
        if (compress) {
            writer = new Json::FastWriter;
        } else {
            writer = new Json::StyledWriter;
        }

        Json::Value root;

        for (IListStruct *item : _data) {
            root.append(item->toJson());
        }
        std::string json = writer->write(root);

        SAFERELEASE(writer);
        return json;
    }

}
