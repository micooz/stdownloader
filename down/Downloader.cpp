#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <map>
#include "Downloader.h"
#include "Configure.h"
#include "Sampler.h"
#include "Resource.h"

namespace songtaste
{

    Downloader::Downloader()
        : _http(io)
    {
        Configure &config = *(Configure::getInstance());

        _url_down   = config[constant::config::urls][constant::config::down].asString();
        _url_time   = config[constant::config::urls][constant::config::time].asString();
        _regex_down = config[constant::config::regexs][constant::config::down].asString();

        if (_url_down.empty() || _regex_down.empty()) {
            throw std::logic_error(constant::error::configure_error);
        }

        std::string user_agent = config[constant::config::useragent].asString();

        if (!user_agent.empty()) {
            avhttp::request_opts opt;
            opt.insert(avhttp::http_options::user_agent, user_agent);
            _http.request_options(opt);
        }

    }

    Downloader::~Downloader()
    {
        if (_http.is_open()) {
            _http.close();
        }
    }

    void Downloader::download(unsigned int songid, const MInfo info)
    {
        boost::system::error_code ec;

        std::map<string, string> form;
        form["str"] = info->midurl;
        form["sid"] = songid;

        avhttp::request_opts req_opts = post_form(_http, form);
        req_opts.remove(avhttp::http_options::connection);
        req_opts.insert(avhttp::http_options::connection, "keep-alive");
        _http.request_options(req_opts);
        _http.open(_url_time, ec);
        if (ec) {
            throw std::logic_error(ec.message());
        }

        std::stringstream ss;
        ss << &_http;
        string url = ss.str();

        std::ofstream fout;
        std::string suffix, filename;
        suffix   = info->songurl.substr(url.find_last_of("."));
        filename = info->songname + suffix;

        fout.open(filename, std::ios::binary);
        if (!fout.is_open()) {
            throw std::logic_error("cannot create file: " + filename);
        }

        std::stringstream conv;
        conv << _url_down << songid;
        string referer = conv.str();

        _http.close();
        _http.request_options(avhttp::request_opts());
        req_opts.clear();
        req_opts.insert(avhttp::http_options::connection, "keep-alive");
        req_opts.insert(avhttp::http_options::accept, "*/*");
        req_opts.insert(avhttp::http_options::referer, referer);
        _http.request_options(req_opts);

        _http.open(url);

        std::stringstream num(_http.response_options().find(avhttp::http_options::content_length));
        unsigned long file_size;
        num >> file_size;

        char buf[1024];
        std::size_t trans_size          = 0;
        std::size_t bytes_transferred   = 0;
        do {
            bytes_transferred = _http.read_some(boost::asio::buffer(buf), ec);

            trans_size += bytes_transferred;

            Sampler::getInstance()->sampling(500, trans_size, file_size);

            fout.write(buf, bytes_transferred);

        } while (!ec && bytes_transferred);

        fout.flush();
    }

    void
    Downloader::download(unsigned int songid, const string &dir, const string &name)
    {
        //create sub folders
        boost::system::error_code ec;
        boost::filesystem::create_directories(boost::filesystem::path(dir), ec);
        if (ec) {
            throw std::logic_error(ec.message());
        }

        MInfo info = getMusicInfo(songid);
        info->songname = dir + ((name.empty()) ? info->songname : name);
        this->download(songid, info);
    }

    MInfo
    Downloader::getMusicInfo(unsigned int songid)
    {
        std::stringstream conv;
        boost::system::error_code ec;
        conv << _url_down << songid;
        string url = conv.str();
        _http.open(url, ec);
        if (ec) {
            throw std::logic_error(ec.message());
        }
        std::stringstream buf;
        buf << &_http;
        string html = buf.str();

        boost::regex pattern(_regex_down);
        boost::smatch matches;
        std::string::const_iterator s = html.begin();
        std::string::const_iterator e = html.end();

        MInfo info(new MusicInfo);

        boost::regex_search(s, e, matches, pattern);
        info->songid    = matches.str(1);
        info->songname  = matches.str(2);
        info->singer    = matches.str(3);
        info->isbox     = matches.str(4);
        info->idx       = matches.str(5);
        info->songurl   = matches.str(6);
        info->midurl    = matches.str(7);

        return info;
    }

    std::string
    Downloader::map_to_query(const KeyValues &key_values)
    {
        if (key_values.size() == 0) {
            return std::string();
        }

        std::stringstream ss;
        for (KeyValues::const_iterator iter = key_values.begin();
             iter != key_values.end();
             ++iter) {
            ss << iter->first << "=" << iter->second << "&";
        }

        const std::string &temp = ss.str();
        return std::string(temp.begin(), temp.begin() + temp.size() - 1);
    }

    avhttp::request_opts
    Downloader::post_form(avhttp::http_stream &stream, const KeyValues &key_values)
    {
        using namespace avhttp;
        const std::string &body = map_to_query(key_values);
        request_opts opts = stream.request_options();
        opts.remove(http_options::request_method);
        opts.remove(http_options::request_body);
        opts.remove(http_options::content_type);
        opts.remove(http_options::content_length);
        opts.insert(http_options::content_length, (boost::format("%1%") % body.size()).str());
        opts.insert(http_options::content_type, "application/x-www-form-urlencoded");
        opts.insert(http_options::request_body, body);
        opts.insert(http_options::request_method, "POST");
        stream.request_options(opts);
        return opts;
    }

}
