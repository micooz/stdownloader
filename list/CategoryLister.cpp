#include <boost/regex.hpp>
#include "CategoryLister.h"

namespace songtaste {

    CategoryLister::CategoryLister() {
        _url_category = _config->all()["URLS"]["category"].asString();
        _url_catsong = _config->all()["URLS"]["catesong"].asString();
        _regex_category = _config->all()["REGEXS"]["categorylist"].asString();
        _regex_catsong = _config->all()["REGEXS"]["catsong"].asString();

        if (_url_category.empty() || _regex_category.empty() || _regex_catsong.empty() || _url_catsong.empty()) {
            throw error("configure item is empty");
        }
    }

    ListCollection
        CategoryLister::getListAt(const unsigned int catid, const unsigned int page /* = 1 */) {
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

        ListCollection _result;

        while (boost::regex_search(s, e, matches, pattern)) {
            CateoryListMusicStruct *clms = new CateoryListMusicStruct;
            //matches.str(0) is the original string
            clms->songid = matches.str(1);
            clms->songname = matches.str(2);
            clms->recnum = matches.str(3);

            ListStruct item(clms);

            _result.push_back(item);
            //iterate next matching
            s = matches[3].second;
        }

        return _result;
    }

    ListCollection
        CategoryLister::getCatList() {
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

        ListCollection _result;

        while (boost::regex_search(s, e, matches, pattern)) {
            CategoryListStruct *cls = new CategoryListStruct;
            //matches.str(0) is the original string
            cls->idx = matches.str(1);
            cls->catid = matches.str(2);
            cls->catname = matches.str(3);
            cls->width = matches.str(4);
            cls->catnum = matches.str(5);

            ListStruct item(cls);

            _result.push_back(item);
            //iterate next matching
            s = matches[5].second;
        }

        return _result;
    }

    CategoryLister::~CategoryLister() {
    }

}
