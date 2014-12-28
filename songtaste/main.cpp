#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> sub_routines = {
    "list", "down", "parse"
};

int main(int argc, char *argv[])
{
    try {
        if (argc < 2) {
            cout << "invalid sub routines.";
            exit(0);
        }

        bool found = false;
        for (auto sub : sub_routines) {
            if (sub == argv[1]) {
                string str_argv;
                str_argv.reserve(100);

                for (int i = 2; i < argc; i++) {
                    str_argv.append(argv[i]);
                    str_argv.append(" ");
                }

                string command(sub);
                command.append(" ").append(str_argv).pop_back();

                FILE *pf = nullptr;
#if defined (WIN32) || defined (_WIN32)
                pf = _popen(command.c_str(), "w");
                _pclose(pf);
#elif defined (linux)||defined (__linux__)
                pf = popen(command.c_str(), "w");
                pclose(pf);
#endif
                pf = nullptr;
                found = true;
                break;
            }
        }
        if (!found) cout << "invalid operation.";

    } catch (const std::exception &err) {
        cout << err.what();
    }

    return 0;
}
