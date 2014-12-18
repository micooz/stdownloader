//
// AlbumLister.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef ALBUMLISTER_H
#define ALBUMLISTER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <avhttp.hpp>
#include "ILister.h"

namespace songtaste {

    class AlbumLister : public ILister {
    public:
        //function MSL(SongName, SongID, UName, UID, UIcon, RecWidth, RateUID, RateDT, RateUName)
        explicit AlbumLister();
        ~AlbumLister();

        IListStruct* getList();
    private:
        std::string _url_recommend;
        std::string _regex_pattern;
        avhttp::http_stream _http;
    };
}

#endif // ALBUMLISTER_H
