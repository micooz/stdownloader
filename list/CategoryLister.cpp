#include <boost/regex.hpp>
#include "Configure.h"
#include "ListCollection.h"
#include "IListStruct.h"
#include "CategoryLister.h"
#include "CategoryListStruct.h"
#include "CategoryListMusicStruct.h"

namespace songtaste {
    
    CategoryLister::CategoryLister():
        _catlist(nullptr), _musiclist(nullptr), _http(_io){
        _url_category = Configure::getInstance()->all()["urls"]["category"].asString();
        _url_catsong = Configure::getInstance()->all()["urls"]["catsong"].asString();
        _regex_category = Configure::getInstance()->all()["regexs"]["categorylist"].asString();
        _regex_catsong = Configure::getInstance()->all()["regexs"]["catsong"].asString();
        
        if (_url_category.empty() || _regex_category.empty() || _regex_catsong.empty() || _url_catsong.empty()) {
            throw error("configure item is empty");
        }
        
        _catlist   = new ListCollection;
        _musiclist = new ListCollection;
    }
    
    CategoryLister::~CategoryLister() {
        SAFERELEASE(_catlist);
        SAFERELEASE(_musiclist);
    }
    
    ListCollection *
    CategoryLister::getListAt(const unsigned int) {
        boost::system::error_code ec;
        //open connection
        _http.open(_url_category, ec);
        if (ec) {
            throw error(ec.message());
        }
        std::stringstream ss;
        ss << &_http;
        std::string html = ss.str();
        
        boost::regex pattern(_regex_category);
        boost::smatch matches;
        std::string::const_iterator s = html.begin();
        std::string::const_iterator e = html.end();
        
        while (boost::regex_search(s, e, matches, pattern)) {
            auto cls = new CategoryListStruct;
            cls->idx      = matches.str(1);
            cls->catid    = matches.str(2);
            cls->catname  = matches.str(3);
            cls->width    = matches.str(4);
            cls->catnum   = matches.str(5);
            //add to container
            _catlist->add(cls);
            //iterate next matching
            s = matches[5].second;
        }
        
        return _catlist;
    }
    
    ListCollection *
    CategoryLister::getMusicByCatid(const unsigned int catid, unsigned int page) {
        boost::system::error_code ec;
        
        std::stringstream conv;
        conv << _url_catsong << "/cat" << catid << "/" << page;
        
        std::string url = conv.str();
        //open connection
        _http.open(url, ec);
        if (ec) {
            throw error(ec.message());
        }
        std::stringstream ss;
        ss << &_http;
        std::string html = ss.str();
        
        boost::regex pattern(_regex_catsong);
        boost::smatch matches;
        std::string::const_iterator s = html.begin();
        std::string::const_iterator e = html.end();
        
        while (boost::regex_search(s, e, matches, pattern)) {
            auto clms = new CategoryListMusicStruct;
            clms->songid    =  matches.str(1);
            clms->songname  =  matches.str(2);
            clms->recnum    =  matches.str(3);
            //add to container
            _musiclist->add(clms);
            //iterate next matching
            s = matches[3].second;
        }
        
        return _musiclist;
    }
    
}
