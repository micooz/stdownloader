//
// CategoryLister.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef CATEGORYLISTER_H
#define CATEGORYLISTER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "ILister.h"

namespace songtaste {

    class CategoryLister : public ILister {
    public:
        explicit CategoryLister();
        ~CategoryLister();

        ListCollection getListAt(const unsigned int page = 1);
    private:
        string _url_category;
        string _regex_pattern;
    };

}
#endif // CATEGORYLISTER_H
