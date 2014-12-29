#include <boost/program_options.hpp>
#include <iostream>
#include "RecommendLister.h"
#include "CategoryLister.h"
#include "ListCollection.h"

using namespace boost::program_options;
using namespace songtaste;
using namespace std;

int main(int argc, char *argv[])
{
    options_description desc("Usage");
    desc.add_options()
    ("help,h",      "show help information")
    ("recommend",   "get recommend list")
    ("category",    "get category list")
    ("catsong",     "get song list from a category, require --catid")
    ("catid",       value<unsigned int>(), "category id")
    ("page",        value<unsigned int>(), "page number, default to 1");

    variables_map vm;
    try {
        store(parse_command_line(argc, argv, desc), vm);
    } catch (std::exception &ex) {
        cout << ex.what() << endl;
        return -1;
    }
    notify(vm);

    try {

        do {
            if (vm.count("help") || argc == 1) {
                cout << desc;
                break;
            }

            if (vm.count("recommend")) {
                unsigned int page = vm.count("page") ? vm["page"].as<unsigned int>() : 1;
                ILister *pLister  = new RecommendLister;
                cout << pLister->getListAt(page)->toJsonString();
                SAFERELEASE(pLister);
                break;
            }

            if (vm.count("category")) {
                ILister *lister = new CategoryLister;
                cout << lister->getListAt()->toJsonString();
                SAFERELEASE(lister);
                break;
            }

            if (vm.count("catsong") && vm.count("catid")) {
                unsigned int catid = vm["catid"].as<unsigned int>();
                unsigned int page  = vm.count("page") ? vm["page"].as<unsigned int>() : 1;
                CategoryLister *lister = new CategoryLister;
                cout << lister->getMusicByCatid(catid, page)->toJsonString();
                SAFERELEASE(lister);
                break;
            }

        } while (0);

    } catch (const exception &err) {
        cout << err.what() << endl;
    }

    return 0;
}
