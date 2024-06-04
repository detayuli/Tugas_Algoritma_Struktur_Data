#include <iostream>
#include <vector>
#include <algorithm> // untuk std::find

using namespace std;

int main() {
    vector<int> number = {1, 2, 3, 4, 5};

    //iterasi
    for (int i = 0; i < number.size(); ++i) // Perbaiki kondisi iterasi
    {
        cout << number[i] << " ";
    }
    cout << endl;

    //insert
    cout << "================================" << endl;
    cout << "Insert" << endl;
    int indeksPenambahan, angkaPenambahan;
    cout << "Masukkan posisi angka yang ingin ditambahkan : ";
    cin >> indeksPenambahan;
    cout << "Masukkan angka yang ingin ditambahkan : ";
    cin >> angkaPenambahan;
    number.insert(number.begin() + indeksPenambahan, angkaPenambahan);
    cout << "Hasil setelah dimasukkan :" << endl;

    for (const int& insert : number)
    {
        cout << insert << " ";
    }
    cout << endl;

    //erase
    cout << "================================" << endl;
    cout << "Hapus" << endl;
    int indeksHapus;
    cout << "Masukkan posisi angka yang ingin dihapus : ";
    cin >> indeksHapus;
    number.erase(number.begin() + indeksHapus);
    cout << "Hasil setelah dihapus :" << endl;

    for (const int& erase : number)
    {
        cout << erase << " ";
    }
    cout << endl;

    //find
    cout << "================================" << endl;
    cout << "Mencari" << endl;
    int angkaCari;
    cout << "Masukkan angka yang ingin dicari letak posisi indeksnya: ";
    cin >> angkaCari;
    
    auto prosesCari = find(number.begin(), number.end(), angkaCari); // Perbaiki penggunaan find

    // Mengecek apakah nilaiCari ditemukan atau tidak
    if (prosesCari != number.end()) {
        cout << "Elemen " << angkaCari << " ditemukan di posisi: " << distance(number.begin(), prosesCari) << endl;
    } else {
        cout << "Elemen " << angkaCari << " tidak ditemukan";
    }

    cout << endl;
}


// int main() {
//     // Membuat vector integer
//     vector<int> vec = {10, 20, 30, 40, 50};

//     // Iterasi
//     cout << "Iterasi elemen-elemen vector:" << endl;
//     for (int i = 0; i < vec.size(); ++i) {
//         cout << vec[i] << " ";
//     }
//     cout << endl;

//     // Insert (menambahkan elemen)
//     vec.insert(vec.begin() + 2, 25); // Menambahkan elemen 25 di posisi indeks 2
//     cout << "Setelah insert 25 di posisi 2:" << endl;
//     for (const auto& elem : vec) {
//         cout << elem << " ";
//     }
//     cout << endl;

//     // Delete (menghapus elemen)
//     vec.erase(vec.begin() + 3); // Menghapus elemen di posisi indeks 3
//     cout << "Setelah delete elemen di posisi 3:" << endl;
//     for (const auto& elem : vec) {
//         cout << elem << " ";
//     }
//     cout << endl;

//     // Find (mencari elemen)
    // auto it = find(vec.begin(), vec.end(), 40); // Mencari elemen dengan nilai 40
    // if (it != vec.end()) {
    //     cout << "Elemen 40 ditemukan di posisi: " << distance(vec.begin(), it) << endl;
    // } else {
    //     cout << "Elemen 40 tidak ditemukan." << endl;
    // }

//     return 0;
// }
