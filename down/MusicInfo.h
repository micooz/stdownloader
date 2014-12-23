#ifndef MUSICINFO_H
#define MUSICINFO_H

#include <memory>
#include <string>


namespace songtaste {
    
    typedef std::string string;
    
    class MusicInfo {
    public:
        explicit MusicInfo();
        ~MusicInfo();
        
        std::string toJson();
        
        string songid;
        string songname;
        string singer;
        string isbox;
        string idx;
        string songurl;
        string midurl;
    };
    
    typedef std::shared_ptr<MusicInfo> MInfo;
}

#endif // MUSICINFO_H
