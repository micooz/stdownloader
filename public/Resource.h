//
// Resource.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

namespace songtaste
{
    namespace constant
    {
        namespace config
        {
            const std::string file          =  "config.json";
            const std::string urls          =  "urls";
            const std::string recommend     =  "recommend";
            const std::string category      =  "category";
            const std::string catsong       =  "catsong";
            const std::string categorylist  =  "categorylist";
            const std::string down          =  "down";
            const std::string time          =  "time";
            
            
            const std::string regexs        =  "regexs";
            const std::string useragent     =  "useragent";
            const std::string cachepath     =  "cachepath";
        }
        
        namespace error
        {
            const std::string configure_error        =  "configure item is empty";
            const std::string page_error             =  "page error";
            const std::string load_config_error      =  "cannot load config.json";
            const std::string create_directory_error =  "cannot create directory";
            const std::string load_cache_error       =  "loading cache failed";
        }

    }
}

#endif // RESOURCE_H
