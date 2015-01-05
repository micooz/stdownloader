#include <boost/regex.hpp>
#include "Configure.h"
#include "CategoryMusicCache.h"
#include "CategoryMusicLister.h"
#include "CategoryListMusicStruct.h"
#include "Resource.h"
#include "Utils.hpp"
#include "ListCollection.h"

namespace songtaste
{

    CategoryMusicLister::CategoryMusicLister(unsigned int catid, bool cache)
        : _catid(catid), _cache(cache), _musiclist(nullptr), _http(_io)
    {
        Configure &config = *(Configure::getInstance());

        _url_catsong    = config[constant::config::urls][constant::config::catsong].asString();
        _regex_catsong  = config[constant::config::regexs][constant::config::catsong].asString();

        if (_url_catsong.empty() || _regex_catsong.empty()) {
            throw std::logic_error(constant::error::configure_error);
        }

        std::string user_agent = config[constant::config::useragent].asString();

        setUserAgent(user_agent, &_http);

        _musiclist = new ListCollection;
    }

    CategoryMusicLister::~CategoryMusicLister()
    {
        SAFERELEASE(_musiclist);
    }

    ListCollection *
    CategoryMusicLister::getListAt(const unsigned int page)
    {
        //load from cache
        ICache *cache = new CategoryMusicCache(_catid, page);
        if (_cache && cache->exsit()) {
            cache->load(_musiclist);
            SAFERELEASE(cache);
            return _musiclist;
        }
        //no cache
        boost::system::error_code ec;
        std::stringstream conv;
        conv << _url_catsong << "/cat" << _catid << "/" << page;
        std::string url = conv.str();
        //open connection
        _http.open(url, ec);
        if (ec) {
            throw std::logic_error(ec.message());
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
        //cache
        if (_cache) {
            cache->save(_musiclist);
            SAFERELEASE(cache);
        }
        return _musiclist;
    }

}
