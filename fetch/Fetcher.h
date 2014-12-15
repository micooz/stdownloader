//
// Fetcher.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef FETCHER_H
#define FETCHER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "common.h"
#include "Configure.h"

namespace songtaste {

    class Fetcher {
    public:
        Fetcher();

        void fetch();

        ~Fetcher();
    private:
        std::string url_time;
    };

}

#endif // Fetcher.h
