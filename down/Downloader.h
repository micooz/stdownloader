#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <boost/asio.hpp>
#include <string>
#include <stdexcept>
#include <avhttp.hpp>
#include "MusicInfo.h"

namespace songtaste{
    
    typedef std::string string;
    typedef std::logic_error error;
    
    class Downloader {
    public:
        explicit Downloader();
        ~Downloader();
        
        void download(unsigned int songid, const string &path);
        
        MInfo getMusicInfo(unsigned int songid);
        
    private:
        string _url_down;
        string _regex_down;
        boost::asio::io_service _io;
        avhttp::http_stream _http;
    };
    
}

#endif // DOWNLOADER_H
