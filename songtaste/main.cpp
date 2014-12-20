#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const string help = "this program cannot be run directly, please give me some args!";

vector<string> sub_routines = {
    "list", "fetch"
};

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            cout << help << endl;
            exit(0);
        }

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

                break;
            }
        }

    } catch (const std::logic_error &err) {
        cout << err.what() << endl;
    }

    return 0;
}
