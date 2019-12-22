#include "log_generator.h"

// в лог пихаем дату(номер ленты, номер таска, время начала/конца работы )
void Log::set(data_t data)
{
    std::lock_guard<std::mutex> lock(mutex);

    pull.push_back(data);
}


void Log::sort()
{
    auto n = static_cast<size_t>(pull.size());

    if (n > 1)
    {
        bool swapped = true;

        while (swapped)
        {
            swapped = false;

            for (size_t i=0; i+1<n; i++)
            {
                if (pull[i].task_number > pull[i+1].task_number)
                {
                    auto data = pull[i];
                    pull[i] = pull[i+1];
                    pull[i+1] = data;

                    swapped = true;
                }
            }
            n--;
        }
    }
}


void Log::show()
{
    std::cout.setf( std::ios::fixed);

    sort();

    auto tmp_n = pull[0].task_number;

    std::cout << "Tape    " << "Task    \t" << "Lenght    \t" << "Start \t" << "End" << std::endl << std::endl;
    for (auto t : pull){

        if (tmp_n != t.task_number){
            std::cout << "___" << std::endl;
            tmp_n = t.task_number;
        }

        std::cout << "Tape: " << t.line_number << ", Task: " << t.task_number << "\t" <<  " Lenght: " << t.lenght<< "  ";
        std::cout << "\t" << std::setprecision(6) << t.time_start << "\t" << t.time_end << std::endl;

    }
}


data_t init(int &ln, int &tn, int len, double tst, double te)
{
    data_t data;
    data.line_number = ln;
    data.task_number = tn;
    data.lenght = len;
    data.time_start = tst / 1e+006;
    data.time_end = te / 1e+006;

    return data;
}
