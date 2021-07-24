#include <cmath>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

static const int MAX = 10e8;
static double sum = 0;

void worker(int min, int max) {
  for (int i = min; i <= max; i++) {
    sum += sqrt(i);
  }
}

void serial_task(int min, int max) {
  auto start_time = chrono::steady_clock::now();
  sum = 0;
  worker(0, MAX);
  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
  cout << "Serail task finish, " << ms << " ms consumed, Result: " << sum << endl;
}

void concurrent_task(int min, int max) {
  auto start_time = chrono::steady_clock::now();

  unsigned concurrent_count = thread::hardware_concurrency();
  cout << "hardware_concurrency: " << concurrent_count << endl;
  vector<thread> threads; 
  min = 0;
  sum = 0;
  for (int t = 0; t < concurrent_count; t++) {
    int range = max / concurrent_count * (t + 1);
    threads.push_back(thread(worker, min, range));
    min = range + 1;
  }
  for (int i = 0; i < threads.size(); i++) {
    threads[i].join();
  }

  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
  cout << "Concurrent task finish, " << ms << " ms consumed, Result: " << sum << endl;
}

int main() {
  serial_task(0, MAX);
  concurrent_task(0, MAX);
  return 0;
}