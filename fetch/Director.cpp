//
// director.cpp
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//

#include "Director.h"

namespace songtaste {

    Director::Director() {
    }

    Director*
        Director::getInstance() {
        static Director instance;
        return &instance;
    }

    Director::~Director() {
    }

}