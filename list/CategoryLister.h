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

#include <boost/asio.hpp>
#include <avhttp.hpp>
#include "ILister.h"

namespace songtaste
{
    class ListCollection;

    class CategoryLister : public ILister
    {
    public:
        explicit CategoryLister(bool cache = false);
        ~CategoryLister();

        ListCollection *getListAt(const unsigned int);

        ListCollection *getMusicByCatid(const unsigned int catid, unsigned int page = 1);

    private:
        bool _cache;
        
        std::string _url_category;
        std::string _url_catsong;
        std::string _regex_category;
        std::string _regex_catsong;

        boost::asio::io_service _io;
        avhttp::http_stream _http;

        ListCollection *_catlist;
        ListCollection *_musiclist;
    };

}
#endif // CATEGORYLISTER_H
