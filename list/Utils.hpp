#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <avhttp.hpp>

namespace songtaste
{

    static std::string clearspace(const std::string &str)
    {
        typedef std::string::const_iterator iterator;
        iterator begin = str.cbegin();
        iterator end   = str.cend();
        std::string result;
        result.reserve(str.size());
        for (auto i = begin; i != end; ++i) {
            if (*i == ' ')
                continue;
            result.push_back(*i);
        }
        return result;
    }

    static void setUserAgent(const std::string &ua, avhttp::http_stream *http)
    {
        if (!ua.empty()) {
            avhttp::request_opts opt;
            opt.insert(avhttp::http_options::user_agent, ua);
            http->request_options(opt);
        }
    }

}

#endif // UTILS_HPP
