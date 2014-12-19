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

namespace songtaste {
    using namespace Json;

    typedef Json::Value Config;
    typedef std::logic_error error;

    class Configure : public boost::noncopyable {
    public:
        static Configure* getInstance();

        const Config& all() const;

        ~Configure();
    private:
        explicit Configure();
        Config _config;
    };

}

#endif // Configure.h
