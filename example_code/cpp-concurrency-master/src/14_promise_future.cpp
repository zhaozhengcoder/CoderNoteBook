#include <cmath>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

static const int MAX = 10e8;

double concurrent_worker(int min, int max) {
  double sum = 0;
  for (int i = min; i <= max; i++) {
    sum += sqrt(i);
  }
  return sum;
}

void concurrent_task(int min, int max, promise<double>* result) {
  vector<future<double>> results;

  unsigned concurrent_count = thread::hardware_concurrency();
  min = 0;
  for (int i = 0; i < concurrent_count; i++) {
    packaged_task<double(int, int)> task(concurrent_worker);
    results.push_back(task.get_future());

    int range = max / concurrent_count * (i + 1);
    thread t(std::move(task), min, range);
    t.detach();

    min = range + 1;
  }

  cout << "threads create finish" << endl;
  double sum = 0;
  for (auto& r : results) {
    sum += r.get();
  }
  result->set_value(sum);
  cout << "concurrent_task finish" << endl;
}

int main() {
  auto start_time = chrono::steady_clock::now();

  promise<double> sum;
  concurrent_task(0, MAX, &sum);

  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
  cout << "Concurrent task finish, " << ms << " ms consumed." << endl;
  cout << "Result: " << sum.get_future().get() << endl;
  return 0;
}