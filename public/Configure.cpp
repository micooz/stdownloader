#include <fstream>
#include "Configure.h"
#include "Resource.h"

namespace songtaste
{

    Configure::Configure()
    {
        std::ifstream fs(CONFIG_FILE);

        if (!fs.good()) {
            throw std::logic_error("cannot open config.json");
        }

        Json::Reader reader;
        if (!reader.parse(fs, _config, false)) {
            throw std::logic_error("loading configure file error");
        }
        fs.close();
    }

    Configure *
    Configure::getInstance()
    {
        static Configure instance;
        return &instance;
    }

    Json::Value &Configure::operator[](const std::string &key)
    {
        return _config[key];
    }

    Configure::~Configure()
    {
    }

}
