#include <boost/regex.hpp>
#include <map>
#include <streambuf>
#include "Downloader.h"
#include "Configure.h"
#include "Console.hpp"
#include "Sampler.h"

namespace songtaste {
    
    Downloader::Downloader(boost::asio::io_service &io)
        :_http(io){
        Config config   = Configure::getInstance()->all();
        _url_down       = config["URLS"]["down"].asString();
        _url_time       = config["URLS"]["time"].asString();
        _regex_down     = config["REGEXS"]["down"].asString();
        
        if(_url_down.empty() || _regex_down.empty()){
            throw error("URLS->down cannot be empty");
        }
    }
    
    Downloader::~Downloader() {
        if(_fout.is_open()){
            _fout.close();
        }
        
        if(_http.is_open()){
            _http.close();
        }
    }
    
    void Downloader::download(unsigned int songid, const string &path) {
        MInfo minfo = this->getMusicInfo(songid);
        boost::system::error_code ec;
        
        std::map<string,string> form;
        form["str"] = minfo->midurl;
        form["sid"] = songid;
        
        request_opts req_opts = post_form(_http, form);
        req_opts.remove(avhttp::http_options::connection);
        req_opts.insert(avhttp::http_options::connection, "keep-alive");
        //req_opts.insert(http_options::referer, url_login);
        //post
        _http.request_options(req_opts);
        //_http->max_redirects(0);//disable Location redirect
        _http.open(_url_time, ec);
        if(ec){
            throw error(ec.message());
        }
        
        std::stringstream ss;
        ss << &_http;
        string url = ss.str();
        
        _fout.open(path + ".mp3", std::ios::binary);
        if(!_fout.is_open()){
            throw error("cannot create file");
        }
        std::stringstream conv;
        conv << _url_down << songid;
        string referer = conv.str();
        
        _http.close();
        _http.request_options(request_opts());
        req_opts.clear();
        req_opts.insert(avhttp::http_options::connection, "keep-alive");
        req_opts.insert(avhttp::http_options::accept, "*/*");
        req_opts.insert(avhttp::http_options::referer, referer);
        _http.request_options(req_opts);
        
        std::cout << "opening " << url <<std::endl;
        
        //        _http.async_open(url, boost::bind(
        //                             &Downloader::handle_open,
        //                             this,
        //                             boost::asio::placeholders::error)
        //                         );
        _http.open(url);
        
        std::stringstream num(_http.response_options().find(http_options::content_length));
        unsigned long file_size;
        num >> file_size;
        
        char buf[1024];
        std::size_t trans_size          = 0;
        std::size_t bytes_transferred   = 0;
        do{
            bytes_transferred = _http.read_some(boost::asio::buffer(buf), ec);
            trans_size += bytes_transferred;
            
            Sampler::getInstance()->sampling(500, trans_size, file_size);
            
            _fout.write(buf, bytes_transferred);
            
        }while(!ec && bytes_transferred);
        
        _fout.flush();
        std::cout << trans_size << " bytes saved." << std::endl;
    }
    
    MInfo Downloader::getMusicInfo(unsigned int songid) {
        std::stringstream conv;
        boost::system::error_code ec;
        conv << _url_down << songid;
        string url = conv.str();
        _http.open(url, ec);
        if(ec){
            throw error(ec.message());
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
        //matches.str(0) is the original string
        info->songid    = matches.str(1);
        info->songname  = matches.str(2);
        info->singer    = matches.str(3);
        info->isbox     = matches.str(4);
        info->idx       = matches.str(5);
        info->songurl   = matches.str(6);
        info->midurl    = matches.str(7);
        
        return info;
    }
    
    std::string Downloader::map_to_query(const KeyValues &key_values) {
        if(key_values.size() == 0)
        {
            return std::string();
        }
        
        std::stringstream ss;
        for(KeyValues::const_iterator iter = key_values.begin();
            iter != key_values.end();
            ++iter)
        {
            ss << iter->first << "=" << iter->second << "&";
        }
        
        const std::string& temp = ss.str();
        return std::string(temp.begin(), temp.begin() + temp.size() - 1);
    }
    
    request_opts Downloader::post_form(http_stream &stream, const KeyValues &key_values) {
        const std::string& body = map_to_query(key_values);
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
    
    //    void Downloader::handle_open(const boost::system::error_code &ec) {
    
    //        if(ec){
    //            throw error(ec.message());
    //        }
    
    //        _http.async_read_some(boost::asio::buffer(_buffer), boost::bind(
    //                                  &Downloader::handle_read, this, 
    //                                  boost::asio::placeholders::bytes_transferred,
    //                                  boost::asio::placeholders::error)
    //                              );
    //    }
    
    //    void Downloader::handle_read(int bytes_transferred, const boost::system::error_code &ec) {
    //        static long long lbytes = 0;
    //        if (!ec) {
    //            _fout.write(_buffer.data(), bytes_transferred);
    //            _http.async_read_some(boost::asio::buffer(_buffer), boost::bind(
    //                                      &Downloader::handle_read, this,
    //                                      boost::asio::placeholders::bytes_transferred,
    //                                      boost::asio::placeholders::error)
    //                                  );
    //            lbytes += bytes_transferred;
    //        } else if (ec == boost::asio::error::eof) {
    //            _fout.write(_buffer.data(), bytes_transferred);
    //            lbytes += bytes_transferred;
    //        }
    //        _fout.flush();
    //        //Console console;
    //        //console << lbytes << " bytes received.";
    //    }
    
}
