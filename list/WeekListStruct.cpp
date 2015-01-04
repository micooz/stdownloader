#include <json/json.h>
#include <Resource.h>
#include "WeekListStruct.h"

namespace songtaste
{

    WeekListStruct::WeekListStruct()
    {

    }

    WeekListStruct::~WeekListStruct()
    {

    }

    const Json::Value WeekListStruct::toJson()
    {
        Json::Value root;

        root["weekfrom"] = weekfrom;
        root["weektime"] = weektime;

        return root;
    }

    void WeekListStruct::parseJson(const std::string &jsonstr)
    {
        Json::Reader reader;
        Json::Value  root;

        if (!reader.parse(jsonstr, root)) {
            throw std::logic_error(constant::error::load_cache_error);
        }

        parseJson(root);
    }

    void WeekListStruct::parseJson(const Json::Value &jsonval)
    {
        weekfrom = jsonval["weekfrom"].asString();
        weektime = jsonval["weektime"].asString();
    }

}


