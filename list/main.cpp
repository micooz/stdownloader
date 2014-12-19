//detect memory leak
#if defined (WIN32) || (_WIN32)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#undef free // avoid avhttp\bitfield.hpp error
#endif

#include <iostream>
#include "AlbumLister.h"
#include "RecommendLister.h"
#include "CategoryLister.h"
#include "CategoryListStruct.h"

using namespace std;
using namespace songtaste;

int main(int argc, char *argv[]) {
#if defined (WIN32) || (_WIN32)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    try {
        //Lister lister(new RecommendLister);
        //ListCollection data = lister->getListAt(2);

        //ListCollection::const_iterator it = data.cbegin();
        //for (; it != data.end(); ++it) {
        //    ListStruct ls = *it;

        //    cout << ls->songname << "\n" << ls->songid << "\n" << ls->uname << "\n"
        //        << ls->uid << "\n" << ls->uicon << "\n" << ls->recwidth << "\n"
        //        << ls->rateuid << "\n" << ls->ratedt << "\n" << ls->rateuname;
        //    cout << endl;
        //    cout << endl;
        //}
        Lister lister(new CategoryLister);
        ListCollection data = lister->getListAt();
        ListCollection::const_iterator it = data.cbegin();
        for (; it != data.cend(); ++it) {
            CategoryListStruct *ls = static_cast<CategoryListStruct*>(it->get());

            cout << ls->idx << "\n" << ls->catid << "\n" << ls->catname
                << "\n" << ls->width << "\n" << ls->catnum << endl << endl;
        }

    } catch (const logic_error &err) {
        cout << err.what() << endl;
    }

    return 0;
}
