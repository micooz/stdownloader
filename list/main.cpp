#include <iostream>
#include "ILister.h"
#include "AlbumLister.h"
#include "AlbumListStruct.h"

using namespace std;
using namespace songtaste;

int main(int argc, char *argv[]) {

    try {
        ILister *lister = new AlbumLister;
        IListStruct *data = lister->getList();

        delete lister;
        lister = nullptr;

    } catch (const logic_error &err) {
        cout << err.what() << endl;
    }

    return 0;
}
