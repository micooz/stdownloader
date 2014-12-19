#include <boost/regex.hpp>
#include <sstream>
#include "RecommendLister.h"
#include "RecommendListStruct.h"

namespace songtaste {

    RecommendLister::RecommendLister() {
        _url_recommend = _config->all()["URLS"]["recommend"].asString();
        _regex_pattern = _config->all()["REGEXS"]["recommend"].asString();
        if (_url_recommend.empty() || _regex_pattern.empty()) {
            throw error("configure item is empty");
        }
    }

    ListCollection
        RecommendLister::getListAt(const unsigned int page /* = 1 */) {
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
            RecommendListStruct *rls = new RecommendListStruct;

            //matches.str(0) is the original string
            rls->songname = matches.str(1);
            rls->songid = matches.str(2);
            rls->uname = matches.str(3);
            rls->uid = matches.str(4);
            rls->uicon = matches.str(5);
            rls->recwidth = matches.str(6);
            rls->rateuid = matches.str(7);
            rls->ratedt = matches.str(8);
            rls->rateuname = matches.str(9);

            ListStruct item(rls);
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