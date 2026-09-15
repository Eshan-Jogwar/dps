#include <bits/stdc++.h>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

// c = m ^ e mod n
// m = c ^ d mod n
// (e * d) % phi(n) = 1

int modPow(int base, int exponent, int n) {
  int result = 1;

  for (int i = 0; i < exponent; i++) {
    result = (result * base) % n;
  }

  return result;
}

void encode(string text, int e, int p, int q, vector<int> &result) {
  int n = p * q;
  int phi = (p - 1) * (q - 1);

  for (char c : text) {
    int t = (int)c;
    int cipher = modPow(t, e, n);
    result.push_back(cipher);
  }
}

string decode(vector<int> cipher, int e, int p, int q) {
  int n = p * q;
  int phi = (p - 1) * (q - 1);

  int d = 1;
  while ((d * e) % phi != 1) {
    d++;
  }

  string result = "";

  for (int m : cipher) {
    int c = modPow(m, d, n);
    result += (char)c;
  }

  return result;
}

int main() {
  string text;
  int p, q, e;

  cout << "enter text: ";
  cin >> text;

  cout << "enter p: ";
  cin >> p;

  cout << "enter q: ";
  cin >> q;

  cout << "enter e: ";
  cin >> e;

  vector<int> result;

  encode(text, e, p, q, result);

  for (int i : result) {
    cout << i << " ";
  }

  cout << endl;

  cout << decode(result, e, p, q);
}
