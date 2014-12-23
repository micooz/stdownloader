#ifndef SAMPLER_H
#define SAMPLER_H

namespace songtaste{
    
    class Sampler {
    public:
        static Sampler* getInstance();
        ~Sampler();
        
        void sampling(unsigned long interval, unsigned long current, unsigned long total);
    private:
        Sampler();
    };
    
}

#endif // SAMPLER_H
