//
// Lister.cpp
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#include "ILister.h"

namespace songtaste {

    ILister::ILister()
        :_http(_io) {
        _config = Configure::getInstance();
    }

    ListCollection
        ILister::getListAt(const unsigned int page /* = 1 */) {
        return ListCollection();
    }

    ILister::~ILister() {
    }

}
