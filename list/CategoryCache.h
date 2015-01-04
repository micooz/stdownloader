#ifndef CATEGORYCACHE_H
#define CATEGORYCACHE_H

#include <string>
#include "ICache.h"

namespace songtaste
{

    class CategoryCache : public ICache
    {
    public:
        CategoryCache();
        ~CategoryCache();
        
        bool exsit(void);
        
        void save(ListCollection *collection);
        
        void load(ListCollection *list);
        
        std::string file(void) const;
        
    private:
        std::string _dir;
        
    };

}

#endif // CATEGORYCACHE_H
