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

        const std::string toJsonString(void);

    private:
        std::vector<IListStruct *> _data;
    };

}

#endif // LISTCOLLECTION_H
