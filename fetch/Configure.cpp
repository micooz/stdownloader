#include <fstream>
#include "Configure.h"

namespace songtaste {

    Configure::Configure() {
        std::string config_path = "config.json";
        std::ifstream fs(config_path);

        if (!fs.good()) {
            throw error("cannot open config.json");
        }

        Json::Reader reader;
        if (!reader.parse(fs, _config, false)) {
            throw error("loading configure file error");
        }
        fs.close();
    }

    Configure*
        Configure::getInstance() {
        static Configure* instance;
        return instance;
    }

    const Config&
        Configure::all() const {
        return _config;
    }

    Configure::~Configure() {
    }
}


