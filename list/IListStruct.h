//
// IListStruct.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef ILISTSTRUCT_H
#define ILISTSTRUCT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#define SAFERELEASE(p) if(p) {delete p; p = nullptr;}

#include <string>

namespace Json
{
    class Value;
}

namespace songtaste
{
    class Json::Value;

    class IListStruct
    {
    public:
        explicit IListStruct();

        virtual ~IListStruct();

        virtual const Json::Value toJson(void) = 0;
        
        virtual void parseJson(const std::string &jsonstr) = 0;
        
        virtual void parseJson(const Json::Value &jsonval) = 0;
        
    };

}

#endif // ILISTSTRUCT_H
