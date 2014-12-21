//
// CategoryListStruct.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef CATEGORYLISTSTRUCT_H
#define CATEGORYLISTSTRUCT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "IListStruct.h"

namespace songtaste {
    
    class CategoryListStruct : public IListStruct {
    public:
        explicit CategoryListStruct();
        ~CategoryListStruct();
        
        string idx;
        string catid;
        string catname;
        string width;
        string catnum;
    private:
        
    };
    
}

#endif // CATEGORYLISTSTRUCT_H
