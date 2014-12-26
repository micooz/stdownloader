#include <boost/program_options.hpp>
#include <iostream>
#include "Downloader.h"

using namespace std;
using namespace boost::program_options;
using namespace songtaste;

int main(int argc,char *argv[]) {
    
    options_description desc("Usage");
    
    desc.add_options()
            ("help,h","show help information")
            ("id",value<unsigned int>(),"song id")
            ("dir",value<std::string>()->default_value("./"),"store directory")
            ("name",value<std::string>(),"file name, default to original name (maybe illegal)")
            ("info","get music information instead of downloading");
    
    variables_map vm;
    try {
        store(parse_command_line(argc, argv, desc), vm);
    } catch(const std::exception &err) {
        cout << err.what() << endl;
        return -1;
    }
    notify(vm);
    
    try {
        do {
            if(vm.count("help") || argc == 1){
                cout<< desc;
                break;
            }
            
            if(!vm.count("id")){
                throw std::logic_error("--id must be set");
            }
            
            unsigned int songid = vm["id"].as<unsigned int>();
            
            if(vm.count("info")){
                shared_ptr<Downloader> downloader(new Downloader);
                MInfo info = downloader->getMusicInfo(songid);
                std::cout << info->toJson();
                break;
            } else {
                shared_ptr<Downloader> downloader(new Downloader);
                std::string dir  = vm["dir"].as<std::string>();
                std::string name = vm.count("name")?vm["name"].as<std::string>():"";
                
                if(*(dir.end() - 1) != '/') {
                    dir.push_back('/');
                }
                
                downloader->download(songid, dir, name);
                break;
            }
            
        } while(0);
        
    } catch(const std::exception &err) {
        cout << err.what();
    }
    
    return 0;
}
