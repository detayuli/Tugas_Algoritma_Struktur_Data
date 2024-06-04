#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <cstdlib>
#include <algorithm> // For find, count, sort
#include <random>    // For random number generation

using namespace std;

// Hash function for pair<int, int>
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

// Function to transfer similar numbers
void transferSimilarNumbers(vector<int> &from, vector<int> &to) {
    unordered_map<int, int> fromCount, toCount;
    for (int num : from) {
        if (num != 0)
            fromCount[num]++;
    }
    for (int num : to) {
        if (num != 0)
            toCount[num]++;
    }

    for (const auto &pair : fromCount) {
        int num = pair.first;
        int countFrom = pair.second;
        int countTo = toCount[num];

        if (countFrom > 0 && countTo > 0) {
            int transfers = min(countFrom, countTo);
            auto it_from = from.begin();
            while (transfers > 0 && it_from != from.end()) {
                if (*it_from == num) {
                    auto it_to = find(to.begin(), to.end(), 0); // Find an empty slot in "to"
                    if (it_to != to.end()) {
                        *it_to = num;
                        *it_from = 0; // Remove transferred number from the source cell
                        --transfers;
                    }
                }
                ++it_from;
            }
        }
    }
}

// Function to generate a vector with up to 4 random integers and fill the rest with zeros
vector<int> generateRandomPlate(int size, int min, int max) {
    vector<int> vec(size, 0);
    random_device rd;                             // Seed for the random number engine
    mt19937 gen(rd());                            // Mersenne Twister engine
    uniform_int_distribution<> dis(min, max);     // Uniform distribution for integers

    int nonZeroCount = uniform_int_distribution<>(1, 4)(gen); // Number of non-zero elements (1 to 4)
    for (int i = 0; i < nonZeroCount; ++i) {
        vec[i] = dis(gen);
    }

    shuffle(vec.begin(), vec.end(), gen); // Shuffle to randomize the position of non-zero elements

    return vec;
}

// Function to sort a vector
void sortVector(vector<int> &vec) {
    sort(vec.begin(), vec.end());
}

int main() {
    // Initialize an unordered_map to store the vectors with coordinates as keys
    unordered_map<pair<int, int>, vector<int>, pair_hash> matrix;
    int x, y;
    srand(time(0));
    bool game_over = false;

    while (!game_over) {
        // Accessing and printing elements
        cout << "Kondisi piring diatas meja:" << endl;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 4; ++j) {
                cout << "[" << i << "," << j << "] ";
                auto key = make_pair(i, j);
                if (matrix.find(key) != matrix.end()) {
                    bool allZero = true;
                    for (int k : matrix[key]) {
                        cout << k << " ";
                        if (k != 0) {
                            allZero = false;
                        }
                    }
                    if (allZero) {
                        cout << "0 ";
                    }
                } else {
                    cout << "0 0 0 0 0 0 ";
                }
                cout << "  ";
            }
            cout << endl;
        }

        // Generate plate content
        vector<int> numbers = generateRandomPlate(6, 1, 10);
        cout << "Piring kamu:" << endl;
        for (int num : numbers) {
            cout << num << " ";
        }
        cout << "\nMasukkan ke piring yang kamu pilih (format: x y)" << endl;
        cin >> x >> y;

        // Check if the coordinates are valid
        if (x < 0 || x >= 5 || y < 0 || y >= 4) {
            cout << "Penempatan kamu salah!!." << endl;
            continue; // Skip the rest of the loop and start the next iteration
        }

        auto key = make_pair(x, y);

        // Check if the chosen plate is already filled
        if (matrix.find(key) != matrix.end()) {
            cout << "Piring sudah terisi!." << endl;
            continue;
        }

        // Sort the new plate before inserting it
        sortVector(numbers);
        matrix[key] = numbers;

        // Transfer similar numbers to neighbors if common elements exist
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (const auto &dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if (nx >= 0 && nx < 5 && ny >= 0 && ny < 4) {
                auto neighbor_key = make_pair(nx, ny);
                if (matrix.find(neighbor_key) != matrix.end()) {
                    transferSimilarNumbers(matrix[key], matrix[neighbor_key]);
                }
            }
        }

        // Sort the updated plates
        sortVector(matrix[key]);
        for (const auto &dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if (nx >= 0 && nx < 5 && ny >= 0 && ny < 4) {
                auto neighbor_key = make_pair(nx, ny);
                if (matrix.find(neighbor_key) != matrix.end()) {
                    sortVector(matrix[neighbor_key]);
                }
            }
        }

        // Check if there are any available spaces left
        bool available_space = false;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (matrix.find(make_pair(i, j)) == matrix.end()) {
                    available_space = true;
                    break;
                }
            }
            if (available_space)
                break;
        }

        if (!available_space) {
            game_over = true;
            cout << "Piring sudah abis, kamu kalah! Huhuhu :< " << endl;
        }
    }

    return 0;
}
