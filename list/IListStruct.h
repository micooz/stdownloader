//
// IListStruct.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef ILISTSTRUCT_H
#define ILISTSTRUCT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <memory>
#include <string>

namespace songtaste {
    typedef std::string string;

    class IListStruct {
    public:
        explicit IListStruct();
        virtual ~IListStruct();
    };
    
    typedef std::shared_ptr<IListStruct> ListStruct;
}

#endif // ILISTSTRUCT_H
