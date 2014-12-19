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

    ILister::~ILister() {
    }

}
