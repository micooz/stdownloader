#include <boost/program_options.hpp>
#include <iostream>
#include "RecommendLister.h"
#include "CategoryLister.h"
#include "CategoryMusicLister.h"
#include "WeekLister.h"
#include "WeekMusicLister.h"
#include "ListCollection.h"

using namespace boost::program_options;
using namespace songtaste;
using namespace std;

int main(int argc, char *argv[])
{
    options_description desc("Usage");
    desc.add_options()
    ("help,h",      "show help information"                             )
    ("recommend",   "get recommend list"                                )
    ("category",    "get category list"                                 )
    ("week",        "get week list"                                     )
    ("weekchart",   "get week music chart"                              )
    ("catsong",     "get song list from a category, require --catid"    )
    ("cache",       "cache list or load from cache if exist"            )
    ("catid",       value<unsigned int>(), "category id"                )
    ("page",        value<unsigned int>(), "page number, default to 1"  );

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
                ILister *pLister  = new RecommendLister(vm.count("cache"));
                cout << pLister->getListAt(page)->toJsonString();
                SAFERELEASE(pLister);
                break;
            }

            if (vm.count("category")) {
                ILister *lister = new CategoryLister(vm.count("cache"));
                cout << lister->getListAt()->toJsonString();
                SAFERELEASE(lister);
                break;
            }

            if (vm.count("catsong") && vm.count("catid")) {
                unsigned int catid = vm["catid"].as<unsigned int>();
                unsigned int page  = vm.count("page") ? vm["page"].as<unsigned int>() : 1;
                bool cache         = vm.count("cache");
                ILister *lister = new CategoryMusicLister(catid, cache);
                cout << lister->getListAt(page)->toJsonString();
                SAFERELEASE(lister);
                break;
            }

            if (vm.count("week")) {
                ILister *lister = new WeekLister(vm.count("cache"));
                cout << lister->getListAt()->toJsonString();
                SAFERELEASE(lister);
                break;
            }

            if (vm.count("weekchart")) {
                ILister *lister = new WeekMusicLister(vm.count("cache"));
                cout << lister->getListAt()->toJsonString();
                SAFERELEASE(lister);
                break;
            }

        } while (0);

    } catch (const exception &err) {
        cout << err.what();
    }

    return 0;
}
