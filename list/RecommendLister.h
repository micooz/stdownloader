//
// RecommendLister.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef RECOMMENDLISTER_H
#define RECOMMENDLISTER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <avhttp.hpp>
#include "ILister.h"
#include "RecommendListStruct.h"

namespace songtaste {

    class RecommendLister : public ILister {
    public:
        explicit RecommendLister();
        ~RecommendLister();

        //implments
        ListCollection getListAt(const unsigned int page = 0);

        //addon functions

    private:
        std::string _url_recommend;
        std::string _regex_pattern;
        avhttp::http_stream _http;
    };

}
#endif // RECOMMENDLISTER_H
