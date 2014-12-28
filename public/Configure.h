//
// Configure.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef CONFIGURE_H
#define CONFIGURE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <json/json.h>
#include <boost/noncopyable.hpp>

namespace songtaste
{

    class Configure : public boost::noncopyable
    {
    public:
        static Configure *getInstance();

        Json::Value &operator[](const std::string &key);

        ~Configure();
    private:
        explicit Configure();

        const std::string CONFIG_FILE = "config.json";
        Json::Value _config;
    };
    
}

#endif // Configure.h
