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

    class CategoryLister : public ILister
    {
    public:
        explicit CategoryLister(bool cache = false);
        ~CategoryLister();

        ListCollection *getListAt(const unsigned int);

    private:
        bool _cache;
        
        std::string _url_category;
        std::string _regex_category;

        boost::asio::io_service _io;
        avhttp::http_stream _http;

        ListCollection *_catlist;
    };

}
#endif // CATEGORYLISTER_H
