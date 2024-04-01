#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

void calculate_partial_sum(const int* arr, int start, int end, atomic<int>& partial_sum) {
  partial_sum = 0;
  for (int i = start; i <= end; ++i) {
    partial_sum += arr[i];
  }
}

int main() {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int size = sizeof(arr) / sizeof(arr[0]);

  int num_threads = thread::hardware_concurrency();
  int chunk_size = size / num_threads;

  // "Use atomic integer for thread-safe partial sum accumulation" -Terveisin internet
  atomic<int> total_sum(0);
  atomic<int> partial_sums[num_threads];

  // Threadit
  thread threads[num_threads];
  for (int i = 0; i < num_threads; ++i) {
    int start = i * chunk_size;
    int end = (i == (num_threads - 1)) ? size - 1 : (start + chunk_size) - 1;
    threads[i] = thread(calculate_partial_sum, arr, start, end, std::ref(partial_sums[i]));
  }

  // Ootetaan että threadit on valmiit
  for (auto& thread : threads) {
    thread.join();
  }

  // Laskee yhteisen summan
  for (int i = 0; i < num_threads; ++i) {
    total_sum += partial_sums[i];
  }

  cout << "Total sum: " << total_sum << endl;

  return 0;
}