#include <iostream>
#include "Downloader.h"
using namespace std;
using namespace songtaste;

int main(int argc,char *argv[]) {
    
    try{
        
        shared_ptr<Downloader> downloader(new Downloader);
        
        MInfo info = downloader->getMusicInfo(3465694);
        
        cout << info->idx << " " << info->isbox << " " << info->midurl << " " << info->singer << " "
             << info->songid << " " << info->songname << " " << info->songurl << endl << endl;
        
    }catch(const error &err){
        cout << err.what() << endl;
    }
    
    return 0;
}
