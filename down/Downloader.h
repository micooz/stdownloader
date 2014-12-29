#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <string>
#include <array>
#include <fstream>
#include <stdexcept>
#include <avhttp.hpp>
#include "MusicInfo.h"

namespace songtaste
{
    typedef std::map<std::string, std::string> KeyValues;

    class Downloader
    {
    public:
        explicit Downloader();
        ~Downloader();

        void download(unsigned int songid, const string &dir, const string &name);

        MInfo getMusicInfo(unsigned int songid);
    protected:
        void download(unsigned int songid, const MInfo info);

        std::string map_to_query(const KeyValues &key_values);

        avhttp::request_opts post_form(avhttp::http_stream &stream, const KeyValues &key_values);
    private:
        boost::asio::io_service io;
        avhttp::http_stream _http;
        std::string _url_down;
        std::string _url_time;
        std::string _regex_down;
    };

}

#endif // DOWNLOADER_H
