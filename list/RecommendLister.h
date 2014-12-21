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

#include "ILister.h"

namespace songtaste {

    class RecommendLister : public ILister {
    public:
        explicit RecommendLister();
        ~RecommendLister();

        ListCollection getListAt(const unsigned int page = 1);

    private:
        std::string _url_recommend;
        std::string _regex_pattern;
    };

}
#endif // RECOMMENDLISTER_H
