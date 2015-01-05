#ifndef CATEGORYMUSICCACHE_H
#define CATEGORYMUSICCACHE_H

#include "ICache.h"

namespace songtaste
{

    class CategoryMusicCache : public ICache
    {
    public:
        explicit CategoryMusicCache(unsigned int catid, unsigned int page = 1);

        ~CategoryMusicCache();

        void load(ListCollection *list);

        std::string file(void) const;

    private:
        std::string  _dir;
        unsigned int _page;
        unsigned int _catid;
    };

}

#endif // CATEGORYMUSICCACHE_H
