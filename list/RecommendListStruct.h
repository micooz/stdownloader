//
// RecommendListStruct.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef RECOMMENDLISTSTRUCT_H
#define RECOMMENDLISTSTRUCT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <string>
#include "IListStruct.h"

namespace songtaste
{

    class RecommendListStruct : public IListStruct
    {
    public:
        explicit RecommendListStruct();
        ~RecommendListStruct();

        const Json::Value toJson(void);

    public:
        std::string songname;
        std::string songid;
        std::string uname;
        std::string uid;
        std::string uicon;
        std::string recwidth;
        std::string rateuid;
        std::string ratedt;
        std::string rateuname;
    };

}

#endif // RECOMMENDLISTSTRUCT_H
