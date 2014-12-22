#ifndef SAMPLER_H
#define SAMPLER_H

#include <map>
#include <string>

namespace songtaste{
    
    class Sampler {
    public:
        static Sampler* getInstance();
        ~Sampler();
        
        void sampling(unsigned long interval, unsigned long current, unsigned long total);
    private:
        Sampler();
        std::map<unsigned short, std::string> _buffer;
    };
    
}

#endif // SAMPLER_H
