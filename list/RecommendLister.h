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

#include <boost/asio.hpp>
#include <avhttp.hpp>
#include "ILister.h"

namespace songtaste
{
    class ListCollection;

    class RecommendLister : public ILister
    {
    public:
        explicit RecommendLister(bool cache = false);
        ~RecommendLister();

        ListCollection *getListAt(const unsigned int page = 1);

    private:
        bool _cache;
        
        std::string _url_recommend;
        std::string _regex_pattern;

        boost::asio::io_service _io;
        avhttp::http_stream _http;

        ListCollection *_list;
    };

}
#endif // RECOMMENDLISTER_H
