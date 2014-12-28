//
// CategoryListStruct.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef CATEGORYLISTSTRUCT_H
#define CATEGORYLISTSTRUCT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "IListStruct.h"

namespace songtaste
{

    class CategoryListStruct : public IListStruct
    {
    public:
        explicit CategoryListStruct();
        ~CategoryListStruct();

        const Json::Value toJson(void);

    public:
        std::string idx;
        std::string catid;
        std::string catname;
        std::string width;
        std::string catnum;
    };

}

#endif // CATEGORYLISTSTRUCT_H
