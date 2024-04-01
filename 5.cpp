#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
 
using namespace std;

int main()
{
    int historia = 100;
	vector<int> v(historia, 1);
	iota(v.begin(), v.end(), 0);
 
    auto print = [](const int& n) { cout << n << ' '; };
 
    cout << "before:\t";
    for_each(v.cbegin(), v.cend(), print);
    cout << '\n';
 
    // increment elements in-place
    for_each(v.begin(), v.end(), [](int &n) { 
        n++; 
    });
 
    cout << "after:\t";
    for_each(v.cbegin(), v.cend(), print);
    cout << '\n';
 
    struct Sum
    {
        void operator()(int n) { sum += n; }
        int sum {0};
    };
 
    // invoke Sum::operator() for each element
    Sum s = for_each(v.cbegin(), v.cend(), Sum());    
    cout << "sum:\t" << s.sum << '\n';
}