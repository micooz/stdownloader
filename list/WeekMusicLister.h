#ifndef WEEKMUSICLISTER_H
#define WEEKMUSICLISTER_H

#include <boost/asio.hpp>
#include <avhttp.hpp>
#include "ILister.h"

namespace songtaste
{

    class WeekMusicLister : public ILister
    {
    public:
        explicit WeekMusicLister(bool cache = false);
        
        ~WeekMusicLister();
        
        ListCollection *getListAt(const unsigned int page = 1);
    private:
        bool _cache;
        
        std::string _url_weekrecommend;
        std::string _regex_weekrecommend;
        
        boost::asio::io_service _io;
        avhttp::http_stream _http;
        
        ListCollection *_weekcommendlist;
    };

}

#endif // WEEKMUSICLISTER_H
