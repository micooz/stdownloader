//
// Lister.cpp
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//
#include "ILister.h"

namespace songtaste {

    ILister::ILister() {
        _config = Configure::getInstance();

        /*_url_category = con["URLS"]["category"].asString();
        _url_charts = con["URLS"]["charts"].asString();
        _url_recommend = con["URLS"]["recommend"].asString();*/
    }

    ILister::~ILister() {
    }

}
