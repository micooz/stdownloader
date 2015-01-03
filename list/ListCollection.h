#ifndef LISTCOLLECTION_H
#define LISTCOLLECTION_H

#include <string>
#include <vector>

namespace songtaste
{
    class IListStruct;

    class ListCollection
    {
    public:
        explicit ListCollection();

        ~ListCollection();

        void add(IListStruct *item);

        const std::string toJsonString(bool compress = true);
        
        template<typename T>
        void parseJsonArray(const std::string& jsonstr);

    private:
        std::vector<IListStruct *> _data;
    };

}

#include "ListCollectionImpl.h"

#endif // LISTCOLLECTION_H
