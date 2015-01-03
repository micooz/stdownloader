#include <fstream>
#include "Configure.h"
#include "Resource.h"

namespace songtaste
{

    Configure::Configure()
    {
        do {
            std::ifstream fs(constant::config::file);
            if (!fs.good()) break;

            Json::Reader reader;

            if (!reader.parse(fs, _config, false)) break;

            fs.close();

            return;
        } while (0);

        throw std::logic_error(constant::error::load_config_error);
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
