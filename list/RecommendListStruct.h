//
// RecommendListStruct.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef RECOMMENDLISTSTRUCT_H
#define RECOMMENDLISTSTRUCT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "IListStruct.h"

namespace songtaste {

    class RecommendListStruct :
        public IListStruct {
    public:
        RecommendListStruct();
        ~RecommendListStruct();


    };

}

#endif // RECOMMENDLISTSTRUCT_H
