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

#include <string>
#include <vector>
#include <memory>
#include <boost/asio/io_service.hpp>
#include "Configure.h"
#include "IListStruct.h"

namespace songtaste {

    typedef std::vector<ListStruct> ListCollection;

    class ILister {
    public:
        explicit ILister();
        virtual ~ILister();

        virtual ListCollection getList() = 0;

    protected:
        Configure *_config;
        boost::asio::io_service _io;
    private:
        
    };

    typedef std::shared_ptr<ILister> Lister;

}

#endif // ILISTER_H
