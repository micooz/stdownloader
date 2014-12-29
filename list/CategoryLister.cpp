#include <boost/regex.hpp>
#include "Configure.h"
#include "ListCollection.h"
#include "IListStruct.h"
#include "CategoryLister.h"
#include "CategoryListStruct.h"
#include "CategoryListMusicStruct.h"
#include "Resource.h"

namespace songtaste
{

    CategoryLister::CategoryLister():
        _catlist(nullptr), _musiclist(nullptr), _http(_io)
    {
        Configure &config = *(Configure::getInstance());

        _url_category   = config[constant::config::urls][constant::config::category].asString();
        _url_catsong    = config[constant::config::urls][constant::config::catsong].asString();
        _regex_category = config[constant::config::regexs][constant::config::categorylist].asString();
        _regex_catsong  = config[constant::config::regexs][constant::config::catsong].asString();

        if (_url_category.empty() || _regex_category.empty() || _regex_catsong.empty() || _url_catsong.empty()) {
            throw std::logic_error(constant::error::configure_error);
        }

        std::string user_agent = config[constant::config::useragent].asString();

        if (!user_agent.empty()) {
            _http.request_options()(avhttp::http_options::user_agent, user_agent);
        }

        _catlist   = new ListCollection;
        _musiclist = new ListCollection;
    }

    CategoryLister::~CategoryLister()
    {
        SAFERELEASE(_catlist);
        SAFERELEASE(_musiclist);
    }

    ListCollection *
    CategoryLister::getListAt(const unsigned int)
    {
        boost::system::error_code ec;
        //open connection
        _http.open(_url_category, ec);
        if (ec) {
            throw std::logic_error(ec.message());
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
    CategoryLister::getMusicByCatid(const unsigned int catid, unsigned int page)
    {
        boost::system::error_code ec;

        std::stringstream conv;
        conv << _url_catsong << "/cat" << catid << "/" << page;

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

        return _musiclist;
    }

}
