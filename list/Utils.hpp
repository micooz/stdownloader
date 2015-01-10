#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <avhttp.hpp>

namespace songtaste
{

    static inline std::string convertSpace(const std::string &source, bool reverse = false)
    {
        typedef std::string::const_iterator iterator;
        iterator begin = source.cbegin();
        iterator end   = source.cend();
        std::string result;
        result.reserve(source.size());
        for (auto i = begin; i != end; ++i) {
            if (reverse) {
                if ( i + 5 != end
                     && *i == '&'
                     && *(i + 1) == 'n'
                     && *(i + 2) == 'b'
                     && *(i + 3) == 's'
                     && *(i + 4) == 'p'
                     && *(i + 5) == ';') {
                    result.push_back(' ');
                    i += 5;
                    continue;
                }
            } else {
                if (*i == ' ') {
                    result.append("&nbsp;");
                    continue;
                }
            }
            result.push_back(*i);
        }
        return result;
    }

    static inline void setUserAgent(const std::string &ua, avhttp::http_stream *http)
    {
        if (!ua.empty()) {
            avhttp::request_opts opt;
            opt.insert(avhttp::http_options::user_agent, ua);
            http->request_options(opt);
        }
    }

}

#endif // UTILS_HPP
