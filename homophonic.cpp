#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cctype>

using namespace std;

int main() {

    char matrix[10][10] = {
        {'o','e','r','a','t','i','e','w','n','a'},
        {'s','o','i','s','d','h','o','t','d','e'},
        {'h','s','p','a','e','h','n','i','x','o'},
        {'e','q','e','e','n','t','h','l','y','s'},
        {'a','i','e','p','j','w','r','e','n','a'},
        {'t','z','m','f','d','a','i','r','l','t'},
        {'u','g','c','e','g','u','t','o','e','l'},
        {'b','i','t','u','h','c','e','n','r','y'},
        {'t','n','c','h','b','o','t','v','a','f'},
        {'a','k','r','s','l','d','m','o','r','s'}
    };

    string plaintext;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    vector<pair<int, int>> positions[26];

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            char c = matrix[i][j];

            if (c >= 'a' && c <= 'z') {
                positions[c - 'a'].push_back({i, j});
            }
        }
    }

    random_device rd;
    mt19937 gen(rd());

    string ciphertext;

    for (char c : plaintext) {

        // Preserve spaces
        if (c == ' ') {
            ciphertext += " ";
            continue;
        }

        c = tolower(c);

        if (c >= 'a' && c <= 'z' && !positions[c - 'a'].empty()) {

            // Randomly select one occurrence
            uniform_int_distribution<int> dist(
                0, positions[c - 'a'].size() - 1
            );

            int index = dist(gen);

            int row = positions[c - 'a'][index].first;
            int col = positions[c - 'a'][index].second;

            ciphertext += to_string(row) + to_string(col) + " ";
        }
        else {
            ciphertext += c;
        }
    }

    cout << "\nOriginal Plaintext : " << plaintext << endl;
    cout << "Ciphertext         : " << ciphertext << endl;

    return 0;
}
