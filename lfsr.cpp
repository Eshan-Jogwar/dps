#include <bits/stdc++.h>
using namespace std;

int main() {
  int num = 0b1001;
  vector<int> taps = {2, 3};

  for (int i = 0; i < 20; i++) {
    int temp = ((num >> taps[0]) & 1) ^ ((num >> taps[1]) & 1);

    for (int j = 2; j < taps.size(); j++) {
      temp ^= (num >> taps[j]) & 1;
    }

    num >>= 1;
    num |= temp << 3;

    cout << bitset<4>(num) << endl;
  }
}
