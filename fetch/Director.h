//
// director.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef DIRECTOR_H
#define DIRECTOR_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "common.h"

namespace songtaste {

    class Director {
    public:
        static Director* getInstance();

        ~Director();
    private:
        Director();
    };

}

#endif // director.h
