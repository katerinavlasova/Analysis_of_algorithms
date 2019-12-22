#include "executer.h"
#include "log_generator.h"
#include "mytime.h"
#include <string.h>
#include <cstring>
#include <fstream>
static std::chrono::time_point<std::chrono::steady_clock> start;
static std::atomic_int tape_number(0);

// обработка тасков на ленте и передача в следующую очередь
void executer(myqueue& q1, myqueue& q2, Log &log)
{
    int tape_id = ++tape_number;
    long long all_waiting_time = 0;
    int number_of_waitings = 0;
    std::chrono::time_point<std::chrono::steady_clock> start_awaiting_time; // начало времени ожидания
    bool awaiting = false;                                                  // флаг ожидания очереди
    bool exit = false;

    std::mt19937 gen1(time(0));                             // генератор рандомных чисел
    std::uniform_int_distribution<int> uid(500, 1000);  // устанавливаем распределение
    std::uniform_int_distribution<int> uid2(0, 1000);

    while(!exit){

        // берем таск из очереди
        auto task = q1.getTask();

        // Если очередь не пустая(в случае пустой очереди возвращается таск с номером -1)
        if (task.number != -1)
        {
            // сохраняем время начала работы
            auto time_st = time_point(start);

            // симулируем обработку таска
            int len = uid(gen1);
            task.lenght = len;
            task.data = new int[len];
            for (int i = 0; i < len; i++)
                task.data[i] = uid2(gen1);
            // сохраняем время конца работы
            auto time_end = time_point(start);


            // посылаем данные {номер ленты, номер таска, начало/конец обработки} в лог
            data_t data = init(tape_id, task.number, task.lenght, time_st, time_end);
            log.set(data);


            // передаем task в очередь на обработку дальше
            q2.set(task);
            if (awaiting)
            {
                awaiting = false;  // сброс флага ожидания
                all_waiting_time += time_point(start_awaiting_time);
                number_of_waitings += 1;
            }
        }
        else
        {
            // если очередь пустая, начинаем считать время ожидания
            if (!awaiting)
            {
                awaiting = true;
                start_awaiting_time = std::chrono::steady_clock::now();
            }
            // время ожидания больше среднего времени ожидания в два раза
            else  if (number_of_waitings > 0 && time_point(start_awaiting_time) > 2 * (all_waiting_time / number_of_waitings))
            {
                exit = true;
            }
        }
    }
    return;
}



void executer2(myqueue& q1, myqueue& q2, Log &log)
{
    int tape_id = ++tape_number;

    std::chrono::time_point<std::chrono::steady_clock> start_awaiting_time; // начало времени ожидания
    bool awaiting = false;                                                  // флаг ожидания очереди
    bool exit = false;
    long long all_waiting_time = 0;
    int number_of_waitings = 0;
    std::mt19937 gen1(time(nullptr));                             // генератор рандомных чисел
    std::uniform_int_distribution<> urd(1750, 2250);  // устанавливаем распределение


    while(!exit){

        // берем таск из очереди
        auto task = q1.getTask();

        // Если очередь не пустая(в случае пустой очереди возвращается таск с номером -1)
        if (task.number != -1)
        {
            // сохраняем время начала работы
            auto time_st = time_point(start);

            insertion_sort(task);

            // сохраняем время конца работы
            auto time_end = time_point(start);


            // посылаем данные {номер ленты, номер таска, начало/конец обработки} в лог
            data_t data = init(tape_id, task.number, task.lenght, time_st, time_end);
            log.set(data);


            // передаем task в очередь на обработку дальше
            q2.set(task);

            if (awaiting)
            {
                awaiting = false;  // сброс флага ожидания
                all_waiting_time += time_point(start_awaiting_time);
                number_of_waitings += 1;
            }
        }
        else
        {
            // если очередь пустая, начинаем считать время ожидания
            if (!awaiting)
            {
                awaiting = true;
                start_awaiting_time = std::chrono::steady_clock::now();
            }
            // время ожидания больше среднего времени ожидания в два раза
            else  if (number_of_waitings > 0 && time_point(start_awaiting_time) > 2 * (all_waiting_time / number_of_waitings))
            {
                exit = true;
            }

        }
    }
    return;
}


// в очередь ничего после не передает
void executer(myqueue& q1, Log &log)
{
    int tape_id = ++tape_number;

    std::chrono::time_point<std::chrono::steady_clock> start_awaiting_time; // начало времени ожидания
    bool awaiting = false;                                                  // флаг ожидания очереди
    long long all_waiting_time = 0;
    int number_of_waitings = 0;
    bool exit = false;

    std::mt19937 gen1(time(nullptr));                 // генератор рандомных чисел
    std::uniform_int_distribution<> urd(1750, 2250);  // устанавливаем распределение


    while(!exit){
        // берем таск из очереди
        auto task = q1.getTask();

        if (task.number != -1)
        {
            // сохраняем время начала работы
            auto time_st = time_point(start);
            std::string strin = "file" + std::to_string(task.number) + ".txt";
            std::ofstream file (strin);
            for(int i = 0; i < task.lenght; i++)
            {
                file << task.data[i];
                file << " ";
            }

            // сохраняем время конца работы
            auto time_end = time_point(start);


            // посылаем данные {номер ленты, номер таска, начало/конец обработки} в лог
            data_t data = init(tape_id, task.number, task.lenght, time_st, time_end);
            log.set(data);

            if (awaiting)
            {
                awaiting = false;  // сброс флага ожидания
                all_waiting_time += time_point(start_awaiting_time);
                number_of_waitings += 1;
            }
        }
        else
        {
            // если очередь пустая, начинаем считать время ожидания
            if (!awaiting)
            {
                awaiting = true;
                start_awaiting_time = std::chrono::steady_clock::now();
            }
            // время ожидания больше среднего времени ожидания в два раза
            else  if (number_of_waitings > 0 && time_point(start_awaiting_time) > 2 * (all_waiting_time / number_of_waitings))
            {
                exit = true;
            }
            }
        }
 }


void init_start_time()
{
    start = std::chrono::steady_clock::now();
}
