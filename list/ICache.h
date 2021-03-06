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
        virtual ~ICache();

        virtual bool exsit(void);

        virtual void save(ListCollection *collection);

        virtual void load(ListCollection *list) = 0;

        virtual std::string file(void) const = 0;
    };

}

#endif // ICACHE_H
