#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

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

}

#endif // UTILS_HPP
