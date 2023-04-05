#include <iostream>
#include <thread>

using namespace std;

int main() {
  thread t([] {
    cout << "Hello World from lambda thread." << endl;
  });

  t.join();

  return 0;
}