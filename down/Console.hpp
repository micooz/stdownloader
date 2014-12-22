#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <iostream>

namespace songtaste {
    
    using namespace std;
    
    class Console {
    public:
        ~Console(){
            
        }

        explicit Console(){
            
        }
        
        template<class T>
        Console& operator<<(const T &text){
            std::system("cls");
            std::cout << text;
            return *this;
        }
    };
    
}

#endif // CONSOLE_HPP
