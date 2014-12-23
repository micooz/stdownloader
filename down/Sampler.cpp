#include <boost/timer.hpp>
#include <json/json.h>
#include <iostream>
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
        static Json::Value json;
        
        if (current > total) {
            return;
        }
        
        if (t_interval.elapsed() * 1e3 >= interval || current == total) {
            //calc percentage
            double percent = (double)current / total;
            std::stringstream conv;
            conv << percent * 100 << "%";
            //calc download speed
            static unsigned long last_current = current;
            double speed = double(current - last_current) / interval * 1e3;
            last_current = current;
            t_interval.restart();
            //generate json string
            json["percentage"] = percent;
            json["percentstr"] = conv.str();
            json["current"   ] = double(current);
            json["total"     ] = double(total);
            json["bytes/s"   ] = speed;
            Json::FastWriter writer;
            std::system("cls");
            std::cout << writer.write(json);
        }
        
    }
    
}
