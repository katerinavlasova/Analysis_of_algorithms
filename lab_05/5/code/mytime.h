#ifndef MYTIME_H
#define MYTIME_H

#include <chrono>

// значение высчитано на основе худего результата обработки тасков
// значение указано в микросекундах

#define NORMAL_AWAITING_TIME 5510000

long long time_point(std::chrono::time_point<std::chrono::steady_clock> &);


bool time_is_out(long long);
bool time_is_out3(long long);


#endif // MYTIME_H
