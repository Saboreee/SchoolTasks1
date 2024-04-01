#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class Game_Task {

};

class TaskQueue {
public:
  TaskQueue(int nof_threads) {
    // Luo työjono
    jobs = new queue<Game_Task>();

    // Luo säikeet
    for (int i = 0; i < nof_threads; ++i) {
      threads.push_back(thread(&TaskQueue::run, this));
    }
  }

  void addJob(Game_Task task) {
    // Lisää työ jonoon
    lock_guard<mutex> lock(mtx);
    jobs->push(task);
    cv.notify_one(); // Herättää yhden odottavan säikeen
  }

  ~TaskQueue() {
    // Tyhjennä työjono
    {
      lock_guard<mutex> lock(mtx);
      while (!jobs->empty()) {
        jobs->pop();
      }
    }

    // Herättää kaikki säikeet ja odottaa niiden lopettamista
    cv.notify_all();
    for (auto& thread : threads) {
      thread.join();
    }
  }

private:
  void run() {
    while (true) {
      Game_Task task;
      cout << "odottaa";
      // Odota työtä
      {
        unique_lock<mutex> lock(mtx);
        while (jobs->empty()) {
          cv.wait(lock);
        }

        // Ota työ jonoon
        task = jobs->front();
        jobs->pop();
      }
    cout << "yep";
      // Suorita työ
    }
  }

  queue<Game_Task>* jobs;
  mutex mtx;
  condition_variable cv;
  vector<thread> threads;
};

int main() {
  TaskQueue queue(4);

  // Lisää töitä jonoon
  for (int i = 0; i < 10; ++i) {
    Game_Task task;
    // ... Alusta tehtävä ...
    queue.addJob(task);
  }

  return 0;
}