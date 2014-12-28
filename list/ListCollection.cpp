#include <json/json.h>
#include "IListStruct.h"
#include "ListCollection.h"

namespace songtaste{
    
    ListCollection::ListCollection() {
        
    }
    
    ListCollection::~ListCollection() {
        for(IListStruct *item : _data){
            SAFERELEASE(item);
        }
    }
    
    void ListCollection::add(IListStruct *item) {
        _data.push_back(item);
    }
    
    const std::string ListCollection::toJsonString() {
        Json::FastWriter writer;
        Json::Value root;
        
        for(IListStruct *item : _data){
            root.append(item->toJson());
        }
        
        return writer.write(root);
    }
    
}
