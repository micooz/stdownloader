#include <iostream>
#include "Downloader.h"
using namespace std;
using namespace songtaste;

int main(int argc,char *argv[]) {
    
    try{
        boost::asio::io_service io;
        shared_ptr<Downloader> downloader(new Downloader(io));
        
        MInfo info = downloader->getMusicInfo(122572);
        
        //        cout << info->idx << " " << info->isbox << " " << info->midurl << " " << info->singer << " "
        //             << info->songid << " " << info->songname << " " << info->songurl << endl << endl;
        
        downloader->download(122572, info->songname);
        
        io.run();
        
    }catch(const error &err){
        cout << err.what() << endl;
    }
    
    return 0;
}
