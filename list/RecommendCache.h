#ifndef RECOMMENDCACHE_H
#define RECOMMENDCACHE_H

#include "ICache.h"

namespace songtaste
{

    class RecommendCache : public ICache
    {
    public:
        explicit RecommendCache(unsigned int page = 1);
        
        ~RecommendCache();
        
        void load(ListCollection *list);
        
        std::string file(void) const;
        
    private:
        unsigned int _page;
        std::string  _dir;
    };

}



#endif // RECOMMENDCACHE_H
