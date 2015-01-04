#ifndef WEEKLISTER_H
#define WEEKLISTER_H

#include <boost/asio.hpp>
#include <avhttp.hpp>
#include "ILister.h"

namespace songtaste
{
    
    /**
     * @brief get the list of some week time table
     */
    class WeekLister : public ILister
    {
    public:
        explicit WeekLister(bool cache = false);

        ~WeekLister();

        ListCollection *getListAt(const unsigned int page = 1);
    private:
        bool _cache;
        
        std::string _url_weeklist;
        std::string _regex_weeklist;
        
        boost::asio::io_service _io;
        avhttp::http_stream _http;
        
        ListCollection *_weeklist;
    };

}



#endif // WEEKLISTER_H
