#include "mytime.h"

// сохраняет текущее время и возращает результат
long long time_point(std::chrono::time_point<std::chrono::steady_clock> &start)
{
    auto end = std::chrono::steady_clock::now();
    auto result = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

    return result;
}


// проверка на превышение времени ожидания
bool time_is_out(long long time)
{
    return time > NORMAL_AWAITING_TIME*2 ? 1 : 0;
}


bool time_is_out3(long long time)
{
    return time > NORMAL_AWAITING_TIME*4 ? 1 : 0;
}
