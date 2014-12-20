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

#include <vector>
#include <memory>
#include "ILister.h"
#include "CategoryListStruct.h"

namespace songtaste {

    class CategoryLister : public ILister {
    public:
        explicit CategoryLister();
        ~CategoryLister();

        ListCollection getCatList();

        ListCollection getListAt(const unsigned int catid, const unsigned int page = 1);

    private:
        string _url_category;
        string _url_catsong;
        string _regex_category;
        string _regex_catsong;
    };

}
#endif // CATEGORYLISTER_H
