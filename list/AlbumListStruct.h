//
// AlbumListeStruct.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef ALBUMLISTSTRUCT_H
#define ALBUMLISTSTRUCT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "IListStruct.h"

namespace songtaste {

    class AlbumListStruct : public IListStruct {
    public:
        explicit AlbumListStruct();
        ~AlbumListStruct();
    };

}
#endif // ALBUMLISTSTRUCT_H
