#include <iostream>
#include <string>
#include <vector>
#include <cctype>

std::string normalizePlaintext(const std::string &text) {
    std::string result;
    for (char ch : text) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            result.push_back(std::toupper(static_cast<unsigned char>(ch)));
        }
    }
    return result;
}

std::string encryptRailFence(const std::string &text, int rails, std::vector<std::string> &railRows) {
    if (rails <= 1 || text.empty()) {
        railRows.assign(rails, std::string());
        return text;
    }

    railRows.assign(rails, std::string());
    int currentRail = 0;
    int direction = 1;

    for (char ch : text) {
        railRows[currentRail].push_back(ch);
        currentRail += direction;
        if (currentRail == rails - 1 || currentRail == 0) {
            direction = -direction;
        }
    }

    std::string ciphertext;
    for (const auto &row : railRows) {
        ciphertext += row;
    }
    return ciphertext;
}

std::string decryptRailFence(const std::string &ciphertext, int rails, std::vector<std::string> &railRows) {
    if (rails <= 1 || ciphertext.empty()) {
        railRows.assign(rails, std::string());
        return ciphertext;
    }

    int n = ciphertext.size();
    std::vector<int> railLen(rails, 0);

    int currentRail = 0;
    int direction = 1;
    for (int i = 0; i < n; ++i) {
        railLen[currentRail]++;
        currentRail += direction;
        if (currentRail == rails - 1 || currentRail == 0) {
            direction = -direction;
        }
    }

    railRows.assign(rails, std::string());
    int index = 0;
    for (int r = 0; r < rails; ++r) {
        railRows[r] = ciphertext.substr(index, railLen[r]);
        index += railLen[r];
    }

    std::string plaintext;
    plaintext.reserve(n);
    currentRail = 0;
    direction = 1;
    std::vector<int> railPos(rails, 0);
    for (int i = 0; i < n; ++i) {
        plaintext.push_back(railRows[currentRail][railPos[currentRail]++]);
        currentRail += direction;
        if (currentRail == rails - 1 || currentRail == 0) {
            direction = -direction;
        }
    }
    return plaintext;
}

std::vector<std::string> buildRailGrid(const std::string &text, int rails) {
    int n = text.size();
    std::vector<std::string> grid(rails, std::string(n, ' '));

    int currentRail = 0;
    int direction = 1;
    for (int i = 0; i < n; ++i) {
        grid[currentRail][i] = text[i];
        currentRail += direction;
        if (currentRail == rails - 1 || currentRail == 0) {
            direction = -direction;
        }
    }
    return grid;
}

int main() {
    std::string plaintext = "THE END SEMESTER EXAMINATION WILL BEGIN FROM FIFTEENTH DECEMBER.";
    std::string normalized = normalizePlaintext(plaintext);
    int rails = 3;

    std::vector<std::string> encryptRows;
    std::string ciphertext = encryptRailFence(normalized, rails, encryptRows);

    std::cout << "Normalized plaintext: " << normalized << "\n";
    std::cout << "Total characters in plaintext: " << normalized.size() << "\n\n";

    std::cout << "3-rail zig-zag arrangement (encryption):\n";
    auto grid = buildRailGrid(normalized, rails);
    for (int r = 0; r < rails; ++r) {
        std::cout << "Rail " << r + 1 << ": ";
        for (char ch : grid[r]) {
            std::cout << (ch == ' ' ? ' ' : ch);
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "Characters row-wise from Rail 1 to Rail 3:\n";
    for (int r = 0; r < rails; ++r) {
        std::cout << "Rail " << r + 1 << ": " << encryptRows[r] << "\n";
    }
    std::cout << "\n";

    std::cout << "Ciphertext: " << ciphertext << "\n";
    std::cout << "Total characters in ciphertext: " << ciphertext.size() << "\n\n";

    std::vector<std::string> decryptRows;
    std::string recovered = decryptRailFence(ciphertext, rails, decryptRows);

    std::cout << "Reconstructed 3-rail zig-zag arrangement (decryption):\n";
    auto decryptGrid = buildRailGrid(recovered, rails);
    for (int r = 0; r < rails; ++r) {
        std::cout << "Rail " << r + 1 << ": ";
        for (char ch : decryptGrid[r]) {
            std::cout << (ch == ' ' ? ' ' : ch);
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "Recovered plaintext: " << recovered << "\n";
    std::cout << "Total characters recovered: " << recovered.size() << "\n";

    return 0;
}
