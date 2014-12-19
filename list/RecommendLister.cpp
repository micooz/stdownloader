#include <boost/regex.hpp>
#include <sstream>
#include "RecommendLister.h"

namespace songtaste {

    RecommendLister::RecommendLister()
        :_http(_io) {
        _url_recommend = _config->all()["URLS"]["recommend"].asString();
        _regex_pattern = _config->all()["REGEXS"]["recommend"].asString();
        if (_url_recommend.empty() || _regex_pattern.empty()) {
            throw error("configure item is empty!");
        }
    }

    ListCollection
        RecommendLister::getListAt(const unsigned int page /* = 1 */ ) {
        if (page < 1 || page > 10) {
            throw error("page error");
        }
        boost::system::error_code ec;
        //support for paging
        std::stringstream conv;
        conv << _url_recommend << page;
        //open connection
        _http.open(conv.str(), ec);
        if (ec) {
            throw error(ec.message());
        }
        std::stringstream ss;
        ss << &_http;
        std::string html = ss.str();

        boost::regex pattern(_regex_pattern);
        boost::smatch matches;
        std::string::const_iterator s = html.begin();
        std::string::const_iterator e = html.end();

        ListCollection _result;

        while (boost::regex_search(s, e, matches, pattern)) {
            BOOST_ASSERT(matches.size() == 10);

            ListStruct item(new RecommendListStruct);
            //matches.str(0) is the original string
            item->songname = matches.str(1);
            item->songid = matches.str(2);
            item->uname = matches.str(3);
            item->uid = matches.str(4);
            item->uicon = matches.str(5);
            item->recwidth = matches.str(6);
            item->rateuid = matches.str(7);
            item->ratedt = matches.str(8);
            item->rateuname = matches.str(9);

            _result.push_back(item);

            //iterate next matching
            s = matches[9].second;
        }

        return _result;
    }

    RecommendLister::~RecommendLister() {
        if (_http.is_open()) {
            _http.close();
        }
    }

}