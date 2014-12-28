//
// ILister.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef ILISTER_H
#define ILISTER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#define SAFERELEASE(p) if(p) {delete p; p = nullptr;}
#include <string>

namespace songtaste {
    class ListCollection;
    //class std::string;
    
    class ILister {
    public:
        explicit ILister();
        
        virtual ~ILister();
        
        virtual ListCollection* getListAt(const unsigned int page = 1) = 0;
    };
    
}

#endif // ILISTER_H
