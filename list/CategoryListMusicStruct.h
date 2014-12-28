//
// CategoryListMusicStruct.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//

#ifndef CATEGORYLISTMUSICSTRUCT_H
#define CATEGORYLISTMUSICSTRUCT_H

#include "IListStruct.h"

namespace songtaste {
    class CategoryListMusicStruct : public IListStruct {
    public:
        explicit CategoryListMusicStruct();
        
        ~CategoryListMusicStruct();
        
        const Json::Value toJson(void);
        
    public:
        std::string songid;
        std::string songname;
        std::string recnum;
    };  
}

#endif // CATEGORYLISTMUSICSTRUCT_H
