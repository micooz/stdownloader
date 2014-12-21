#include <boost/regex.hpp>
#include <streambuf>
#include "Downloader.h"
#include "Configure.h"

namespace songtaste {
    
    Downloader::Downloader()
        :_http(_io){
        Config config   = Configure::getInstance()->all();
        _url_down       = config["URLS"]["down"].asString();
        _regex_down     = config["REGEXS"]["down"].asString();
        
        if(_url_down.empty() || _regex_down.empty()){
            throw error("URLS->down cannot be empty");
        }
    }
    
    Downloader::~Downloader() {
        
    }
    
    // function WrtSongLine(SongID, SongName, Singer, IsBox, Idx, SongUrl, MidUrl){
    void Downloader::download(unsigned int songid, const string &path) {
        MInfo minfo = this->getMusicInfo(songid);
        
        
        
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
    
}
