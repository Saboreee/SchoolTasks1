#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;


class Game_Task {
    public :
    Game_Task() {}
    virtual void Game_Task::perform() = 0;
};

class SubClass : public Game_Task
    {
    public:
    SubClass(){}
    virtual ~SubClass() {}
    };

    class task : public Game_Task
    {
    public:
    task(){}
    virtual ~task() {}
    };

int main() {
    const auto processor_count = std::thread::hardware_concurrency();
    cout << processor_count;
    
    
    vector<Game_Task*> tasks;
    
    int number_of_tasks = tasks.size();
    for (int i = 0; i < number_of_tasks; i++)
    {
    task[i]->perform();
    }
    
 // Continue only after all tasks are complete!

    return 0;

}