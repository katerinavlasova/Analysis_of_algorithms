#include "executer.h"
#include "log_generator.h"

using namespace std;


int main()
{
    init_start_time();

    myqueue q1, q2, q3;

    Log log;

    // Задачи создаются и передаются в очередь 1
    std::thread generate_task (generator, ref(q1));

    // Работа лент
    std::thread tape1([&](){executer(q1, q2, log);});
    std::thread tape2([&](){executer2(q2, q3, log);});
    std::thread tape3([&](){executer(q3, log);});


    // Просим main подождать ленты
    if (generate_task.joinable())
        generate_task.join();

    if (tape1.joinable())
        tape1.join();

    if (tape2.joinable())
        tape2.join();

    if (tape3.joinable())
        tape3.join();


    // Вывод результата
    log.show();

    show_generated_tasks_info();

    return 0;
}
