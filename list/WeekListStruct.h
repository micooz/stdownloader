#ifndef WEEKLISTSTRUCT_H
#define WEEKLISTSTRUCT_H

#include "IListStruct.h"

namespace songtaste
{

    class WeekListStruct : public IListStruct
    {
    public:
        explicit WeekListStruct();

        ~WeekListStruct();

        const Json::Value toJson(void);

        void parseJson(const std::string &jsonstr);
        
        void parseJson(const Json::Value &jsonval);
        
    public:
        std::string weekfrom;
        std::string weektime;
    };

}

#endif // WEEKLISTSTRUCT_H
