#pragma once
#include <random>

class LossChannel{
    public:
    LossChannel(double loss,unsigned seed):
    drop_(loss),rng_(seed) {}
    bool deliver()
    {
        return !drop_(rng_); 
    }

    private:
        std::bernoulli_distribution drop_;
        std::mt19937 rng_;
};