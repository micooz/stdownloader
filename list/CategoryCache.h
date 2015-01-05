#ifndef CATEGORYCACHE_H
#define CATEGORYCACHE_H

#include "ICache.h"

namespace songtaste
{

    class CategoryCache : public ICache
    {
    public:
        explicit CategoryCache();

        ~CategoryCache();

        void load(ListCollection *list);

        std::string file(void) const;

    private:
        std::string _dir;
    };

}

#endif // CATEGORYCACHE_H
