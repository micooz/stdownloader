#ifndef WEEKMUSICLISTSTRUCT_H
#define WEEKMUSICLISTSTRUCT_H

#include "IListStruct.h"

namespace songtaste {
    
    class WeekMusicListStruct : public IListStruct
    {
    public:
        WeekMusicListStruct();
        
        ~WeekMusicListStruct();
        
        const Json::Value toJson(void);

        void parseJson(const std::string &jsonstr);
        
        void parseJson(const Json::Value &jsonval);
        
    public:
        std::string idx;
        std::string songid;
        std::string songname;
        std::string singer;
        std::string sex;
        std::string uid;
        std::string uname;
        std::string width;
        std::string lsnnum;
    };
    
}

#endif // WEEKMUSICLISTSTRUCT_H
