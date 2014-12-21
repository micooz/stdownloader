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

#include <boost/asio/io_service.hpp>
#include <avhttp.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Configure.h"
#include "IListStruct.h"

namespace songtaste {
    
    typedef std::vector<ListStruct> ListCollection;
    
    class ILister {
    public:
        explicit ILister();
        virtual ~ILister();
        
        /**
         * @brief get music list at the specified page
         * @param page(1-10)
         * @return ListCollection
         */
        virtual ListCollection getListAt(const unsigned int page = 1);
        
    protected:
        Configure *_config;
        boost::asio::io_service _io;
        avhttp::http_stream _http;
    };
    
    typedef std::shared_ptr<ILister> Lister;
    
}

#endif // ILISTER_H
