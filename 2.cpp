#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

int historia = 10000;
int a;
int b;
int saldo;
vector<int> Taulu(historia, 1);
mutex myMutex;
// mutexin ansiosta pystyisi käyttämään 1 muuttujaa vain pienellä säädöllä?

class thread_talletus {
public:
    void operator()(int x)
    {
        lock_guard<mutex> guard(myMutex);
        Taulu.push_back(x); 

        for (int x : Taulu) {
        a = a + x;
        }
        cout << "Rahaa tililla talletuksen jalkeen: " << a << endl;
    }
};

class thread_nosto {
public:
    void operator()(int x)
    {
        lock_guard<mutex> guard(myMutex);
        Taulu.push_back(x); 

        for (int x : Taulu) {
        b = b + x;
        }
        cout << "Rahaa tililla noston jalkeen: " << b << endl;
    }
};

int main()
{

    thread th1(thread_talletus(), 20);
    thread th2(thread_nosto(), -5);

    th1.join();
    th2.join();
    
    for (int x : Taulu) {
        saldo = saldo + x;
    }
    cout << "Tarkistus: " << saldo;

    return 0;

}