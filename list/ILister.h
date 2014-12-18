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
#include <boost/asio/io_service.hpp>
#include "Configure.h"
#include "IListStruct.h"

namespace songtaste {

    class ILister {
    public:
        explicit ILister();
        virtual ~ILister();

        virtual IListStruct* getList() = 0;

    protected:
        Configure *_config;
        boost::asio::io_service _io;
    private:
        //std::string _url_category;
        //std::string _url_charts;
        //std::string _url_recommend;
    };

}

#endif // ILISTER_H
