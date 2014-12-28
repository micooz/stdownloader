#include "AlbumLister.h"
#include "AlbumListStruct.h"

namespace songtaste {
    
    AlbumLister::AlbumLister() {
    }
    
    std::vector<IListStruct*>*
    AlbumLister::getListAt(const unsigned int page) {
        
        return new std::vector<IListStruct*>();
    }
    
    AlbumLister::~AlbumLister() {
    }
    
}
