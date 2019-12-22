#ifndef LOG_GENERATOR_H
#define LOG_GENERATOR_H


#include "generator.h"
#include "struct.h"

class Log {

    public:
        void show();
        void sort();
        void set(data_t);

    private:
        std::vector<data_t> pull;
        std::mutex mutex;
};

#endif // LOG_GENERATOR_H
