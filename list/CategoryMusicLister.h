#ifndef CATEGORYMUSICLISTER_H
#define CATEGORYMUSICLISTER_H

#include <boost/asio.hpp>
#include <avhttp.hpp>
#include "ILister.h"

namespace songtaste {
    
    class CategoryMusicLister : public ILister
    {
    public:
        explicit CategoryMusicLister(unsigned int catid, bool cache = false);
        
        ~CategoryMusicLister();
        
        ListCollection *getListAt(const unsigned int page = 1);
        
    private:
        bool _cache;
        unsigned int _catid;
        
        std::string _url_catsong;
        std::string _regex_catsong;
        
        boost::asio::io_service _io;
        avhttp::http_stream _http;
        
        ListCollection *_musiclist;
    };
    
}

#endif // CATEGORYMUSICLISTER_H
