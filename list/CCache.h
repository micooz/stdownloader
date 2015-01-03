#ifndef CCACHE_H
#define CCACHE_H

#include <string>

namespace songtaste
{
    class ListCollection;

    class CCache
    {
    public:
        explicit CCache();
        ~CCache();

        enum Type {
            RECOMMEND = 0,
            CATEGORY
        };

        bool exsit(const Type &type);

        void save(ListCollection *collection, const Type &type);

        void load(const Type &type, ListCollection *pList);
        
    protected:
        
        std::string getPath(const Type &type);
        
    private:
        std::string _dir;
    };

}

#endif // CCACHE_H
