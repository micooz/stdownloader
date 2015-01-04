#include <boost/regex.hpp>
#include <sstream>
#include "Configure.h"
#include "Utils.hpp"
#include "ListCollection.h"
#include "RecommendLister.h"
#include "RecommendListStruct.h"
#include "RecommendCache.h"
#include "Resource.h"

namespace songtaste
{

    RecommendLister::RecommendLister(bool cache):
        _list(nullptr), _http(_io), _cache(cache)
    {
        Configure &config = *(Configure::getInstance());

        _url_recommend = config[constant::config::urls][constant::config::recommend].asString();
        _regex_pattern = config[constant::config::regexs][constant::config::recommend].asString();

        std::string user_agent = config[constant::config::useragent].asString();

        setUserAgent(user_agent, &_http);

        if (_url_recommend.empty() || _regex_pattern.empty()) {
            throw std::logic_error(constant::error::configure_error);
        }

        _list = new ListCollection;
    }

    ListCollection *
    RecommendLister::getListAt(const unsigned int page /* = 1 */)
    {
        //load from cache
        ICache *cache = new RecommendCache(page);
        if (_cache && cache->exsit()) {
            cache->load(_list);
            SAFERELEASE(cache);
            return _list;
        }
        //no cache
        if (page < 1 || page > 10) {
            throw std::logic_error(constant::error::page_error);
        }
        boost::system::error_code ec;
        //support for paging
        std::stringstream conv;
        conv << _url_recommend << "/" << page;
        //open connection
        _http.open(conv.str(), ec);
        if (ec) {
            throw std::logic_error(ec.message());
        }
        std::stringstream ss;
        ss << &_http;
        std::string html = ss.str();

        boost::regex pattern(_regex_pattern);
        boost::smatch matches;
        std::string::const_iterator s = html.begin();
        std::string::const_iterator e = html.end();

        while (boost::regex_search(s, e, matches, pattern)) {
            RecommendListStruct *rls = new RecommendListStruct;
            rls->songname   = matches.str(1);
            rls->songid     = matches.str(2);
            rls->uname      = matches.str(3);
            rls->uid        = matches.str(4);
            rls->uicon      = matches.str(5);
            rls->recwidth   = matches.str(6);
            rls->rateuid    = matches.str(7);
            rls->ratedt     = matches.str(8);
            rls->rateuname  = matches.str(9);
            //add to container
            _list->add(rls);
            //iterate next matching
            s = matches[9].second;
        }

        //cache
        if (_cache) {
            cache->save(_list);
            SAFERELEASE(cache);
        }
        return _list;
    }

    RecommendLister::~RecommendLister()
    {
        if (_http.is_open()) {
            _http.close();
        }
        SAFERELEASE(_list);
    }

}
