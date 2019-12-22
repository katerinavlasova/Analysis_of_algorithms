#ifndef GENERATOR_H
#define GENERATOR_H

#include <thread>
#include <random>
#include <atomic>
#include <iostream>
#include <iomanip>

#include "myqueue.h"
#include "mytime.h"

#define TASK_NUMBER 15

void generator(myqueue&);

void show_generated_tasks_info();

#endif // GENERATOR_H
