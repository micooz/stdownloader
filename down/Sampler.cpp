#include <boost/timer.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Sampler.h"

namespace songtaste{
    
    Sampler::Sampler() {
    } 
    
    Sampler::~Sampler() {
    }
    
    Sampler *Sampler::getInstance() {
        static Sampler ins;
        return &ins;
    }
    
    /**
     * @brief Sampler::sampling
     * @param interval ms
     * @param current
     * @param total
     */
    void Sampler::sampling(unsigned long interval, unsigned long current, unsigned long total) {
        static boost::timer t_interval;
        
        if (current > total) {
            return;
        }
        
        if (t_interval.elapsed() * 1e3 >= interval || current == total) {
            //calc percentage
            double percent = (double)current / total;
            std::stringstream conv;
            conv << percent * 100 << "% (" << current << "bytes of " << total << "bytes)";
            
            _buffer[0] = conv.str();
            
            //calc download speed
            static unsigned long last_current = current;
            double speed = double(current - last_current) / interval * 1e3;
            
            std::stringstream conv1;
            conv1 << std::setprecision(10) << speed << " bytes/s";
            
            _buffer[1] = conv1.str();
            
            last_current = current;
            //display in console
            std::system("cls");
            for (std::map<unsigned short, std::string>::iterator it = _buffer.begin(); it != _buffer.end(); ++it){
                std::cout << it->second << " ";
            }
            std::cout << std::endl;           
            
            t_interval.restart();
        }
        
    }
    
}
