#include <boost/regex.hpp>
#include "CategoryLister.h"
#include "CategoryListStruct.h"

namespace songtaste {

    CategoryLister::CategoryLister() {
        _url_category = _config->all()["URLS"]["category"].asString();
        _regex_pattern = _config->all()["REGEXS"]["categorylist"].asString();
        if (_url_category.empty() || _regex_pattern.empty()) {
            throw error("configure item is empty");
        }
    }

    ListCollection
        CategoryLister::getListAt(const unsigned int page) {
        boost::system::error_code ec;
        //open connection
        _http.open(_url_category, ec);
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
