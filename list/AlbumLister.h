//
// AlbumLister.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef ALBUMLISTER_H
#define ALBUMLISTER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "ILister.h"

namespace songtaste {

    class AlbumLister : public ILister {
    public:
        explicit AlbumLister();
        ~AlbumLister();

        //implments virtual functions
        ListCollection getListAt(const unsigned int page);

        //addon functions

    private:

    };
}

#endif // ALBUMLISTER_H
