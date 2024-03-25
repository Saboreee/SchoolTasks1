#include <iostream>
#include <thread>
#include <vector>

using namespace std;

int koko = 1000;
int summa;
vector<int> Taulu(koko, 1);

class thread_kutsu {
public:
    void operator()(int x)
    {
        for (summa < x; summa++;) {
            cout << summa << " ";
        }
        cout << summa;
    }
};

int main()
{

    thread th1(thread_kutsu(), Taulu.size());
    thread th2(thread_kutsu(), Taulu.size());
    thread th3(thread_kutsu(), Taulu.size());
    thread th4(thread_kutsu(), Taulu.size());

    th1.join();
    th2.join();
    th3.join();
    th4.join();

    return 0;

}
