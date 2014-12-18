#include <streambuf>
#include <boost/regex.hpp>
#include "AlbumLister.h"

namespace songtaste {

    AlbumLister::AlbumLister()
        :_http(_io) {
        _url_recommend = _config->all()["URLS"]["recommend"].asString();
        _regex_pattern = _config->all()["REGEXS"]["recommend"].asString();
        if (_url_recommend.empty() || _regex_pattern.empty()) {
            throw error("configure item is empty!");
        }
    }

    IListStruct*
        AlbumLister::getList() {
        boost::system::error_code ec;
        _http.open(_url_recommend, ec);
        if (ec) {
            throw error(ec.message());
        }
        std::stringstream ss;
        ss << &_http;

        //std::ofstream out("html.out");
        //out << ss.str();
        //out.close();
        std::string html = ss.str();

        boost::regex pattern(_regex_pattern);
        boost::smatch matches;
        std::string::const_iterator s = html.begin();
        std::string::const_iterator e = html.end();

        std::vector<std::string> _result;

        while (boost::regex_search(s, e, matches, pattern)) {
            for (size_t i = 0; i < matches.size(); ++i) {
                if (matches[i].matched) {
                    _result.push_back(matches.str(i));
                    _result.push_back("\n");
                }
            }
            s = matches[0].second;
        }

        BOOST_ASSERT(matches.size() > 0);
        return nullptr;
    }

    AlbumLister::~AlbumLister() {
        if (_http.is_open()) {
            _http.close();
        }
    }

}