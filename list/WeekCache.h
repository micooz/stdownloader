#ifndef WEEKCACHE_H
#define WEEKCACHE_H

#include "ICache.h"

namespace songtaste
{

    class WeekCache : public ICache
    {
    public:
        explicit WeekCache();

        ~WeekCache();

        bool exsit(void);

        void save(ListCollection *collection);

        void load(ListCollection *list);

        std::string file(void) const;
    private:
        std::string _dir;
    };

}

#endif // WEEKCACHE_H
