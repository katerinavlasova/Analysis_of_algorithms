#include "generator.h"

//  инициализация таска, записывается номер текущего задания
Task init(int number)
{
    Task task;
    task.number = number;

    return task;
}

// сартирова44ка
void insertion_sort(task object)
{
    int temp, item;
    for (int i = 1; i < object.lenght; i++)
    {
        temp = object.data[i];
        item = i - 1;
        while (item >= 0 && object.data[item] > temp)
        {
            object.data[item + 1] = object.data[item];
            object.data[item] = temp;
            item--;
        }
    }
}


/*
 * Работа генератора
 *
*/

void generator(myqueue &q)
{
    int counter = 0; // отвечает за подсчет тасков

    auto t = static_cast<int>(time(nullptr));
    std::mt19937 gen1(t); // инициализируем генератор рандомных чисел

    // Создаем диапазон значений
    std::uniform_int_distribution<> urd(1, TASK_NUMBER); // количество тасков на каждой итерации
    std::uniform_int_distribution<> urd1(100, 500); // время ожидания
                                                    // симуляция разного времени генерации

    while (counter < TASK_NUMBER)
    {
        auto tmp_tasks_number = urd(gen1); // генерируем количество таска
                                           // на текущей итерации

        for (int i=0; i < tmp_tasks_number and counter < TASK_NUMBER; i++)
        {
            Task task = init(++counter); // создаем таск, присваиваем ему номер

            q.set(task); // устанавливаем в очередь
        }

        // симуляция генерации следующих тасков
        auto sleep_time = urd1(gen1);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }
    return;
}

// выводит в консоль сообщение о количестве созданных тасков
void show_generated_tasks_info(){
    std::cout << std::endl << TASK_NUMBER << " tasks were generated." << std::endl;
}
