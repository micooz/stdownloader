#ifndef WEEKMUSICCACHE_H
#define WEEKMUSICCACHE_H

#include "ICache.h"

namespace songtaste
{

    class WeekMusicCache : public ICache
    {
    public:
        explicit WeekMusicCache();

        ~WeekMusicCache();

        bool exsit(void);

        void save(ListCollection *collection);

        void load(ListCollection *list);

        std::string file(void) const;

    private:
        std::string _dir;
    };

}

#endif // WEEKMUSICCACHE_H
