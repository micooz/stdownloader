#ifndef ICACHE_H
#define ICACHE_H

#include <string>

namespace songtaste
{
    class ListCollection;

    class ICache
    {
    public:
        explicit ICache();
        ~ICache();

        virtual bool exsit(void) = 0;

        virtual void save(ListCollection *collection) = 0;

        virtual void load(ListCollection *list) = 0;

        virtual std::string file(void) const = 0;
    };

}

#endif // ICACHE_H
