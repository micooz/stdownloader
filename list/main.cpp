//detect memory leak
#if defined (WIN32) || (_WIN32)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#undef free // avoid avhttp\bitfield.hpp error
#endif

#include <boost/program_options.hpp>
#include <iostream>
#include "RecommendLister.h"
#include "RecommendListStruct.h"
#include "CategoryLister.h"
#include "CategoryListStruct.h"
#include "CategoryListMusicStruct.h"

using namespace std;
using namespace boost::program_options;
using namespace songtaste;

int main(int argc, char *argv[]) {
#if defined (WIN32) || (_WIN32)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    
    options_description desc("Usage");
    desc.add_options()
            ("help,h","show help information")
            ("recommend","get recommend list")
            ("category","get category list")
            ("catsong","get song list from a category,require --catid")
            ("catid",value<unsigned int>(),"category id")
            ("page",value<unsigned int>(),"page number");
    
    variables_map vm;
    try{
        store(parse_command_line(argc,argv,desc),vm);
    }catch(std::exception &ex){
        cout << ex.what() << endl;
        return -1;
    }
    notify(vm);
    
    try {
        
        do{
            if(vm.count("help") || vm.size() == 0){
                cout<< desc <<endl;
                break;
            }
            
            if(vm.count("recommend")){
                unsigned int page = vm.count("page")?vm["page"].as<unsigned int>():0;
                
                shared_ptr<RecommendLister> lister(new RecommendLister);
                
                Json::Value root;
                ListCollection data = lister->getListAt(page);
                ListCollection::const_iterator it = data.cbegin();
                for (; it != data.cend(); ++it) {
                    RecommendListStruct *ls = static_cast<RecommendListStruct*>(it->get());
                    
                    Json::Value item;
                    item["songname"]    = ls->songname;
                    item["songid"]      = ls->songid;
                    item["uname"]       = ls->uname;
                    item["uid"]         = ls->uid;
                    item["uicon"]       = ls->uicon;
                    item["recwidth"]    = ls->recwidth;
                    item["rateuid"]     = ls->rateuid;
                    item["ratedt"]      = ls->ratedt;
                    item["rateuname"]   = ls->rateuname;
                    
                    root.append(item);
                }
                Json::FastWriter writer;
                cout<< writer.write(root);
                
                break;
            }
            
            if(vm.count("category")){
                shared_ptr<CategoryLister> lister(new CategoryLister);
                ListCollection data = lister->getCatList();
                
                Json::Value root;
                ListCollection::const_iterator it = data.cbegin();
                for (; it != data.cend(); ++it) {
                    CategoryListStruct *ls = static_cast<CategoryListStruct*>(it->get());
                    
                    Json::Value item;
                    item["catid"]       = ls->catid;
                    item["catname"]     = ls->catname;
                    item["catnum"]      = ls->catnum;
                    item["idx"]         = ls->idx;
                    item["width"]       = ls->width;
                    
                    root.append(item);
                }
                Json::FastWriter writer;
                cout<< writer.write(root);
                
                break;
            }            
            
            if(vm.count("catsong") && vm.count("catid")){
                unsigned int catid = vm["catid"].as<unsigned int>();
                unsigned int page = vm.count("page")?vm["page"].as<unsigned int>():0;
                
                shared_ptr<CategoryLister> lister(new CategoryLister);
                ListCollection data = lister->getListAt(catid,page);
                
                Json::Value root;
                ListCollection::const_iterator it = data.cbegin();
                for (; it != data.cend(); ++it) {
                    CategoryListMusicStruct *ls = static_cast<CategoryListMusicStruct*>(it->get());
                    
                    Json::Value item;
                    item["songid"]       = ls->songid;
                    item["songname"]     = ls->songname;
                    item["recnum"]       = ls->recnum;
                    
                    root.append(item);
                }
                Json::FastWriter writer;
                cout<< writer.write(root);
                
                break;
            }
            
        }while(0);
        
    } catch (const logic_error &err) {
        cout << err.what() << endl;
    }
    
    return 0;
}
