#ifndef STRUCT_H
#define STRUCT_H

typedef struct task {
    int number;
        int lenght;
        int* data;
}Task;



typedef struct data {

    int line_number;
    int task_number;
    int lenght;
    double time_start;
    double time_end;

}data_t;

Task init(int);
void insertion_sort(task object);
data_t init(int &ln, int &tn, int len, double tst, double te);

#endif // STRUCT_H
