#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <map>
#include "Downloader.h"
#include "Configure.h"
#include "Sampler.h"

namespace songtaste {
    
    Downloader::Downloader()
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
        if(_http.is_open()){
            _http.close();
        }
    }
    
    void Downloader::download(unsigned int songid, const MInfo info) {
        boost::system::error_code ec;
        
        std::map<string,string> form;
        form["str"] = info->midurl;
        form["sid"] = songid;
        
        request_opts req_opts = post_form(_http, form);
        req_opts.remove(avhttp::http_options::connection);
        req_opts.insert(avhttp::http_options::connection, "keep-alive");
        _http.request_options(req_opts);
        _http.open(_url_time, ec);
        if(ec){
            throw error(ec.message());
        }
        
        std::stringstream ss;
        ss << &_http;
        string url = ss.str();
        
        std::ofstream fout;
        std::string suffix, filename;
        suffix   = info->songurl.substr(url.find_last_of("."));
        filename = info->songname + suffix;
        
        fout.open(filename, std::ios::binary);
        if(!fout.is_open()){
            throw error("cannot create file: " + filename);
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
            
            fout.write(buf, bytes_transferred);
            
        }while(!ec && bytes_transferred);
        
        fout.flush();
    }
    
    void 
    Downloader::download(unsigned int songid, const string &dir, const string &name) {
        //create sub folders
        boost::system::error_code ec;
        boost::filesystem::create_directories(boost::filesystem::path(dir), ec);
        if (ec) {
            throw ec.message();
        }
        
        MInfo info = getMusicInfo(songid);
        info->songname = dir + ((name.empty())?info->songname:name);
        this->download(songid, info);
    }
    
    MInfo 
    Downloader::getMusicInfo(unsigned int songid) {
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
    Downloader::map_to_query(const KeyValues &key_values) {
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
    
    request_opts 
    Downloader::post_form(http_stream &stream, const KeyValues &key_values) {
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
    
}
