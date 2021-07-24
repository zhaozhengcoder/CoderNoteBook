#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

void init() {
  cout << "Initialing..." << endl;
  // Do something...
}

void worker(once_flag* flag) {
  call_once(*flag, init);
}

int main() {
  once_flag flag;

  thread t1(worker, &flag);
  thread t2(worker, &flag);
  thread t3(worker, &flag);

  t1.join();
  t2.join();
  t3.join();

  return 0;
}