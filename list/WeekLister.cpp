#include <boost/regex.hpp>
#include "Configure.h"
#include "Utils.hpp"
#include "ListCollection.h"
#include "WeekLister.h"
#include "WeekListStruct.h"
#include "WeekCache.h"


namespace songtaste
{

    WeekLister::WeekLister(bool cache)
        : _cache(cache), _weeklist(nullptr), _http(_io)
    {
        Configure &config = *(Configure::getInstance());

        _url_weeklist   = config[constant::config::urls][constant::config::chart].asString();
        _regex_weeklist = config[constant::config::regexs][constant::config::chart].asString();

        if (_url_weeklist.empty() || _regex_weeklist.empty()) {
            throw std::logic_error(constant::error::configure_error);
        }

        std::string user_agent = config[constant::config::useragent].asString();

        setUserAgent(user_agent, &_http);

        _weeklist = new ListCollection;
    }

    WeekLister::~WeekLister()
    {
        if (_http.is_open()) {
            _http.close();
        }
        SAFERELEASE(_weeklist);
    }

    ListCollection *WeekLister::getListAt(const unsigned int)
    {
        //load from cache
        ICache *cache = new WeekCache;
        if(_cache && cache->exsit()){
            cache->load(_weeklist);
            SAFERELEASE(cache);
            return _weeklist;
        }
        //no cache
        boost::system::error_code ec;
        //open connection
        _http.open(_url_weeklist, ec);
        if (ec) {
            throw std::logic_error(ec.message());
        }
        std::stringstream ss;
        ss << &_http;
        std::string html = ss.str();

        boost::regex pattern(_regex_weeklist);
        boost::smatch matches;
        std::string::const_iterator s = html.begin();
        std::string::const_iterator e = html.end();

        while (boost::regex_search(s, e, matches, pattern)) {
            WeekListStruct *st = new WeekListStruct;
            st->weekfrom = matches.str(1);
            st->weektime = matches.str(2); 
            //add to container
            _weeklist->add(st);
            //iterate next matching
            s = matches[2].second;
        }

        //cache
        if (_cache) {
            cache->save(_weeklist);
            SAFERELEASE(cache);
        }
        return _weeklist;
    }

}



