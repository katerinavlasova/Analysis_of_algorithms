#include "myqueue.h"

myqueue::myqueue(){}

// Добаввление элемента в очередь
void myqueue::set(Task task)
{
    std::lock_guard<std::mutex> lock(mutex);

    if (!isFull())
        queue.push(task);
}

// Если очередь переполнена
bool myqueue::isFull()
{
    if (queue.size() > QUEUE_MAX_SIZE)
        return 1;
    else
        return 0;
}

// А еще она может быть пустой
bool myqueue::isEmpty()
{
    return queue.empty();
}

// а тут мы берем таск
Task myqueue::getTask()
{
    std::lock_guard<std::mutex> lock(mutex);

    Task task;
    task.number = -1;

    if (!isEmpty()){
        task = queue.front();
        queue.pop();
    }

    return task;
}
