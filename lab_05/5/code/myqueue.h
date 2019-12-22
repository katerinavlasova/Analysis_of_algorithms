#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <queue>
#include <mutex>

#include "struct.h"

#define QUEUE_MAX_SIZE 3

class myqueue
{
public:
    myqueue();

    void set(Task task);
    Task getTask();
    bool isEmpty();
    bool isFull();

private:
    std::queue<Task> queue;
    std::mutex mutex;
};

#endif // MYQUEUE_H
