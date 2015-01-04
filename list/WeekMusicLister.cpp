#include <boost/regex.hpp>
#include "Configure.h"
#include "Utils.hpp"
#include "ListCollection.h"
#include "WeekMusicCache.h"
#include "WeekMusicLister.h"
#include "WeekMusicListStruct.h"

namespace songtaste
{

    WeekMusicLister::WeekMusicLister(bool cache)
        : _cache(cache), _weekcommendlist(nullptr), _http(_io)
    {
        Configure &config = *(Configure::getInstance());

        _url_weekrecommend   = config[constant::config::urls][constant::config::chart].asString();
        _regex_weekrecommend = config[constant::config::regexs][constant::config::chartmusic].asString();

        if (_url_weekrecommend.empty() || _regex_weekrecommend.empty()) {
            throw std::logic_error(constant::error::configure_error);
        }

        std::string user_agent = config[constant::config::useragent].asString();

        setUserAgent(user_agent, &_http);

        _weekcommendlist = new ListCollection;
    }

    WeekMusicLister::~WeekMusicLister()
    {
        if (_http.is_open()) {
            _http.close();
        }
        SAFERELEASE(_weekcommendlist);
    }

    ListCollection *WeekMusicLister::getListAt(const unsigned int)
    {
        //load from cache
        ICache *cache = new WeekMusicCache;
        if (_cache && cache->exsit()) {
            cache->load(_weekcommendlist);
            SAFERELEASE(cache);
            return _weekcommendlist;
        }
        //no cache
        boost::system::error_code ec;
        //open connection
        _http.open(_url_weekrecommend, ec);
        if (ec) {
            throw std::logic_error(ec.message());
        }
        std::stringstream ss;
        ss << &_http;
        std::string html = ss.str();

        boost::regex pattern(_regex_weekrecommend);
        boost::smatch matches;
        std::string::const_iterator s = html.begin();
        std::string::const_iterator e = html.end();

        while (boost::regex_search(s, e, matches, pattern)) {
            auto st = new WeekMusicListStruct;
            st->idx         = matches.str(1);
            st->songid      = matches.str(2);
            st->songname    = matches.str(3);
            st->singer      = matches.str(4);
            st->sex         = matches.str(5);
            st->uid         = matches.str(6);
            st->uname       = matches.str(7);
            st->width       = matches.str(8);
            st->lsnnum      = matches.str(9);
            //add to container
            _weekcommendlist->add(st);
            //iterate next matching
            s = matches[9].second;
        }

        //cache
        if (_cache) {
            cache->save(_weekcommendlist);
            SAFERELEASE(cache);
        }
        return _weekcommendlist;
    }

}



