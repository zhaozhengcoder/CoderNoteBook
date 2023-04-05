#include <iostream>
#include <string>
#include <thread>

using namespace std;

void hello(string name) {
  cout << "Welcome to " << name << endl;
}

int main() {
  thread t(hello, "https://paul.pub");
  t.join();

  return 0;
}