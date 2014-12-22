#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <string>
#include <array>
#include <fstream>
#include <stdexcept>
#include <avhttp.hpp>
#include "MusicInfo.h"

namespace songtaste{
    
    using namespace avhttp;
    
    typedef std::string string;
    typedef std::logic_error error;
    typedef std::map<std::string, std::string> KeyValues;
    
    class Downloader {
    public:
        explicit Downloader(boost::asio::io_service &io);
        ~Downloader();
        
        void download(unsigned int songid, const string &path);
        
        MInfo getMusicInfo(unsigned int songid);
    protected:
        std::string map_to_query(const KeyValues& key_values);
        
        avhttp::request_opts post_form(http_stream& stream, const KeyValues& key_values);
        
//        void handle_open(const boost::system::error_code &ec);
        
//        void handle_read(int bytes_transferred, const boost::system::error_code &ec);
        
    private:
        string _url_down;
        string _url_time;
        string _regex_down;
        
        avhttp::http_stream _http;
        std::array<char,1024> _buffer;
        std::ofstream _fout;
    };
    
}

#endif // DOWNLOADER_H
